#!/usr/bin/python3


import ipaddress
import cerberus


class NetworkDataJsonValidator(cerberus.Validator):
    """
    A simple JSON data validator with a custom data type for IPv4 addresses
    """
    def _validate_type_ipv4address(self, field, value):
        """
        checks that the given value is a valid IPv4 address
        """
        try:
            # try to create an IPv4 address object using the python3 ipaddress module
            ipaddress.IPv4Address(value)

        except:
            self._error(field, "Not a valid IPv4 address")

# End of file.
