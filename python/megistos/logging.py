#!/usr/bin/python3


import logging


def init(progname=None, level=logging.INFO):
    logging.basicConfig(
        #level=logging.INFO,
        level=logging.DEBUG,
        format=f"%(asctime)s {progname}[%(process)d] %(levelname)s: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

# End of file.
