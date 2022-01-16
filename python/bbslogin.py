#!/usr/bin/env python3

import asyncio
import fcntl
import logging
import os
import signal
import struct
import sys
import termios
import tty
import jinja2

import megistos.logging
import megistos.channels
import megistos.validation
import megistos.output
from megistos import MegistosProgram
from megistos import config
from megistos.bbsd_client import BBSDClient
from megistos.task_logger import create_task


class BBSLogin(MegistosProgram):
    """
    """

    DESCRIPTION = "Megistos Login/Signup"

    def __init__(self):
        super().__init__()
        self.init_module()

        self.bbsd = None
        self.channel = None
        self.done = False

        self.parse_command_line()

        # Read the configuration, keep only the bbsd section.
        self.config = config.read_config(self.args.config, config.CONFIG_SCHEMA)

        self.out = megistos.output.OutputEngine(self.config)

        self.old_termios = termios.tcgetattr(0)
        self._mainloop = None


    def parse_command_line(self):
        parser = self.create_command_line_parser(description=self.DESCRIPTION)

        parser.add_argument("-t", "--term", metavar="TERMINAL-TYPE",
                            type=str, default="ansi",
                            help="""Set the terminal type to use.
                            Terminal types are described in the
                            terminal_types: section of the
                            configuraiton. (default: %(default)s)""")

        self.args = parser.parse_args()

        # Early sanity checks
        if not os.isatty(sys.stdin.fileno()) or \
           not os.isatty(sys.stdout.fileno()):
            parser.error("Standard input and output must both be TTYs.")

        return self.args


    def handle_exception(self, loop, context):
        msg = context.get("exception", context["message"])

        logging.critical(f"Exception was never caught: {msg}")
        logging.info("Shutting down...")
        #create_task(self.shutdown(failure_msg=msg))


    def fail(self, exitcode=1):
        self._exitcode = exitcode
        if self._mainloop is not None:
            self._mainloop.create_task(self.shutdown())
        else:
            sys.exit(self._exitcode)


    async def _shutdown(self):
        self._mainloop.stop()


    async def shutdown(self, signal=None, failure_msg: str=None):
        """Cleanup tasks tied to the service's shutdown."""

        if failure_msg:
            logging.info("%s. Shutting down.", failure_msg)

        self.done = True

        if signal:
            logging.info(f"Received exit signal {signal.name}...")

        tasks = [t for t in asyncio.all_tasks() if t is not
                 asyncio.current_task()]

        for task in tasks:
            task.cancel()

        #await asyncio.gather(*tasks)
        #logging.info(f"Flushing metrics")
        asyncio.ensure_future(self._shutdown())


    def terminal_resized(self):
        """Handle the WINCH signal, issued when the terminal emulator window
        has changed size.  Pass this onto the session.
        """
        if self.pty_fd is None:
            return

        try:
            cols, rows = os.get_terminal_size()
            if cols > 0 and rows > 0:
                logging.debug(f"\r\n\033[0;7mResizing terminal to {cols}×{rows}\033[0m\r\n")
        except Exception as e:
            logging.debug(f"Failed to updated terminal window size: {e}")


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
                s, lambda s=s: create_task(self.shutdown(signal=s)))
        loop.set_exception_handler(self.handle_exception)
        return loop


    def run(self):
        try:
            # Initialise the main loop
            self._mainloop = loop = self.init_mainloop()

            # Initialise other stuff
            self.init_channels()

            self.out.set_encoding("utf-8")

            self.bbsd = BBSDClient(self.config, self.channel)

            loop.add_signal_handler(signal.SIGWINCH, self.terminal_resized)
            loop.add_reader(sys.stdin.fileno(), self.handle_fd_read, sys.stdin.fileno())

            create_task(self.ticks(), loop=loop)
            create_task(self.interact(), loop=loop)

            #loop.add_writer(sys.stdout.fileno(), self.handle_fd_write, sys.stdout.fileno())
            #loop.run_until_complete(self.session())
            loop.run_forever()

        except SystemExit as e:
            if self._mainloop is not None:
                loop.close()
            raise

        finally:
            if self._mainloop is not None:
                loop.close()
            if self._exitcode == 0:
                logging.info("Done.")
            sys.exit(self._exitcode)


    async def ticks(self):
        while True:
            await asyncio.sleep(5)
            #logging.debug("Tick!")
            # for x in asyncio.all_tasks():
            #     logging.debug(f"  running task: {x.cancelled():<5} {x.get_coro()}")


    def handle_fd_read(self, fd):
        if self.done:
            return

        try:
            data = os.read(fd, 8192)

        except OSError as e:
            if e.args[0] == 5:
                # Restore original termios settings
                termios.tcsetattr(0, termios.TCSAFLUSH, self.old_termios)

                logging.info("Session ended (server side).")
                create_task(self.shutdown(failure_msg="End of session"))
                return

        if fd == 0:
            os.write(1, data)

        # TODO: FIX THIS.
        if fd == 7:
            sys.stdout.write(data.decode("utf-8"))
            sys.stdout.flush()
        # else:
        #     logging.debug(f"INPUT AVAILABLE: fd={fd}, data=\"{data}\"")


    # def handle_fd_write(self, fd):
    #     pass


    async def interact(self):
        try:
            # Connect to BBSD.
            await self.bbsd.connect()


            x = """
            Hello, {{ something }}!
            """

            t = jinja2.Template(x)
            s = t.render(something="World φοο")
            print(s)
            
            sys.exit(0)


        except SystemExit as e:
            self.fail()
            return


if __name__ == "__main__":
    BBSLogin().run()
