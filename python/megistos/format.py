#!/usr/bin/python3

import functools
import pprint
import re
import sys
import typing
import yaml
import textwrap

from attr import define, field
from copy import copy

from html.parser import HTMLParser

from . import logging
from . import colour
from . import config

from .terminal import Terminal
from .utilities import filter_keys, justify


TERMINALS_SCHEMA = {
    'terminals': {
        'type': 'dict',
        'valueschema': {
            'type': 'dict',
            'schema': {
                'inherit': dict(type='string'),
                'cols': dict(type='integer'),
                'rows': dict(type='integer'),
                'has_escape_sequences': dict(type='boolean'),
                'can_reposition_cursor': dict(type='boolean'),
                'can_turn_off_attrs': dict(type='boolean'),
                'has_ansi_colour': dict(type='boolean'),
                'has_16_colours': dict(type='boolean'),
                'has_256_colours': dict(type='boolean'),
                'has_truecolour': dict(type='boolean'),

                'has_bold': dict(type='boolean'),
                'has_dim': dict(type='boolean'),
                'has_italic': dict(type='boolean'),
                'has_underline': dict(type='boolean'),
                'has_blink': dict(type='boolean'),
                'has_inverse': dict(type='boolean'),
                'has_invisible': dict(type='boolean'),
                'has_strikethrough': dict(type='boolean'),
                
                'palette': {
                    'type': 'list',
                    'schema': {
                        'regex': '^#[0-9a-f]{6}$',
                    }
                }
            }
        }
    }
}


COLOR_SCHEMA = {
    'anyof': [
        {'regex': r'^#([0-9a-fA-F]{3}|[0-9a-fA-F]{6})$'}, # #RGB or #RRGGBB
        {'allowed': list(colour.NAMED_COLOURS.keys())}
    ],
}


STYLE_SCHEMA = {
    'styles': {
        'type': 'dict',
        'valueschema': {
            'type': 'dict',
            'schema': {
                'inherit': dict(type='string'),
                'style': {
                    'type': 'dict',
                    'valueschema': {
                        'schema': {
                            'reset': dict(type='boolean'),
                            'fg': COLOR_SCHEMA,
                            'bg': COLOR_SCHEMA,
                            'bold': dict(type='boolean'),
                            'dim': dict(type='boolean'),
                            'italic': dict(type='boolean'),
                            'underline': dict(type='boolean'),
                            'blink': dict(type='boolean'),
                            'inverse': dict(type='boolean'),
                            'invisible': dict(type='boolean'),
                            'strikethrough': dict(type='boolean'),
                        }
                    }
                }
            }
        }
    }
}


_re_attrs2kwargs = re.compile("[^A-Za-z0-9_]+")

def attrs2kwargs(attrs: list, *args) -> dict:
    """Return a dict with only the specified keys from the list
    ``attrs``. Used to obtain variable or argument names from
    HTML-like attributes with casefolding. Keys are case-folded, and
    any non-empty sequence of non-identifier characters in key names
    is replaced by underscores.

    >>> d = [("a", "foo"), ("BORDER--WIDTH", "bar"), ("spam and eggs", "eggs")]
    >>> attrs2kwargs(d, "A")
    {'a': 'foo'}

    >>> attrs2kwargs(d, "a", "border_width", "some_other_attr")
    {'a': 'foo', 'border_width': 'bar'}

    >>> attrs2kwargs(d, "a", "border_width", "spam_and_eggs")
    {'a': 'foo', 'border_width': 'bar', 'spam_and_eggs': 'eggs'}

    >>> attrs2kwargs(d, "foobar")
    {}

    """
    cfargs = { _re_attrs2kwargs.sub("_", x.casefold()): None for x in args }

    retval = {}
    for attr, val in attrs:
        cfattr = _re_attrs2kwargs.sub("_", attr.casefold())
        if cfattr in cfargs:
            retval[cfattr] = val

    return retval


