#!/usr/bin/python3


import logging


def init(level=logging.INFO):
    logging.basicConfig(
        #level=logging.INFO,
        level=logging.DEBUG,
        format="%(asctime)s bbsd[%(process)d] %(levelname)s: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

# End of file.
