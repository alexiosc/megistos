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
    # BBSGETTY FUNCTIONALITY
    #
    ###############################################################################

    def bbsgetty_hangup_tty(self, fd):
        """Use termios to hang up a TTY."""
        t = termios.tcgetattr(fd)
        # Set the line speed to 0 to hangup. Use OS bitfields.
        t[2] &= ~termios.CBAUD # Clear the speed flags in cflags
        t[2] |= termios.B0     # Set the B0 value in cflags
        t[4] = termios.B0      # Also in ispeed (for good measure)
        t[5] = termios.B0      # And ospeed
        termios.tcsetattr(fd, termios.TCSANOW, t)

        # Verify it was done.
        t1 = termios.tcgetattr(fd)
        try:
            assert t1[2] & termios.CBAUD == termios.B0
            assert t1[4] == termios.B0
            assert t1[5] == termios.B0
        except:
            logging.error("Line hangup failed; ignoring and hoping for the best.")


    def bbsgetty_config_tty(self, fd, specs):
        """Use termios to configure a TTY."""

        # No specs, no work.
        if not specs:
            return
        
        iflags = re.compile(r'^-?(IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK|ISTRIP|INLCR|IGNCR|ICRNL|IUCLC|IXON|IXANY|IXOFF|IMAXBEL|IUTF8)$')
        oflags = re.compile(r'^-?(OPOST|OLCUC|ONLCR|OCRNL|ONOCR|ONLRET|OFILL|OFDEL)$')
        cflags = re.compile(r'^-?(CSTOPB|CREAD|PARENB|PARODD|HUPCL|CLOCAL|LOBLK|CMSPAR|CRTSCTS)$')
        lflags = re.compile(r'^-?(ISIG|ICANON|XCASE|ECHO(|E|K|NL|CTL|PRT|KE)|DEFECHO|NOFLSH|TOSTOP|PENDIN|IEXTEN)$')

        cbaud = ["B50", "B75", "B110", "B134", "B150", "B200", "B300", "B600",
                 "B1200", "B1800", "B2400", "B4800", "B9600", "B19200",
                 "B38400", "B57600", "B115200", "B230400", "B460800",
                 "B500000", "B576000", "B921600", "B1000000", "B1152000",
                 "B1500000", "B2000000", "B2500000", "B3000000", "B3500000",
                 "B4000000"]

        cbits = ["CS5", "CS6", "CS7", "CS8"]

        # These are bit field values (like cbaud) with associated bitmasks.
        ofields = re.compile(r'^(NL[01]|CR[0-3]|TAB[0-3]|BS[01]|VT[01]|FF[01])')
        omasks = dict(
            NL=[ termios.NLDLY ],
            CR=[ termios.CRDLY ],
            TA=[ termios.TABDLY ],
            BS=[ termios.BSDLY ],
            VT=[ termios.VTDLY ],
            FF=[ termios.FFDLY ],
        )

        def lookup(name):
            try:
                x = termios.__dict__[name.upper()]
                assert type(x) == int
                return x
            except:
                logging.critical(f"'{name}' is not a termios flag known to this OS. Check man page termios(3)!")
                sys.exit(1)


        def process_flag(bitfield, spec):
            clear, name = False, spec
            if spec[0] == '-':
                clear, name = True, spec[1:]

            value = lookup(name)

            if clear:
                return bitfield & ~value
            else:
                return bitfield | value


        def process_masked_value(bitfield, spec):
            name = spec.upper()
            value = lookup(name)

            try:
                mask = omasks[name[:2]]
            except KeyError:
                logging.critical(f"Don't know how to handle flag '{name}'.")
                sys.exit(1)

            return (bitfield & ~mask) | value


        # Start with our existing flags. Let specs turn them on or off (or modify them).
        t = termios.tcgetattr(fd)

        # Also disable line buffering and go to non-canonical mode.
        t[3] &= termios.ICANON
        t[6][termios.VMIN] = 1
        t[6][termios.VTIME] = 0

        for spec in specs:
            logging.debug(f"Processing spec {spec}")

            if iflags.match(spec):
                logging.debug(f"iflags: {t[0]:>032b}")
                t[0] = process_flag(t[0], spec)
                logging.debug(f"iflags: {t[0]:>032b} {spec}")
                    
            if oflags.match(spec):
                logging.debug(f"oflags: {t[1]:>032b}")
                t[1] = process_flag(t[1], spec)
                logging.debug(f"oflags: {t[1]:>032b} {spec}")
                    
            if cflags.match(spec):
                logging.debug(f"cflags: {t[2]:>032b}")
                t[2] = process_flag(t[2], spec)
                logging.debug(f"cflags: {t[2]:>032b} {spec}")
                    
            if lflags.match(spec):
                logging.debug(f"lflags: {t[3]:>032b}")
                t[3] = process_flag(t[3], spec)
                logging.debug(f"lflags: {t[3]:>032b} {spec}")

            # Handle speed specs
            if spec in cbaud:
                logging.debug(f"cflags: {t[2]:>032b}")
                t[2] &= ~termios.CBAUD
                x = lookup(spec)
                t[2] |= x
                t[4] = x
                t[5] = x
                logging.debug(f"cflags: {t[2]:>032b} {spec}")

            # Handle bit specs
            if spec in cbits:
                logging.debug(f"cflags: {t[2]:>032b}")
                t[2] &= ~termios.CSIZE
                t[2] |= lookup(spec)
                logging.debug(f"cflags: {t[2]:>032b} {spec}")

            # Handle oflag delay specifications
            if ofields.match(spec):
                logging.debug(f"oflags: {t[1]:>032b}")
                t[1] = process_masked_value(t[2], spec)
                logging.debug(f"oflags: {t[1]:>032b} {spec}")

        termios.tcsetattr(fd, termios.TCSANOW, t)


    async def bbsgetty_run_script(self, script):
        pass


    async def bbsgetty_init_modem(self, script):
        if not script:
            logging.info("This modem has no initialisation script, skipping init.")
            return

        logging.info("Initialising modem.")
        await self.bbsgetty_run_script(script)


    async def bbsgetty_answer_call(self):
        pass


    async def bbsgetty(self):
        """Initialise the channel and wait for an incoming call. On channels without
                   modems, this method returns immediately."""

        # No modem definition; no hassle.
        if self.channel.modem_def is None:
            return

        mdef = self.channel.modem_def

        logging.info(f"bbsgetty starting, device {self.channel.dev}, type {self.channel.modem_type}.")

        # Hangup on startup?
        if mdef.get("hangup_on_startup", True):
            self.bbsgetty_hangup_tty(0)

        # Initialise the line.
        self.bbsgetty_config_tty(0, mdef.get("initial"))

        # Initialise the modem.
        await self.bbsgetty_init_modem(mdef.get("init_script"))
        logging.info(f"Modem initialised, waiting for calls.")
        #run_script(mdef.get("init_script", []))

        # Wait for a ring, answer, and connect
        await self.bbsgetty_answer_call()
        logging.info(f"Connected.")

        # Add the session loop now.
        self._mainloop.create_task(self.session())


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
            # loop.create_task(self.handle_bbsd_connection())
            # loop.create_task(self.receive_bbsd_messages())

            loop.create_task(self.ticks())
            loop.create_task(self.bbsgetty())

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
        logging.info(f"Started session on {self.channel.name} ({self.channel.group_name})")

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