def map_enum_attr(args: dict, key: str, attrmap: dict, delete=True) -> dict:
    """Treat args[key] as an enum, and map its string values to some other
    values. Update args, and return it.

    The keys in attrmap must be casefolded.
    
    If the value can't be mapped because it doesn't exist in attrmap,
    delete it unless delete=False is specified.
    
    >>> a = {"align": "left", "foo": "bar"}
    >>> attrmap = {"left": 0, "center": 1, "right": 2}
    >>> map_enum_attr(a, "align", attrmap)
    {'align': 0, 'foo': 'bar'}

    >>> a = {"align": "LEFT", "foo": "bar"}
    >>> map_enum_attr(a, "align", attrmap)
    {'align': 0, 'foo': 'bar'}

    >>> a = {"align": "whoops", "foo": "bar"}
    >>> map_enum_attr(a, "align", attrmap)
    {'foo': 'bar'}

    >>> a = {"align": "whoops", "foo": "bar"}
    >>> map_enum_attr(a, "align", attrmap, delete=False)
    {'align': 'whoops', 'foo': 'bar'}
    """
    try:
        val = args[key].casefold()
        try:
            args[key] = attrmap[val]
        except KeyError:
            if delete:
                del args[key]
    except KeyError:
        return args
    finally:
        return args


def parse_bool(s):
    """Parse a number of different bool-like words.

    >>> parse_bool(1)
    True

    >>> parse_bool(0)
    False

    >>> parse_bool("True")
    True

    >>> parse_bool("no")
    False

    >>> parse_bool("on")
    True
    """
    if type(s) == int:
        return bool(s)
    if s.casefold() in ['1', 'true', 'on', 'yes', 'y', 't']:
        return True
    if s.casefold() in ['0', 'false', 'off', 'no', 'n', 'f']:
        return False
    raise ValueError(s)


def convert_attr(args: dict, key: str, converter: typing.Callable,
                 validator: typing.Callable = None) -> dict:
    """Convert args[key] by applying converter() to the value. If the conversion
    raises ValueError, delete the key from the dict. Otherwise, update the dict
    with the converted value.
    
    If validator is specified and ``validator(converted_value)`` returns
    ``False`` when called with the value, delete the key from the ``args`` dict if
    validator(args[key]) returns False.

    Return the updated args dict.

    >>> d = {"a": "123", "b": "-10", "c": "0x13"}
    >>> convert_attr(d, "a", converter=int)
    {'a': 123, 'b': '-10', 'c': '0x13'}

    >>> convert_attr(d, "b", converter=int, validator=lambda x: x > 0)
    {'a': 123, 'c': '0x13'}

    >>> convert_attr(d, "c", converter=lambda x: int(x, 16))
    {'a': 123, 'c': 19}
    """
    try:
        args[key] = converter(args[key])
        if validator is not None:
            assert validator(args[key])

    except (ValueError, AssertionError):
        del args[key]

    finally:
        return args


@define(kw_only=True)
class TermStyle:
    reset: bool         = field(default=False)
    fg: tuple           = field(default=None)
    bg: tuple           = field(default=None)
    bold: bool          = field(default=None)
    dim: bool           = field(default=None)
    italic: bool        = field(default=None)
    underline: bool     = field(default=None)
    blink: bool         = field(default=None)
    inverse: bool       = field(default=None)
    invisible: bool     = field(default=None)
    strikethrough: bool = field(default=None)


    def get_diff_from(self, other):
        # If this style resets all previous styles, then self will always be
        # the difference.
        if self.reset:
            return self

        kwargs = {}
        for attr in self.__slots__:
            if attr.startswith('_'):
                continue
            if getattr(self, attr) != getattr(other, attr):
                kwargs[attr] = getattr(self, attr)

        return TermStyle(**kwargs)


    def items(self):
        for attr in self.__slots__:
            if attr.startswith('_'):
                continue
            if getattr(self, attr) is not None:
                yield attr, getattr(self, attr)


    def update(self, other):
        """Update our attributes from those of another style. Only attributes set are
        updated.
        """
        retval = {}
        for attr in self.__slots__:
            if attr.startswith('_'):
                continue
            if getattr(other, attr) is not None:
                self[attr] = getattr(other, attr)
        return self
        

    
