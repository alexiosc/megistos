#!/usr/bin/python3

import asyncio
import ctypes
import fcntl
import json
import logging
import os
import pty
import re
import signal
import struct
import sys
import termios
import tty


from .task_logger import create_task


class BBSDClient(object):
    """Functionality used to talk to the bbsd.
    """

    def __init__(self, config, channel):
        self.config = config
        self.channel = channel
        self.connection = None
        self.pub_queue = asyncio.Queue()
        self.response_queue = asyncio.Queue()


    async def connect(self, tcp=False):
        # Connected already?
        if self.connection is not None:
            return

        # TODO: Implement TCP too.
        if tcp:
            logging.error("TCP connections not implemented")
            raise NotImplementedError("TCP connections not implemented")

        # TODO: allow re-establishing dropped connections
        try:
            socket_path = self.config['bbsd']['socket']
            reader, writer = await asyncio.open_unix_connection(socket_path)
            logging.debug(f"Using bbsd socket {socket_path}")
            self.connection = (reader, writer)

            # This task parses incoming text from the connection.
            create_task(self.handle_bbsd_connection())

            # A separate task handles messages received from bbsd. (this is
            # under review for merging with the previous task)
            create_task(self.receive_bbsd_messages())

            return reader, writer

        except asyncio.CancelledError:
            raise

        except Exception as e:
            logging.exception(f"Failed to connect to bbsd.")
            sys.exit(1)

    async def handle_bbsd_connection(self):
        reader, writer = self.connection

        # Be nice, say hello upon connecting.
        hello = dict(op="hello", tty=self.channel.name, pid=os.getpid())
        writer.write((json.dumps(hello) + "\n").encode("utf-8"))
        await writer.drain()
        logging.debug("Said hello: {hello}")

        try:
            while not reader.at_eof():
                line = await reader.readline()
                #logging.debug(f"Received {line}")

                # Attempt to decode it.
                message = line.decode().strip()
                message = message.strip()

                if not message:
                    continue

                try:
                    data = json.loads(message)
                    logging.debug(f"JSON decoded correctly: {data}")

                    # What type of message is it?
                    if 'ok' in data:
                        await self.response_queue.put(data)
                    elif 'ts' in data:
                        await self.pub_queue.put(data)

                except json.decoder.JSONDecodeError as e:
                    response = dict(ok=False, err=repr(e))
                    logging.error(f"{conn}: JSON decoding error: {e!r}")

            if reader.at_eof():
                # TODO: attempt to re-establish connection
                logging.critical("bbsd connection failed.")
                sys.exit(1)

        except asyncio.CancelledError:
            writer.close()
            raise

        except Exception as e:
            logging.exception(f"bbsd command {command} failed to execute")


    async def receive_bbsd_messages(self):
        reader, writer = self.connection
        
        # TODO: make this do some actual work. Somehow.
        try:
            while True:
                msg = await self.pub_queue.get()
                logging.debug("bbsd said: {msg}")

        except asyncio.CancelledError:
            writer.close()
            raise

        except Exception as e:
            logging.exception(f"receive_bbsd_messages(): {e}")
            raise


    async def send(self, op, **kwargs):
        reader, writer = self.connection

        command = dict(op=op)
        command.update(kwargs)

        command_str = json.dumps(command, separators=(',',':')) + "\n"

        writer.write(command_str.encode("utf-8"))
        await writer.drain()

        # if self.bbsd_keepalive is not None:
        #     self.bssd_keepalive.cancel()
        # self._mainloop.call_later(3, self.bbsd_command("ping"))

        response = await self.response_queue.get()
        logging.debug(f"Got response: {response}")

        return response


    async def set_channel_state(self, state, desc=None, errors=False, **kwargs):
        """Update the state of the channel. `state` must be one of the constants in
        megistos.channel."""
        topic = f"channel/{self.channel.name}/state"
        payload = dict(state=state, desc=desc, errors=errors)
        payload.update(**kwargs)
        return await self.send("pub", t=topic, d=payload)


# End of file.
