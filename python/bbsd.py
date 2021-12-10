#!/usr/bin/env python3

import os
import argparse
import asyncio
import signal
import uuid
import json
import socket
import yaml
import sys
import time
import fnmatch

import logging
import random
import string
import pprint

import cerberus

import megistos.validation


"""
{"op":"ping"}

{"op":"sub", "t":"*"}

{"op":"pub", "t":"foo", "d":[1,2,3]}


"""



async def shutdown(loop, signal=None):
    """Cleanup tasks tied to the service's shutdown."""
    if signal:
        logging.info(f"Received exit signal {signal.name}...")
    logging.info("Closing database connections")
    logging.info("NACKing outstanding messages")
    tasks = [t for t in asyncio.all_tasks() if t is not
             asyncio.current_task()]

    [task.cancel() for task in tasks]

    logging.info(f"Cancelling {len(tasks)} outstanding tasks")
    await asyncio.gather(*tasks, return_exceptions=True)
    logging.info(f"Flushing metrics")
    loop.stop()




class BBSD:
    """The BBS daemon coded as an asynchronous Python class, with a lot
    more functionality in a lot less code."""

    DESCRIPTION = "Megistos BBS Daemon (bbsd)"

    BBSD_PORT = 8889

    BBSD_SOCK = "/tmp/bbsd.sock"

    CONFIG_SCHEMA = {
        'bbsd': {
            'type': 'dict',
            'schema': {
                'tick':     dict(type='integer', min=1, max=30, default=15),
                'socket':   dict(type='string', default=BBSD_SOCK),
                'tcp_addr': dict(type='string', default="127.0.0.1"),
                'tcp_port': dict(type='integer', min=1, max=65535, default=BBSD_PORT),
            }
        }
    }

    def __init__(self):
        logging.basicConfig(
            #level=logging.INFO,
            level=logging.DEBUG,
            format="%(asctime)s bbsd[%(process)d] %(levelname)s: %(message)s",
            datefmt="%Y-%m-%d %H:%M:%S",
        )
        logging.info("Started")

        self.connection_id = 0
        self.subscriptions = dict()
        
        self.parse_command_line()
        self.parse_config()


    def parse_command_line(self):
        parser = argparse.ArgumentParser(description=self.DESCRIPTION)

        parser.add_argument("-c", "--config", metavar="PATH",
                            type=str, default="bbsd.yaml",
                            help="""Specify configuration file. (default: %(default)s)""")

        self.args = parser.parse_args()
        return self.args


    def parse_config(self):
        logging.info(f"Reading configuration from {self.args.config}")
        try:
            with open(self.args.config, encoding="utf-8") as f:
                config = yaml.safe_load(f)
                v = cerberus.Validator(self.CONFIG_SCHEMA)
                if not v.validate(config):
                    logging.critical(f"Configuration invalid")
                    sys.exit(1)
                # We only care about this.
                self.config = config['bbsd']
                logging.debug(f"Configuration loaded and valid")

        except cerberus.schema.SchemaError as e:
            logging.critical(f"Configuration error: {e}")
            raise
            sys.exit(1)
            
        except Exception as e:
            msg = f"Failed to read config file {self.args.config}"
            logging.critical(msg, exc_info=e)
            logging.exception(f"Failed to read config file {self.args.config}", exc_info=e)
            raise


    async def ticks(self):
        try:
            tick = self.config['tick']
            logging.info(f"Tick handler started. (period: {tick}s)")
            while True:
                await asyncio.sleep(tick)
                logging.debug("Tick!")
        except Exception as e:
            logging.exception(f"Whoops")


    async def sock_server(self) -> None:
        try:
            socket_path = self.config['socket']
            logging.info(f"Listening on UNIX domain socket {socket_path}")
            server = await asyncio.start_unix_server(self.handle_connection,
                                                     path=socket_path)
            logging.debug("Unix domain socket server started")
            async with server:
                await server.serve_forever()

        except Exception as e:
            logging.exception(f"Exception in sock_server()")
        
    
    async def tcp_server(self) -> None:
        try:
            addr = self.config['tcp_addr']
            port = self.config['tcp_port']
            logging.info(f"Listening on TCP at {addr} port {port}")
        
            # asyncio disables dual stack, so create our own dual stack socket.
            sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.bind((addr, port))
            
            server = await asyncio.start_server(self.handle_connection, sock=sock)
            logging.debug("TCP server started")
            async with server:
                await server.serve_forever()

        except Exception as e:
            logging.exception(f"tcp_server")


    async def dequeuer(self, connection_id, writer):
        try:
            logging.debug(f"Dequeuer for connection #{connection_id} started.")
            while True:
                try:
                    logging.debug(f"Dequeuer for connection #{connection_id} waiting.")
                    msg = await self.queues[connection_id].get()
                    logging.debug(f"Dequeuer for connection #{connection_id}: {msg}.")
                except KeyError:
                    # The queue is gone.
                    logging.error(f"Queue for connection #{connection_id} is gone.")
                    return
                
                logging.debug(f"Connection #{connection_id}: delivering {msg}.")
                writer.write((msg + "\n").encode("utf-8"))
                await writer.drain()

        except Exception as e:
            logging.exception(f"Dequeuer for connection #{connection_id} failed")
             


    async def handle_connection(self, reader, writer) -> None:
        self.connection_id += 1
        connection_id = self.connection_id
        queue = asyncio.Queue()
        dequeuer = asyncio.create_task(self.dequeuer(connection_id, writer))
        self.queues[connection_id] = queue
        logging.info(f"Connection #{connection_id} established")

        try:
            while not reader.at_eof():
                data = await reader.readline()
                command = data.decode()
                command = command.strip()

                if not command:
                    continue

                logging.debug(f"Connection #{connection_id}: received '{command}'")
                response = dict()


                try:
                    if command:
                        data = json.loads(command)
                        logging.debug(f"JSON decoded correctly: {data}")
                        response = self.process_command(data, connection_id)
                    else:
                        response = dict(ok=False, err="Empty")

                except json.decoder.JSONDecodeError as e:
                    response = dict(ok=False, err=repr(e))
                    logging.error(f"connection #{connection_id}: JSON decoding error: {e!r}")

                str_response = json.dumps(response, separators=(',',':')) + "\n"
                writer.write(str_response.encode("utf-8"))
                await writer.drain()
                logging.debug("input: sent back response")

        except asyncio.TimeoutError as e:
            logging.notice("input: Timeout")
    
        except asyncio.CancelledError as e:
            logging.notice("input: Cancelled")
            
        except asyncio.InvalidStateError as e:
            logging.error("input: Invalid State")
            
        except asyncio.IncompleteReadError as e:
            logging.error("input: Incomplete Read")
                          
        except asyncio.LimitOverrunError as e:
            logging.error("input: Reached buffer size limit while looking for a separator")
    
        except ConnectionResetError as e:
            # import traceback
            # print(traceback.format_exc())
            logging.info(f"Connection id #{connection_id} ended")
            pass

        finally:
            logging.info(f"Connection #{connection_id} ended")
            # Remove this connection ID from all subscriptions.
            for sub in self.subscriptions.values():
                sub = sub.remove(set([connection_id]))
            # Remove its message queue
            del self.queues[connection_id]
            del queue


    def run(self):
        loop = asyncio.get_event_loop()
        # May want to catch other signals too
        signals = (signal.SIGHUP, signal.SIGTERM, signal.SIGINT)
        for s in signals:
            loop.add_signal_handler(
                s, lambda s=s: asyncio.create_task(shutdown(loop, signal=s)))
        loop.set_exception_handler(self.handle_exception)
        self.queues = dict()
    
        try:
            # loop.create_task(publish(queue))
            # loop.create_task(consume(queue))
            loop.create_task(self.ticks())
            loop.create_task(self.tcp_server())
            loop.create_task(self.sock_server())
            loop.run_forever()

        finally:
            loop.close()
            logging.info("Done.")


    def process_command(self, data, connection_id):
        try:
            op = data['op']
        except KeyError:
            return dict(ok=False, err="Missing op")

        # Ping requests
        if op == 'ping':
            return dict(ok=True)

        # Subscriptions
        if op == 'sub':
            return self.subscribe(data, connection_id)

        # Subscriptions
        if op == 'subs':
            return self.get_subscriptions(connection_id)

        if op == 'cancel':
            return self.unsubscribe(data, connection_id)

        if op == 'pub':
            return self.publish(data, connection_id)

        return dict(ok=False, err=f"Unhandled op {op}")


    def subscribe(self, data, connection_id):
        try:
            topic = data['t']
        except KeyError:
            return dict(ok=False, err="Missing t")

        # Add the topic and connection ID.
        self.subscriptions.setdefault(topic, set([])).add(connection_id)
        pprint.pprint(self.subscriptions)
                                       
        return dict(ok=True)


    def get_subscriptions(self, connection_id):
        subscriptions = [ topic
                          for topic, subscribers in self.subscriptions.items()
                          if connection_id in subscribers ]
        return dict(ok=True, subs=subscriptions)

        
    def unsubscribe(self, data, connection_id):
        try:
            topic = data['t']
        except KeyError:
            return dict(ok=False, err="Missing t")

        # Remove the connection id, and also the topic if empty.
        try:
            sub = self.subscriptions[topic]
            assert connection_id in sub
            sub.remove(connection_id)
            if not sub:
                del self.subscriptions[topic]

        except (AssertionError, KeyError):
            logging.error(f"Connection #connection_id was never subscribed to topic {topic}")
            return dict(ok=False, err="Not subscribed")

        except Exception as e:
            logging.exception(f"Failed to unsubscribe #connection_id from topic {topic}: {e}")
            return dict(ok=False, err="Error:" + str(e))

        pprint.pprint(self.subscriptions)
        return dict(ok=True)


    def publish(self, data, connection_id):
        try:
            topic = data['t']
        except KeyError:
            return dict(ok=False, err="Missing t")

        try:
            payload = data['d']
        except KeyError:
            return dict(ok=False, err="Missing d")

        # Create the message.
        u = str(uuid.uuid4())
        message = dict(p=connection_id, t=topic, u=u, ts=time.time(), d=payload)
        str_message = json.dumps(message, separators=(',',':'))
        logging.debug(f"Publishing {str_message}")

        for pattern, conn_ids in self.subscriptions.items():
            logging.debug(f"Testing {pattern} -> {conn_ids}")
            # Does the subscription pattern match the topic?
            if fnmatch.fnmatch(topic, pattern):
                # It does. Queue the message to all subscribed connections.
                for conn_id in conn_ids:
                    if conn_id not in self.queues:
                        self.error(f"Connection #{conn_id} still subscribed " +
                                   f"to topic #{topic}, but its queue is gone")
                        continue
                    logging.debug(f"Publishing to connection #{conn_id}")
                    asyncio.create_task(self.queues[conn_id].put(str_message))

        return dict(ok=True, u=u)


    def handle_exception(self, loop, context):
        msg = context.get("exception", context["message"])
        # if 'exception' in context:
        #     print(type(context['exception']))
        #     # import traceback
        #     # print(traceback.format_exc(context['exception']))
        logging.critical(f"Caught exception: {msg}")
        logging.info("Shutting down...")
        asyncio.create_task(shutdown(loop))


if __name__ == "__main__":
    BBSD().run()
