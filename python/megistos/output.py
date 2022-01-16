#!/usr/bin/python3

import re
import os
import sys
import tty
import logging
import codecs

from attr import define, field


from . import config as megistos_config


STARTED = "started"             # Session manager started
INIT    = "init"                # Initialising modem
READY   = "ready"               # Ready and waiting for call
ANSWER  = "answer"              # Incoming call being answered (ATA)
CARRIER = "carrier"             # Call connected (CONNECT)
LOGIN   = "login"               # Session started, now at bbslogin.
FAILED  = "fail"                # Failed to start session
CLEARED = "cleared"             # Connection cleared (session ended)


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


    def set_encoding(self, encoding):
        """Instruct the bbssession handler to change the encoding."""
        sys.stdout.flush()
        os.write(1, b"\033\001\001" + encoding.encode("us-ascii") + b"\001")


# End of file.
