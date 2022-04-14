#!/usr/bin/python3

import os
import sys
import argparse

from . import logging
from . import channels
from .task_logger import create_task

class MegistosProgram:

    BASEDIR = "."
    BINDIR = "."
    
    def __init__(self):
        self.PROGNAME = os.path.splitext(os.path.basename(sys.argv[0]))[0]
        self.log = logging.init(self.PROGNAME)


    def init_module(self):
        """Initialise a Megistos module."""
        #self.output = asyncio.Queue()


    def init_channels(self, dev=None):
        """Load the channel definitions, and find out what our own channel
        is. If dev is not supplied, look for the channel in
        environment variable MEG_DEV.
        """

        if dev is None:
            try:
                dev = os.environ["MEG_DEV"]
            except KeyError:
                logging.critical(f"Environmeng variable MEG_DEV is not set.")
                self.fail()

        # TODO: Add a method to load configuration so self.config makes sense.
        self.channels = channels.Channels(config=self.config)
        self.channel = self.channels.dev_path_to_channel(dev)
        if self.channel is None:
            logging.critical(f"No channel matched device '{self.args.dev}'")
            self.fail()


    def create_command_line_parser(self, *args, **kwargs):
        parser = argparse.ArgumentParser(*args, **kwargs)

        parser.add_argument("-c", "--config", metavar="PATH",
                            type=str, default="bbsd.yaml",
                            help="""Specify configuration file. (default: %(default)s)""")

        return parser


# End of file.
