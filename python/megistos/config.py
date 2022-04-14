#!/usr/bin/python3

import cerberus
import copy
import glob
import os
import sys
import yaml
import logging


BBSD_PORT = 8889

BBSD_SOCK = "/tmp/bbsd.sock"

TERMIOS_SCHEMA = {
    'anyof': [
        # c_iflag
        {'regex': r'^-?(IGNBRK|BRKINT|IGNPAR|PARMRK|INPCK|ISTRIP|INLCR|IGNCR|ICRNL|IUCLC|IXON|IXANY|IXOFF|IMAXBEL|IUTF8)$'},
        # c_oflag
        {'regex': r'^-?(OPOST|OLCUC|ONLCR|OCRNL|ONOCR|ONLRET|OFILL|OFDEL)$'},
        {'regex': r'^(NL[01]|CR[0-3]|TAB[0-3]|BS[01]|VT[01]|FF[01])'},
        # c_cflag
        {'allowed': ["B50", "B75", "B110", "B134", "B150", "B200", "B300",
                     "B600", "B1200", "B1800", "B2400", "B4800", "B9600",
                     "B19200", "B38400", "B57600", "B115200", "B230400",
                     "B460800", "B500000", "B576000", "B921600", "B1000000",
                     "B1152000", "B1500000", "B2000000", "B2500000",
                     "B3000000", "B3500000", "B4000000"]},
        {'allowed': ["CS5", "CS6", "CS7", "CS8"]},
        {'regex': r'^-?(CSTOPB|CREAD|PARENB|PARODD|HUPCL|CLOCAL|LOBLK|CMSPAR|CRTSCTS)$'},
        # c_lflag
        {'regex': r'^-?(ISIG|ICANON|XCASE|ECHO(|E|K|NL|CTL|PRT|KE)|DEFECHO|NOFLSH|TOSTOP|PENDIN|IEXTEN)$'},
    ],
}

INIT_SCRIPT_SCHEMA = {
    'schema': {
        'wait':    dict(type='float'),
        'send':    dict(type='string'),
        'expect':  dict(type='string'),
        'timeout': dict(type='integer', min=0.00001),
    }
}

CONFIG_SCHEMA = {
    'megistos': {
        'type': 'dict',
        'schema': {
            'log_dir':      dict(type='string', default='.'),
            'template_dir': dict(type='string', default='templates')
        }
    },
    'bbsd': {
        'type': 'dict',
        'schema': {
            'tick':     dict(type='integer', min=1, max=30, default=15),
            'socket':   dict(type='string', default=BBSD_SOCK),
            'tcp_addr': dict(type='string', default="127.0.0.1"),
            'tcp_port': dict(type='integer', min=1, max=65535, default=BBSD_PORT),
        }
    },

    'modems': {
        'type': 'dict',
        'valueschema': {
            'type': 'dict',
            'schema': {
                'bps_lock':             dict(type='boolean', default=True),
                'hangup_on_startup':    dict(type='boolean', default=True),
                'initial_tty_config':   dict(type='list', schema=TERMIOS_SCHEMA),
                'final_tty_config':     dict(type='list', schema=TERMIOS_SCHEMA),
                'init_script':          dict(type='list', schema=INIT_SCRIPT_SCHEMA),
                'answer_script':        dict(type='list', schema=INIT_SCRIPT_SCHEMA),
            }
        }
    },

    'channels': {
        'type': 'list',
        'schema': {
            'type': 'dict',
            'valueschema': {
                'schema': {
                    'match_re': dict(type='string', required=True),
                    'name':     dict(type='string', required=True),
                    'modem':    dict(type='string'),
                }
            }
        },
    }
}


# Loader found here:
# https://stackoverflow.com/questions/528281/how-can-i-include-a-yaml-file-inside-another


class CircularInheritanceError(Exception):
    """Raised when a config item inheritance is circular."""
    pass



