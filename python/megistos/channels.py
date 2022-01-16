#!/usr/bin/python3

import re
import os
import logging

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


class Channels(object):
    def __init__(self, config_fname=None, config=None):
        if config is None:
            if config_fname is None:
                raise ValueError("config_fname and config were both None, can't initialise")
            else:
                config = megistos_config.read_config(config_fname, megistos_config.BBSD_CONFIG_SCHEMA)

        self.config = config


    def dev_path_to_channel(self, name):
        """Locate a channel definition for the channel with the supplied device special
        `name`. The "/dev/" prefix can be left out. Return the first matching
        channel structure, or None if none matched.
        """

        # If name starts with a /, this will do the right thing.
        path = os.path.join("/dev", name)

        for group in self.config['channels']:
            # The YAML parser returns a dict with a single key.
            assert len(group) == 1
            channel_group_name, channel_group = list(group.items())[0]

            regex = re.compile(channel_group['match_re'])
            m = regex.match(path)
            if m:
                try:
                    channel_name = channel_group['name'].format(*m.groups())
                except Exception as e:
                    raise ValueError(f"String format error in '{channel_group['name']}' (match_re groups: {m.groups()}): {e}")

                retval = Channel(dev=path, name=channel_name, group_name=channel_group_name, config=channel_group,
                                 modem_type=channel_group.get('modem'),
                                 modem_def = self.config.get('modems',dict()).get(channel_group.get('modem')))

                return retval


# End of file.