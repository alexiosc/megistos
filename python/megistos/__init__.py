#!/usr/bin/python3

import argparse

from . import logging
from .task_logger import create_task

class MegistosProgram:
    def __init__(self):
        logging.init()

    def create_command_line_parser(self, *args, **kwargs):
        parser = argparse.ArgumentParser(*args, **kwargs)

        parser.add_argument("-c", "--config", metavar="PATH",
                            type=str, default="bbsd.yaml",
                            help="""Specify configuration file. (default: %(default)s)""")

        return parser


# End of file.
