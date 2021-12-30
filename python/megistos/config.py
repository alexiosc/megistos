#!/usr/bin/python3

import cerberus
import logging
import sys
import yaml


BBSD_PORT = 8889

BBSD_SOCK = "/tmp/bbsd.sock"

BBSD_CONFIG_SCHEMA = {
    'bbsd': {
        'type': 'dict',
        'schema': {
            'tick':     dict(type='integer', min=1, max=30, default=15),
            'socket':   dict(type='string', default=BBSD_SOCK),
            'tcp_addr': dict(type='string', default="127.0.0.1"),
            'tcp_port': dict(type='integer', min=1, max=65535, default=BBSD_PORT),
        }
    },

    # TODO: Full validation
    'channels': {
        'type': 'list',
    }
}


def read_config(filename, schema):
    logging.info(f"Reading configuration from {filename}")
    try:
        with open(filename, encoding="utf-8") as f:
            config = yaml.safe_load(f)
            v = cerberus.Validator(schema)
            if not v.validate(config):
                logging.critical(f"Configuration invalid")
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
