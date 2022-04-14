#!/usr/bin/python3


import logging


logger = None
handler = None
fmt = None


def init(progname=None, level=logging.INFO):
    # if progname is None:
    #     progname = __name__

    global logger
    logger = logging.getLogger()
    #logger.setLevel(level)
    logger.setLevel(logging.DEBUG)

    # Add the stderr handler. Make it very quiet, unless there's an
    # error. Most normal modules will remove this handler soon after
    # initialisation (at init() time, the location and name of the
    # logfile may not yet be known, so we can't log directly to file.)
    global handler
    if handler is None:
        handler = logging.StreamHandler()
        handler.setLevel(logging.WARNING)

    global formatter
    formatter = logging.Formatter(
        f"%(asctime)s {progname}[%(process)d] %(levelname)s: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S")
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    # logging.basicConfig(
    #     #level=logging.INFO,
    #     level=logging.DEBUG,
    #     format=f"%(asctime)s {progname}[%(process)d] %(levelname)s: %(message)s",
    #     datefmt="%Y-%m-%d %H:%M:%S",
    # )

    return logger


def set_logfile(filename, keep_logging_to_stderr=False):
    global handler
    handler = logging.FileHandler(filename, encoding="utf-8")
    handler.setFormatter(formatter)

    if not keep_logging_to_stderr:
        logger.handlers = []

    logger.addHandler(handler)
    return handler


# End of file.
