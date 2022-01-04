#!/usr/bin/python3

import cerberus
import logging
import sys
import yaml


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


def read_config(filename, schema):
    logging.info(f"Reading configuration from {filename}")
    try:
        with open(filename, encoding="utf-8") as f:
            config = yaml.safe_load(f)
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


# End of file.
