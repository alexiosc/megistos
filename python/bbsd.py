#!/usr/bin/env python3

import argparse
import asyncio
import fnmatch
import json
import os
import signal
import socket
import sys
import time
import uuid
import yaml

import logging
import random
import string
import pprint

import attr
import cerberus

from megistos import MegistosProgram
from megistos import config
import megistos.validation


"""
{"op":"ping"}

{"op":"sub", "t":"*"}

{"op":"pub", "t":"foo", "d":[1,2,3]}
"""


class Connection:
    connection_id: int = attr.ib()
    channel: str = attr.ib()
    queue: attr.ib(repr=False)


    def __init__(self, connection_id, channel, reader, writer):
        self.connection_id = connection_id
        self.channel = channel
        self.queue = asyncio.Queue()
        self.dequeuer = asyncio.create_task(self.dequeuer(self.connection_id, reader, writer))
        self.tty, self.pid, self.username = None, None, None


    def __del__(self):
        self.dequeuer.cancel()  # Probably not necessary
        del self.queue
        

    def __str__(self):
        return f"Connection #{self.connection_id}"


    def __repr__(self):
        return f"Connection #{self.connection_id} " + \
            f"(TTY {self.channel}, PID {self.pid}, User {self.username})"


    async def dequeuer(self, connection_id, reader, writer):
        try:
            logging.debug(f"Dequeuer for connection #{connection_id} started.")
            while not reader.at_eof():
                logging.debug(f"Dequeuer for {self} waiting.")
                msg = await self.queue.get()
                logging.debug(f"{self!r}: delivering {msg}.")
                writer.write((msg + "\n").encode("utf-8"))
                await writer.drain()

        except asyncio.CancelledError:
            raise

        except Exception as e:
            logging.exception(f"Dequeuer for {self} failed")


    def publish(self, message):
        asyncio.create_task(self.queue.put(message))
        
             


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




class BBSD(MegistosProgram):
    """The BBS daemon coded as an asynchronous Python class, with a lot
    more functionality in a lot less code."""

    DESCRIPTION = "Megistos BBS Daemon (bbsd)"

    def __init__(self):
        super().__init__()
        logging.debug("BBS Daemon starting")

        self.parse_command_line()

        # Read the configuration, keep only the bbsd section.
        c = config.read_config(self.args.config, config.CONFIG_SCHEMA)
        self.config = c['bbsd']

        self.connection_id = 0
        self.connections = dict()
        self.subscriptions = dict()

        logging.info("BBS Daemon started")


    def parse_command_line(self):
        parser = self.create_command_line_parser(description=self.DESCRIPTION)

        self.args = parser.parse_args()
        return self.args


    async def ticks(self):
        try:
            tick = self.config['tick']
            logging.info(f"Tick handler started. (period: {tick}s)")
            while True:
                await asyncio.sleep(tick)
                logging.debug("Tick!")
                for x in asyncio.all_tasks():
                    logging.debug(f"  running task: {x.cancelled():<5} {x.get_coro()}")
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


    async def handle_connection(self, reader, writer) -> None:
        self.connection_id += 1
        connection_id = self.connection_id
        channel = "?"

        conn = Connection(self.connection_id, channel, reader, writer)
        self.connections[connection_id] = conn

        logging.info(f"{conn} established")

        try:
            while not reader.at_eof():
                data = await reader.readline()
                command = data.decode().strip()

                if not command:
                    continue

                logging.debug(f"{conn!r}: received '{command}'")
                response = dict()

                try:
                    data = json.loads(command)
                    logging.debug(f"JSON decoded correctly: {data}")
                    response = self.process_command(data, conn)

                except json.decoder.JSONDecodeError as e:
                    response = dict(ok=False, err=repr(e))
                    logging.error(f"{conn}: JSON decoding error: {e!r}")

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
            logging.debug(f"{conn!r} reset")

        finally:
            logging.info(f"{conn!r} ended")

            # Remove this connection ID from all subscriptions.
            for sub in self.subscriptions.values():
                sub = sub.remove(connection_id)

            # Destoy the connection and cancel its tasks
            conn.dequeuer.cancel()
            del conn


    def run(self):
        loop = asyncio.get_event_loop()
        # May want to catch other signals too
        signals = (signal.SIGHUP, signal.SIGTERM, signal.SIGINT)
        for s in signals:
            loop.add_signal_handler(
                s, lambda s=s: asyncio.create_task(shutdown(loop, signal=s)))
        loop.set_exception_handler(self.handle_exception)
    
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


    def process_command(self, data, conn):
        try:
            op = data['op']
        except KeyError:
            return dict(ok=False, err="Missing op")

        # Ping requests
        if op == 'ping':
            return dict(ok=True)

        # Hello: associate connection with channel/PID.
        if op == 'hello':
            return self.hello(data, conn)

        # Subscriptions
        if op == 'sub':
            return self.subscribe(data, conn)

        # Subscriptions
        if op == 'subs':
            return self.get_subscriptions(conn)

        if op == 'cancel':
            return self.unsubscribe(data, conn)

        if op == 'pub':
            return self.publish(data, conn)

        return dict(ok=False, err=f"Unhandled op {op}")


    def hello(self, data, connection):
        connection_id = connection.connection_id
        try:
            tty = data['tty']
        except KeyError:
            return dict(ok=False, err="Missing tty")

        try:
            pid = data['pid']
        except KeyError:
            return dict(ok=False, err="Missing pid")

        connection.channel = tty
        connection.pid = pid
        connection.username = data.get('u')
        logging.info(f"Well hello there, {connection!r}")

        return dict(ok=True)
            

    def subscribe(self, data, connection):
        connection_id = connection.connection_id
        try:
            topic = data['t']
        except KeyError:
            return dict(ok=False, err="Missing t")

        # Add the topic and connection ID.
        self.subscriptions.setdefault(topic, set([])).add(connection_id)
        return dict(ok=True)


    def get_subscriptions(self, connection):
        connection_id = connection.connection_id
        subscriptions = [ topic
                          for topic, subscribers in self.subscriptions.items()
                          if connection_id in subscribers ]
        return dict(ok=True, subs=subscriptions)

        
    def unsubscribe(self, data, connection):
        connection_id = connection.connection_id
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
            logging.error(f"{conn} was never subscribed to topic {topic}")
            return dict(ok=False, err="Not subscribed")

        except Exception as e:
            logging.exception(f"Failed to unsubscribe {conn} from topic {topic}: {e}")
            return dict(ok=False, err="Error:" + str(e))

        return dict(ok=True)


    def publish(self, data, connection):
        connection_id = connection.connection_id
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
        str_message = json.dumps(message, separators=(',',':')) + "\n"
        logging.debug(f"Publishing {str_message}")

        for pattern, conn_ids in self.subscriptions.items():
            logging.debug(f"Testing {pattern} -> {conn_ids}")
            # Does the subscription pattern match the topic?
            if fnmatch.fnmatch(topic, pattern):
                # It does. Queue the message to all subscribed connections.
                for conn_id in conn_ids:
                    try:
                        other_connection = self.connections[conn_id]
                        logging.debug(f"Publishing to {other_connection!r}")
                        other_connection.publish(str_message)
                    except KeyError:
                        pass

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
