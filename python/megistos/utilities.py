#!/usr/bin/python3

import re


def filter_keys(x: dict, *args, casefold=False) -> dict:
    """Return a dict with only the specified keys.

    >>> d = {}
    >>> d["a"] = "foo"
    >>> d["b"] = "bar"
    >>> d["SPAM"] = "eggs"
    >>> filter_keys(d, "a", "b")
    {'a': 'foo', 'b': 'bar'}
    >>> filter_keys(d, "a", "b", "spam")
    {'a': 'foo', 'b': 'bar'}
    >>> filter_keys(d, "a", "b", "spam", "eggs", casefold=True)
    {'a': 'foo', 'b': 'bar', 'spam': 'eggs'}
    """

    if casefold:
        casefolded_args = { x.casefold() for x in args }
        return { k.casefold(): v for k, v in x.items()
                 if k.casefold() in casefolded_args }
    else:
        return { k: v for k, v in x.items() if k in args }


_justify_re = re.compile(r"((?:^|\s+)\S+)")

def justify(s, s_len, width):
    """Fully justify the string s by adding spaces between words until it's the
    same width as width. The argument s_len is the number of visible
    characters in s. If s contains no escape sequences, this is the same as
    len(s).

    >>> s = "Lorem ipsum dolor sit amet."

    >>> justify(s, len(s), 35)
    'Lorem   ipsum   dolor   sit   amet.'

    >>> justify(s, len(s), 30)
    'Lorem  ipsum dolor  sit  amet.'

    >>> justify(s, len(s), 29)
    'Lorem ipsum  dolor sit  amet.'

    >>> justify(s, len(s), 28)
    'Lorem ipsum dolor  sit amet.'

    >>> justify(s, len(s), 27)
    'Lorem ipsum dolor sit amet.'

    >>> justify(s, len(s), 1)
    'Lorem ipsum dolor sit amet.'

    """
    parts = _justify_re.findall(s)
    num_interwords = len(parts) - 1
    if num_interwords == 0:
        return s # Can't justify a single word!

    spaces_needed = width - s_len

    # The easy case! Add one space to each inter-word space.
    if spaces_needed == num_interwords:
        return parts[0] + ''.join(" " + x for x in parts[1:])

    # Calculate the number of spaces we should add (as a float).
    spaces_per_interword = spaces_needed / num_interwords

    # Now perform error diffusion on the required spaces. I learned
    # that algorithm when I was 19 and this is probably the second
    # time I use it. And the first time was writing this same function
    # in C.
    error = 0.49 # 0.49 ensures ceil() approximation of the error.
    retval = parts[0]
    for part in parts[1:]:
        ns = int(spaces_per_interword + error)
        retval += " " * ns
        retval += part
        error += spaces_per_interword - ns

    return retval


# End of file.
