#!/usr/bin/python3
#
# Exception-logging version of asyncio.create_task()
#
# It was found here:
#
# https://quantlane.com/blog/ensure-asyncio-task-exceptions-get-logged/

import sys

import asyncio
import functools
import logging


def create_task(coroutine, loop=None, **kwargs):
    """
    This helper function wraps a ``loop.create_task(coroutine())`` call and ensures there is
    an exception handler added to the resulting task. If the task raises an exception it is logged
    using the provided ``logger``, with additional context provided by ``message`` and optionally
    ``message_args``.
    """
    if loop is None:
        obj = asyncio
    else:
        obj = loop
    task = obj.create_task(coroutine, **kwargs)
    task.add_done_callback(
        functools.partial(_handle_task_result)
    )
    return task


def _handle_task_result(task):
    try:
        task.result()
    except asyncio.CancelledError:
        pass  # Task cancellation should not be logged as an error.
    # Ad the pylint ignore: we want to handle all exceptions here so that the result of the task
    # is properly logged. There is no point re-raising the exception in this callback.
    except Exception:  # pylint: disable=broad-except
        logging.exception("Caught unhandled exception")
        sys.exit(1)
    

# End of file.