class FormatterEngine(HTMLParser):
    """This engine formats a tiny HTML-like markup-language into calls to an Output
    Engine.
    """

    GLOBAL_COLOUR_ATTRS = [ "fg", "bg" ]

    GLOBAL_BOOL_ATTRS = [ "reset", "bold", "dim", "italic", "underline",
                          "blink", "inverse", "invisible", "strikethrough" ]
    
    def __init__(self):
        HTMLParser.__init__(self)
        self.terminal = None
        self.tag_stack, self.style_stack = [], []


    def set_term(self, terminal_name):
        terminals = config.read_config("terminals.yaml", TERMINALS_SCHEMA)['terminals']

        try:
            terminal = config.process_config_inheritance(terminal_name, terminals)

        except KeyError as e:
            raise RuntimeError("Terminal '{}' has not been defined.".format(e.args[0])) from e

        except config.CircularInheritanceError as e:
            raise RuntimeError("Circular 'inherit' reference: {}.".format(" → ".join(seen))) from e

        except config.ParentNotFoundError as e:
            raise RuntimeError("Terminal '{}' (in an 'inherit' referece) not defined".format(e.args[0])) from e

        try:
            self.terminal = Terminal.from_config(terminal_name, terminal)
        except Exception as e:
            raise RuntimeError("Failed to configure terminal '{}': {}".format(terminal_name, e)) from e
    
    
    def error(self, msg):
        # TODO: put this in a log file.
        print("Error: {}".format(msg))
    
    
    def _process_style(self, term, styles, seen):
        # Already processed?
        if term in self.stylesheets:
            #print("Style for {} already processed.".format(term))
            return self.stylesheets[term]
    
        if term in seen:
            raise RuntimeError("Circular 'like' reference: {}.".format(" → ".join(seen)))
    
        term_style = styles[term]
        this_style = { k.replace(" ", ""): v for k, v in term_style.get('style', {}).items() }

        # Convert RGB colours to our local format.
        for tag, tag_style in this_style.items():
            if 'fg' in tag_style:
                tag_style['fg'] = colour.parse_colour(tag_style['fg'])
            if 'bg' in tag_style:
                tag_style['bg'] = colour.parse_colour(tag_style['bg'])

        this_style = { k: TermStyle(**v) for k, v in this_style.items() }
    
        if 'inherit' in term_style:
            parent_term = term_style['inherit']
            #print("Recursing {} like {}".format(term, parent_term))
            inherited_style = self._process_style(parent_term, styles, [ term ] + seen)
            #print("  INH ", inherited_style)
            inherited_style.update(this_style)
            #print("  UPD ", this_style)
            self.stylesheets[term] = inherited_style
            #print("  FIN ", inherited_style)
            return inherited_style
    
        self.stylesheets[term] = this_style
        return this_style
    
    
    def load_style(self, filename):
        if self.terminal is None:
            raise RuntimeError("Terminal is not set. Call set_term() first")

        raw_style = config.read_config(filename, STYLE_SCHEMA)['styles']

        # Get the stylesheet for this terminal, following inheritance
        stylesheet = config.process_config_inheritance(self.terminal.name, raw_style)['style']

        # Process colours in the stylesheet
        for tag in stylesheet:
            if 'fg' in stylesheet[tag]:
                stylesheet[tag]['fg'] = colour.parse_colour(stylesheet[tag]['fg'])
            if 'bg' in stylesheet[tag]:
                stylesheet[tag]['bg'] = colour.parse_colour(stylesheet[tag]['bg'])

        self.style = stylesheet
    
    
    def write(self, s):
        self.feed(s)
    
    
    def get_style(self, tag, attrs):
        # Get style for this tag
        style = copy(self.style.get(tag, {}))
    
        # Get style for a parent_tag>tag ‘selector’.
        if len(self.tag_stack) > 1:
            selector = '>'.join(self.tag_stack[-2:])
            style.update(self.style.get(selector, {}))

        # And update using attributes.
        attrs = self.handle_global_attrs(attrs)
        style.update(attrs)
        return style


    def handle_global_attrs(self, attrs):
        """Handle global attributes, like fg, bg."""

        kwargs = attrs2kwargs(attrs, *self.GLOBAL_COLOUR_ATTRS,
                              *self.GLOBAL_BOOL_ATTRS)

        for key in self.GLOBAL_COLOUR_ATTRS:
            convert_attr(kwargs, key, converter=colour.parse_colour)

        for key in self.GLOBAL_BOOL_ATTRS:
            convert_attr(kwargs, key, converter=parse_bool)

        return kwargs

    
    def handle_starttag(self, tag, attrs):
        self.tag_stack.append(tag)
        style = self.get_style(tag, attrs)
        self.style_stack.append(style)
        self.terminal.update_attrs(**style)

        #print("Start tag:", tag, attrs, style)

        handler = getattr(self, 'handle_starttag_' + tag, None)
        if handler:
            # If the handler returns True, it's done its own style
            # processing, so end here.
            handler(tag, attrs)
    
    
    
    def handle_endtag(self, tag):
        handler = getattr(self, 'handle_endtag_' + tag, None)
        if handler:
            if handler(tag):
                return

        #print("Encountered an end tag:", tag)
        if self.tag_stack:
            if self.tag_stack[-1] != tag:
                self.error("Closing tag <{}> when tag <{}> is open".format(tag, self.tag_stack[-1]))

            self.tag_stack.pop()
            old_style = self.style_stack.pop()
            self.terminal.pop_attr_state()

        else:
            self.error("Closing tag <{}> when no tag is open".format(tag))



    def handle_data(self, data):
        self.terminal.write(data)


    def handle_starttag_p(self, tag, attrs):
        # <p> works like the HTML 1.0 tag, it's just a paragraph separator, not
        # a container. So pop the tag context.
        self.style_stack.pop()
        self.tag_stack.pop()

        # End the previous paragraph (if any) and start a new one.
        self.terminal.paragraph()
        return True             # Don't do anything with styles, stacks, etc.


    def handle_endtag_p(self, tag, attrs):
        # Ignore </p>
        return True

        
    def handle_starttag_format(self, tag, attrs):
        # Start formatting
        # args = filter_keys(attrs, "align", "maxwidth", "margin-left", "margin-right", "indent")

        int_args = ["min_width", "max_width", "margin_left", "margin_right", "indent",
                    "margin_top", "margin_bottom"]
        #kwargs = attrs2kwargs(attrs, "align", *int_args, "border-left", "border-right")
        kwargs = attrs2kwargs(attrs, "align", *int_args)

        # Massage the align attribute.
        map_enum_attr(kwargs, "align", {
            "left": self.terminal.ALIGN_LEFT,
            "centre": self.terminal.ALIGN_CENTRE,
            "center": self.terminal.ALIGN_CENTRE,
            "right": self.terminal.ALIGN_RIGHT,
            "justify": self.terminal.ALIGN_JUSTIFY,
            "l": self.terminal.ALIGN_LEFT,
            "c": self.terminal.ALIGN_CENTRE,
            "r": self.terminal.ALIGN_RIGHT,
            "j": self.terminal.ALIGN_JUSTIFY,
        })

        # Convert args to int.
        for key in int_args:
            convert_attr(kwargs, key, converter=lambda x: int(x),
                         validator=lambda x: x >= 0)

        # And start formatting.
        self.terminal.start_block_formatting(**kwargs)

        return True             # Normal container tag

    
    def handle_endtag_format(self, tag):
        # Stop formatting
        self.terminal.stop_block_formatting()
    

# End of file.
