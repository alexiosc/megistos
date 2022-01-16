#!/usr/bin/python3

import re
import os
import sys
import tty
import logging
import codecs

from attr import define, field


from . import config as megistos_config

# bbssession command opcodes
BBSS_SET_ENCODING = 1
BBSS_TEXT = 2
BBSS_BINARY = 3


@define(kw_only=True)
class Channel(object):
    name: str        = field()
    group_name: str  = field()
    dev: str         = field()
    config: dict     = field(repr=False)
    modem_type: str  = field()
    modem_def: dict  = field(repr=False)


class OutputEngine(object):
    def __init__(self, config):
        self.config = config
        tty.setraw(0)


    def _bbssession_command(self, opcode, payload=None):
        """Send out a bbssession in-band command. These look like terminal
        escape sequences, and follow the form:

        ESC \x01 <OPCODE> [ <PAYLOAD> ] \x01

        They must be sent to bbssession as a single, atomic
        transaction so we use flush the output buffers first, and send
        out the data packet unbuffered.
        """
        sys.stdout.flush()
        op_byte = opcode.to_bytes(1, 'big') # byte order meaningless here
        if payload is None:
            os.write(1, b"\033\001" + op_byte + b"\001")
        else:
            payload_bytes = payload.encode("us-ascii")
            os.write(1, b"\033\001" + op_byte + payload_bytes + b"\001")


    def set_encoding(self, encoding):
        """Instruct the bbssession handler to change the encoding. Also
        enables transcoding implicitly."""
        self._bbssession_command(BBSS_SET_ENCODING, encoding)


    def text_mode(self, state):
        """Enable transcoding of characters."""
        self._bbssession_command(BBSS_TEXT)


    def binary_mode(self, state):
        """Disable transcoding when e.g. binary transmissions are happening."""
        sys.stdout.flush()
        self._bbssession_command(BBSS_BINARY)


# End of file.