class ParentNotFoundError(Exception):
    """Raised when a config item inherits from an unknown item."""
    pass



class LoaderWithInclude(yaml.SafeLoader):
    """Loader with !include capability."""
    def __init__(self, stream):
        self._root = os.path.split(stream.name)[0]
        super(LoaderWithInclude, self).__init__(stream)


    def include(self, node):
        """Process an !include directive."""
        pattern = os.path.join(self._root, self.construct_scalar(node))

        with open(filename) as f:
            return yaml.load(f, LoaderWithInclude)


LoaderWithInclude.add_constructor('!include', LoaderWithInclude.include)


def read_config(filename, schema):
    logging.info(f"Reading configuration from {filename}")
    try:
        with open(filename, encoding="utf-8") as f:
            config = yaml.load(f, LoaderWithInclude)
            v = cerberus.Validator(schema)
            if not v.validate(config):
                logging.critical(f"YAML Configuration is invalid. Parser reports:")
                for line in yaml.dump(v.errors).strip().split("\n"):
                    logging.critical("  " + line)
                sys.exit(1)

            logging.debug(f"Configuration loaded and valid")
            return config

    except cerberus.schema.SchemaError as e:
        logging.critical(f"Configuration error: {e}")
        sys.exit(1)
        
    except Exception as e:
        msg = f"Failed to read config file {filename}"
        logging.critical(msg, exc_info=e)
        logging.exception(f"Failed to read config file {filename}", exc_info=e)
        raise



def process_config_inheritance(name, collection: dict, inherit_key="inherit", seen=None):
    """Process inheritance in configuration values. Modifies ``collection`` by
    adding inherited keys and deleting the ``inherit_name`` key.

    Raises KeyError if ``name`` is not found in ``collection``.

    Raises CircularInheritanceError if circular inheritance is detected.

    Raises ParentNotFoundError if the parent item could not be found.

    >>> col = {}
    >>> col["a"] = {"one": 1, "two": 2}
    >>> col["b"] = {"inherit": "a", "three": 3}
    >>> col["c"] = {"inherit": "a", "four": 4}
    >>> col["d"] = {"inherit": "c", "five": 5}
    >>> col["e"] = {"inherit": "e", "five": 5}
    >>> col["f"] = {"inherit": "z", "six": 6}

    >>> process_config_inheritance("a", col)
    {'one': 1, 'two': 2}

    >>> process_config_inheritance("b", col)
    {'one': 1, 'two': 2, 'three': 3}

    >>> process_config_inheritance("c", col)
    {'one': 1, 'two': 2, 'four': 4}

    >>> process_config_inheritance("d", col)
    {'one': 1, 'two': 2, 'four': 4, 'five': 5}

    >>> col["b"]
    {'one': 1, 'two': 2, 'three': 3}

    >>> col["c"]
    {'one': 1, 'two': 2, 'four': 4}

    >>> process_config_inheritance("e", col)
    Traceback (most recent call last):
    ...
    config.CircularInheritanceError: ('e', ['e'])

    >>> process_config_inheritance("f", col)
    Traceback (most recent call last):
    ...
    config.ParentNotFoundError: z

    >>> process_config_inheritance("spam", col)
    Traceback (most recent call last):
    ...
    KeyError: 'spam'
    """

    item = collection[name]     # Raise KeyError if not found.

    # Terminating condition, no inheritance.
    if inherit_key not in item:
        return item

    if seen is None:
        seen = []

    parent_name = item[inherit_key]
    if parent_name not in collection:
        raise ParentNotFoundError(parent_name)

    if parent_name in seen:
        raise CircularInheritanceError(parent_name, seen)

    inherited_item = process_config_inheritance(parent_name, collection,
                                                inherit_key=inherit_key,
                                                seen=seen + [ name ])
    new_item = copy.deepcopy(inherited_item)
    new_item.update(item)
    del new_item[inherit_key]
    collection[name] = new_item

    return new_item


# End of file.
