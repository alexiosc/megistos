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


from . import channels


class BBSGetty(object):
    """The BBSGetty is a module that replaces the original C-based bbsgetty
    program, itself a fork of the venerable but modem-oriented uugetty.
    
    It's responsible for initialising a modem and waiting for a connection.
    """

    def __init__(self, config, bbsd, channel):
        # The configuration dict.
        self.config = config

        # We'll need to talk to bbsd, so also keep tabs on its client object.
        self.bbsd = bbsd

        # And we'll need access to the channel structure.
        self.channel = channel

        # Input from the modem will be queued here.
        self.input = asyncio.Queue()

        # We store data captured from the modem scripts (e.g. baud rate, caller
        # ID) here.
        self.data = dict()

        # Our state
        self.done = False


    def _compile_script(self, script):
        newscript = []
        for i, instr in enumerate(script, 1):
            opcode, arg = list(instr.items())[0]
            if opcode == "expect":
                try:
                    arg = re.compile(arg)
                except re.error as e:
                    # The caller will make this more meaningful.
                   raise re.error(f"script line {i} (\"{arg}\"): {e}")
            # Note: we change from a singleton dict to a tuple. Much n icer.
            newscript.append((opcode, arg))
        return newscript


    def compile_scripts(self):
        """Compile (and sanity-check) the init and answer scripts."""
        for key in ["init_script", "answer_script"]:
            if key in self.channel.modem_def:
                old_script = self.channel.modem_def[key]
                try:
                    self.channel.modem_def[key] = self._compile_script(old_script)
                except Exception as e:
                    logging.critical(f"While parsing {key}: {e}")
                    sys.exit(1)


    def hangup(self, fd):
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


    def config_tty(self, fd, specs):
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

        # And set some more sane defaults. These are mostly for when the TTY is
        # cooked during our session, which won't be often.
        t[6][termios.VINTR] = termios.CINTR
        t[6][termios.VQUIT] = termios.CQUIT
        t[6][termios.VERASE] = termios.CERASE
        t[6][termios.VWERASE] = termios.CWERASE
        t[6][termios.VKILL] = termios.CKILL
        t[6][termios.VEOF] = termios.CEOF
        t[6][termios.VSTOP] = termios.CSTOP
        t[6][termios.VSTART] = termios.CSTART
        t[6][termios.VSUSP] = termios.CSUSP

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


    async def run_script(self, script, timeout=5):
        linebreaker = re.compile(b"^(.*)[\r\n]+(.*)")

        for opcode, arg in script:
            if opcode == "expect":
                str_arg = arg.pattern # The argument is a regexp.
            else:
                str_arg = str(arg)
            logging.debug("Executing script instruction: {} {}".format(opcode, str_arg))
            if opcode == "timeout":
                timeout = int(arg)
            elif opcode == "wait":
                await asyncio.sleep(arg)
            elif opcode == "send":
                process_arg = arg.encode("utf-8").decode("unicode_escape")
                os.write(1, process_arg.encode("utf-8"))
            elif opcode == "expect":
                try:
                    text = b''
                    while True:
                        # Wait for text, allow for timeouts.
                        recv_chars = await asyncio.wait_for(self.input.get(), timeout=timeout)
                        #logging.debug(f"modem said: {recv_chars}")
                        text += recv_chars
                        # TODO: remove this
                        if b'\003' in text:
                            os.system("stty sane")
                            sys.exit(0)

                        # Process line by line
                        if b'\n' not in text and b'\r' not in text:
                            continue

                        while True:
                            m = linebreaker.match(text)
                            if not m: # Sanity
                                break

                            line, text = m.groups()
                            logging.debug(f"Match. Groups: {line}, {text}")

                            # Attempt to match the pattern.
                            m = arg.search(line.decode("utf-8"))
                            if m:
                                g = m.groupdict()
                                self.data.update(g)
                                logging.debug(f"Found! Regexp groups: {json.dumps(g)}")
                                logging.debug(f"Data gathered so far: {json.dumps(self.data)}")
                                assert False, "Go to next isntruction"
                                sys.exit(0)

                except AssertionError:
                    # Abused to break to next script instruction.
                    continue

                except asyncio.TimeoutError:
                    logging.error(f"Timed out after {timeout}s. Script failed.")
                    return False

                except asyncio.CancelledError:
                    raise
        
                except Exception as e:
                    logging.exception(f"bbsgetty.run_script(): {e}")
                    raise

        return True


    async def init_modem(self, script):
        if not script:
            logging.debug("This modem definition has no initialisation script, skipping init.")
            return

        logging.info("Initialising modem.")
        res = await self.run_script(script)
        if res:
            logging.info("Modem initialised.")
        else:
            logging.critical("Failed to initialise modem, bailing out.")
            sys.exit(1)


    async def wait_for_call(self, script):
        if not script:
            logging.debug("This modem definition has no answer script, won't wait.")
            return

        # Wait for a call. Time out (and re-initialise modem) after two minutes.
        logging.info("Waiting for incoming call...")
        res = await self.run_script(script, timeout=120)
        if res:
            logging.info("Call connected!")
            return True
        else:
            return False


    def update_baud(self, fd):
        """Update the baud rate of the TTY based on any speed hints we got from the
        modem CONNECT xxxx string (or otherwise, depending on answer
        script. Reconfigure the TTY accordingly. On failure, log this as an
        error but proceed anyway.
        """

        # What's the current TTY speed? Introspect termios to find out.
        t = termios.tcgetattr(fd)
        ospeed = t[5]
        bps = None
        for sym in dir(termios):
            if sym[0] != "B":
                continue
            try:
                bps = int(sym[1:])
            except:
                continue
            if termios.__dict__.get(sym) == ospeed:
                break
        if bps is None:
            logging.warning(f"Internal error: failed to get the current output speed of this line (ospeed was {ospeed}).")
        else:
            logging.debug(f"Current speed is {bps} bps (symbol termios.{sym})")

        speed_bps = self.data.get('speed_bps')
        if speed_bps is None or speed_bps == 0:
            logging.error("bps_lock is False, but incoming_call_script didn't detect the connection speed for us to set! Leaving it as-is.")
            return
        else:
            try:
                bps = int(speed_bps)
                sym = "B" + str(bps)
                # All pre MNP modems that require setting the bps rate here
                # will report a standard modem speed. And anyway, if the OS
                # doesn't know this speed, we can't really set it here.
                if sym not in termios.__dict__:
                    logging.critical(f"Speed {bps} is not supported. There is no symbol termios.{sym}!")
                    sys.exit(1)

                val = termios.__dict__[sym]

                t[2] &= ~termios.CBAUD # c_flags
                t[2] |= val
                t[4] = val             # ispeed
                t[5] = val             # ospeed

                termios.tcsetattr(fd, termios.TCSANOW, t)
                logging.info(f"Setting connection speed to {bps} (symbol termios.{sym} = {val})")

            except Exception as e:
                logging.critical(f"Failed to set speed!")
                raise
        

    async def run(self):
        """Initialise the channel and wait for an incoming call. On channels without
        modems, this method returns after performing minimal setup.
        """
        # Tell bbsd a session is awake and initialising.
        await self.bbsd.set_channel_state(channels.STARTED)

        # No modem definition; no hassle.
        if self.channel.modem_def is None:
            self.done = True
            return

        mdef = self.channel.modem_def

        logging.info(f"bbsgetty starting, device {self.channel.dev}, type {self.channel.modem_type}.")

        # Verify the regular expressions in the scripts, and error out now, while it's still early.
        self.compile_scripts()

        # Hangup on startup?
        if mdef.get("hangup_on_startup", True):
            self.hangup(0)

        # Initialise the line.
        tty.setraw(0, when=termios.TCSANOW) # Start off with a raw TTY.
        self.config_tty(0, mdef.get("initial_tty_config"))

        # Initialise the modem.
        await self.bbsd.set_channel_state(channels.INIT)
        await self.init_modem(mdef.get("init_script"))
        logging.info(f"Modem initialised, waiting for calls.")
        #run_script(mdef.get("init_script", []))

        # Wait for a ring, answer, and connect
        await self.bbsd.set_channel_state(channels.READY)
        num_tries = 3
        for i in range(num_tries):
            # Execute the answer_script to wait for an incoming call and answer it
            script = mdef.get("answer_script")
            res = await self.wait_for_call(script)
            if res:
                break
            elif i + 1 < num_tries:
                logging.critical("Answer script failed. Trying again...")
            else:
                logging.critical("Answer script failed for the last time. Bailing out.")
                sys.exit(1)

        await self.bbsd.set_channel_state(channels.CARRIER)
        
        # Deallocate the bbsgetty input queue, and let the session handle input
        # from now on.
        del self.input
        self.input = False
        self.done = True

        # Do we need to update the bps?
        if not mdef.get("bps_lock", True):
            self.update_baud(0)

        # Reconfigure the TTY with the final settings.
        self.config_tty(0, mdef.get("final_tty_config"))


# End of file.
