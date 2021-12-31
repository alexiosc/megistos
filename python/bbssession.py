#!/usr/bin/env python3

import os
import sys
import tty
import ctypes
import pty
import json
import asyncio
import signal
import logging
import termios
import struct
import fcntl


from megistos import MegistosProgram
from megistos import config
import megistos.logging
import megistos.channels
import megistos.validation


class BBSSession(MegistosProgram):
    """
    This program replaces a lot of the older functionality of a channel handler:
    
    * bbsgetty
    * bbslogin
    * emud
    * the bash session loop
    """

    DESCRIPTION = "Megistos Session handler"

    def __init__(self):
        super().__init__()

        self.parse_command_line()

        # Read the configuration, keep only the bbsd section.
        self.config = config.read_config(self.args.config, config.BBSD_CONFIG_SCHEMA)
        # import pprint
        # pprint.pprint(self.config, width=200)
        # sys.exit(0)

        self.pub_queue = asyncio.Queue()
        self.response_queue = asyncio.Queue()
        #self.bbsd_keepalive = None


    def parse_command_line(self):
        parser = self.create_command_line_parser(description=self.DESCRIPTION)

        parser.add_argument("-d", "--dev", metavar="DEVICE-PATH",
                            type=str, default=os.ttyname(sys.stdin.fileno()),
                            help="""Override the device path (with or without the
                            "/dev/" component) this session is running on. This
                            will determine the channel type and name/number and
                            set various defaults. (default: the name of this
                            TTY, %(default)s)""")

        self.args = parser.parse_args()

        # Early sanity checks
        if not os.isatty(sys.stdin.fileno()) or \
           not os.isatty(sys.stdout.fileno()):
            parser.error("Standard input and output must both be TTYs.")
        
        return self.args


    def handle_exception(self, loop, context):
        msg = context.get("exception", context["message"])
        # if 'exception' in context:
        #     print(type(context['exception']))
        #     # import traceback
        #     # print(traceback.format_exc(context['exception']))
        logging.critical(f"Caught exception: {msg}")
        logging.info("Shutting down...")
        asyncio.create_task(self.shutdown(loop))


    async def shutdown(self, loop, signal=None):
        """Cleanup tasks tied to the service's shutdown."""
        if signal:
            logging.info(f"Received exit signal {signal.name}...")
        tasks = [t for t in asyncio.all_tasks() if t is not
                 asyncio.current_task()]

        #await asyncio.gather(*tasks, return_exceptions=True)
        #logging.info(f"Flushing metrics")
        loop.stop()


    def terminal_resized(self):
        """Handle the WINCH signal, issued when the terminal emulator window
        has changed size.  Pass this onto the session.
        """
        try:
            cols, rows = os.get_terminal_size()
            if cols > 0 and rows > 0:
                winsize = struct.pack("HHHH", rows, cols, 0, 0)
                logging.debug(f"\r\n\033[0;7mResizing terminal to {cols}×{rows}\033[0m\r\n")
                fcntl.ioctl(self.pty_fd, termios.TIOCSWINSZ, winsize)
        except Exception as e:
            logging.debug(f"Failed to updated terminal window size: {e}")


    def run(self):
        # Get the channel name.
        # self.tty_name = self.args.dev
        # if self.tty_name is None:
        #     self.tty_name = os.ttyname(sys.stdin.fileno())

        chan = megistos.channels.Channels(config=self.config)
        logging.info(chan.dev_path_to_channel(self.args.dev))
        sys.exit(0)

        logging.info(f"Started session on {self.channel_name}")

        self._mainloop = loop = asyncio.get_event_loop()
        signals = (signal.SIGHUP, signal.SIGTERM, signal.SIGINT)
        for s in signals:
            loop.add_signal_handler(
                s, lambda s=s: asyncio.create_task(self.shutdown(loop, signal=s)))
        loop.add_signal_handler(signal.SIGWINCH, self.terminal_resized)
        loop.set_exception_handler(self.handle_exception)

        try:
            # loop.create_task(self.handle_bbsd_connection())
            # loop.create_task(self.receive_bbsd_messages())
            loop.create_task(self.ticks())
            loop.create_task(self.session())
            loop.add_reader(sys.stdin.fileno(), self.handle_fd_read, sys.stdin.fileno())
            #loop.add_writer(sys.stdout.fileno(), self.handle_fd_write, sys.stdout.fileno())
            #loop.run_until_complete(self.session())
            loop.run_forever()

        finally:
            loop.close()
            logging.info("Done.")


    async def ticks(self):
        while True:
            await asyncio.sleep(3)
            logging.debug("Tick!")
            # for x in asyncio.all_tasks():
            #     logging.debug(f"  running task: {x.cancelled():<5} {x.get_coro()}")


    async def bbsd_command(self, op, **kwargs):
        reader, writer = self.bbsd_connection
    
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


    async def connect_to_bbsd(self):
        # TODO: allow re-establishing dropped connections
        try:
            # TODO: Implement TCP too.
            socket_path = self.config['bbsd']['socket']
            reader, writer = await asyncio.open_unix_connection(socket_path)
            logging.debug(f"Using bbsd socket {socket_path}")
            self.bbsd_connection = (reader, writer)

            # And add a handler for bbsd dialogue to the main loop
            self._mainloop.create_task(self.handle_bbsd_connection())

            return reader, writer

        except asyncio.CancelledError:
            raise

        except Exception as e:
            logging.exception(f"Failed to connect to bbsd.")
            sys.exit(1)


    async def handle_bbsd_connection(self):
        reader, writer = self.bbsd_connection

        # Be nice, say hello upon connecting.
        hello = dict(op="hello", tty=self.channel_name, pid=os.getpid())
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
                        asyncio.create_task(self.response_queue.put(data))
                    elif 'ts' in data:
                        asyncio.create_task(self.pub_queue.put(data))

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


    def handle_fd_read(self, fd):
        data = os.read(fd, 8192)
        if fd == 0:
            os.write(self.pty_fd, data)
        if fd == 7:
            sys.stdout.write(data.decode("utf-8"))
            sys.stdout.flush()
        # else:
        #     logging.debug(f"INPUT AVAILABLE: fd={fd}, data=\"{data}\"")


    def handle_fd_write(self, fd):
        pass


    async def session(self):
        logging.info("Session started")

        await self.connect_to_bbsd()
        # ..

        # master, slave = pty.openpty()
        # logging.debug(f"PTYs: {master}, {slave}")
        # tty.setraw(master)
        # tty.setraw(slave)

        # Initialize the terminal size
        try:
            cols, rows = os.get_terminal_size()
            assert cols > 0 and rows > 0
        except:
            cols, rows = 80, 24 # Sane defaults if this didn't work.

        pid, fd = os.forkpty()

        # Try to get the slave PTS name. Python doesn't yet have an
        # os.ptsname() function, so we have to call the libc one directly.
        try:
            import ctypes
            libc6 = ctypes.CDLL('libc.so.6')
            ptsname = libc6.ptsname
            ptsname.restype = ctypes.c_char_p
            logging.debug(f"ptsname({fd}) = {ptsname(fd)}")

        except Exception as e:
            logging.debug(f"Failed to get pts name: {e}")
                
        self.pty_fd = fd

        logging.debug(f"({pid},{fd})")
        if pid == 0:
            print(f"PID={os.getpid()}: exec(2) /bin/bash... Terminal size is {cols}x{rows}")
            try:
                winsize = struct.pack("HHHH", rows, cols, 0, 0)
                fcntl.ioctl(0, termios.TIOCSWINSZ, winsize)
            except Exception as e:
                print(e)
            sys.stdout.flush()
            sys.stderr.flush()
            os.execvp("/bin/bash", ["bash", "--login"])
            # The child process never gets to this line.

        else:
            tty.setraw(0, when=termios.TCSANOW)

        logging.debug(f"Child PID is {pid}, PTY FD is {fd}")

        self._mainloop.add_reader(fd, self.handle_fd_read, fd)
        #self._mainloop.add_writer(fd, self.handle_fd_write, fd)


if __name__ == "__main__":
    BBSSession().run()
