#!/usr/bin/python3

import re
import os
import logging


from . import config as megistos_config


class Channels(object):
    def __init__(self, config_fname=None, config=None):
        if config is None:
            if config_fname is None:
                raise ValueError("config_fname and config were both None, can't initialise")
            else:
                config = megistos_config.read_config(config_fname, megistos_config.BBSD_CONFIG_SCHEMA)

        try:
            self.config = config['channels']
        except Exception as e:
            raise KeyError("parsed configuration is missing the 'channels' key")


    def dev_path_to_channel(self, name):
        """Locate a channel definition for the channel with the supplied device special
        `name`. The "/dev/" prefix can be left out. Return the first matching
        channel structure, or None if none matched.
        """

        # If name starts with a /, this will do the right thing.
        path = os.path.join("/dev", name)

        for group in self.config:
            # The YAML parser returns a dict with a single key.
            assert len(group) == 1
            channel_group_name, channel_group = list(group.items())[0]
            print(channel_group_name, channel_group)

            regex = re.compile(channel_group['match_re'])
            m = regex.match(path)
            if m:
                channel_name = channel_group['name'].format(*m.groups())
                print("NAME=",channel_name)
                return channel_name, channel_group_name, channel_group
                
        
# End of file.