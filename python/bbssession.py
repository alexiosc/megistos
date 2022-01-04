#!/usr/bin/env python3

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


import megistos.logging
import megistos.channels
import megistos.validation
from megistos import MegistosProgram
from megistos import config
from megistos.bbsgetty import BBSGetty
from megistos.bbsd_client import BBSDClient


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

        self.bbsd = None
        self.channel = None

        self.parse_command_line()

        # Read the configuration, keep only the bbsd section.
        self.config = config.read_config(self.args.config, config.CONFIG_SCHEMA)
        # import pprint
        # pprint.pprint(self.config, width=200)
        # sys.exit(0)

        # No BBSGetty for now. We'll initialise one if needed.
        self.bbsgetty = None


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
        if 'exception' in context:
            print(type(context['exception']))
            import traceback
            print(traceback.format_exc(context['exception']))

        logging.critical(f"Caught exception: {msg}")
        logging.info("Shutting down...")
        asyncio.create_task(self.shutdown(loop, failure_msg=msg))


    async def shutdown(self, loop, signal=None, failure_msg=None):
        """Cleanup tasks tied to the service's shutdown."""

        # Try to update the channel status. Ignore all exceptions at this point.
        # if self.bbsd is not None and self.channel is not None:
        #     try:
        #         coroutine = self.bbsd.set_channel_state(
        #             megistos.channels.FAILED,
        #             desc=failure_msg,
        #             errors=True)
        #         task = asyncio.create_task(coroutine, timeout=1)
        #         await asyncio.gather(task)
        #     except:
        #         pass
        
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
                #logging.debug(f"\r\n\033[0;7mResizing terminal to {cols}×{rows}\033[0m\r\n")
                fcntl.ioctl(self.pty_fd, termios.TIOCSWINSZ, winsize)
        except Exception as e:
            logging.debug(f"Failed to updated terminal window size: {e}")


    def init_channels(self):
        """Load the channel definitions, and find out what our own channel is."""
        self.channels = megistos.channels.Channels(config=self.config)
        self.channel = self.channels.dev_path_to_channel(self.args.dev)
        if self.channel is None:
            logging.critical(f"No channel matched device '{self.args.dev}'")
            sys.exit(1)


    ###############################################################################
    #
    # MAIN CODE
    #
    ###############################################################################

    def init_mainloop(self):
        loop = asyncio.get_event_loop()
        signals = (signal.SIGHUP, signal.SIGTERM, signal.SIGINT)
        for s in signals:
            loop.add_signal_handler(
                s, lambda s=s: asyncio.create_task(self.shutdown(loop, signal=s)))
        loop.set_exception_handler(self.handle_exception)
        return loop
        

    def run(self):
        # Get the channel name.
        # self.tty_name = self.args.dev
        # if self.tty_name is None:
        #     self.tty_name = os.ttyname(sys.stdin.fileno())

        # Initialise the main loop
        self._mainloop = loop = self.init_mainloop()

        # Initialise other stuff
        self.init_channels()

        loop.add_signal_handler(signal.SIGWINCH, self.terminal_resized)

        try:
            loop.add_reader(sys.stdin.fileno(), self.handle_fd_read, sys.stdin.fileno())

            loop.create_task(self.ticks())
            loop.create_task(self.session())

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


    def handle_fd_read(self, fd):
        data = os.read(fd, 40)
        if fd == 0:

            # If BBSGetty is still running, send all line traffic to it.
            if self.bbsgetty is not None and self.bbsgetty.done == False:
                asyncio.create_task(self.bbsgetty.input.put(data))
            else:
                os.write(self.pty_fd, data)

        if fd == 7:
            sys.stdout.write(data.decode("utf-8"))
            sys.stdout.flush()
        # else:
        #     logging.debug(f"INPUT AVAILABLE: fd={fd}, data=\"{data}\"")


    # def handle_fd_write(self, fd):
    #     pass


    async def session(self):
        # Connect to BBSD.
        self.bbsd = BBSDClient(self.config, self.channel, self._mainloop)
        await self.bbsd.connect()

        # We'll need a BBSGetty. Let it decide if it needs to do
        # anything for this channel.
        self.bbsgetty = BBSGetty(self.config, self.bbsd, self.channel)
        await self.bbsgetty.run()

        # Session started
        logging.info(f"Started session on {self.channel.name} ({self.channel.group_name})")
        await self.bbsd.set_channel_state(megistos.channels.LOGIN, data=self.bbsgetty.data)

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
            #logging.debug(f"ptsname({fd}) = {ptsname(fd)}")

        except Exception as e:
            logging.debug(f"Failed to get pts name: {e}")

        self.pty_fd = fd

        #logging.debug(f"({pid},{fd})")
        if pid == 0:
            #print(f"PID={os.getpid()}: exec(2) /bin/bash... Terminal size is {cols}x{rows}")
            try:
                winsize = struct.pack("HHHH", rows, cols, 0, 0)
                fcntl.ioctl(0, termios.TIOCSWINSZ, winsize)
            except Exception as e:
                logging.warning(f"Failed to set pseudoterminal size to {cols}x{rows}: {e}")

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
