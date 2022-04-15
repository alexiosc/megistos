#!/usr/bin/python3

import functools
import pprint
import re
import sys
import textwrap
import typing
import yaml

from attr import define, field
from copy import copy

from html.parser import HTMLParser

from . import logging
from . import colour
from . import config
from . import output
from .utilities import filter_keys, justify


# bbssession command opcodes
BBSS_SET_ENCODING = 1
BBSS_TEXT = 2
BBSS_BINARY = 3


@define(kw_only=True)
class Wrapper:
    """Wrap text incrementally, handle invisible characters and non-breaking
    strings, and provide lists of lines meant to be used by the box model
    formatter.

    """

    width: int             = field(default=79, init=True, repr=True)
    indent: int            = field(default=0, init=True, repr=True)
    single_space: bool     = field(default=True, init=True, repr=False)
    tabsize: int           = field(default=8, init=True, repr=False)

    last_space_i: int      = field(default=-1, repr=False)
    last_space_pos: int    = field(default=-1, repr=False)
    lines: list            = field(default=[], repr=False)
    line_so_far: list      = field(default=[], repr=False)
    pos: int               = field(default=0, repr=False)


    CHUNK_TEXT    = 0
    CHUNK_ESCSEQ  = 1
    CHUNK_NOBR    = 2


    # All white space in Unicode, except for U+00A0 NON-BREAK SPACE
    SPACES = "\t\n\v\f\r \u1680\u2000\u2001\u2002\u2003\u2004\u2005" + \
        "\u2006\u2007\u2008\u2009\u200a\u202f\u205f\u3000"

    unicode_whitespace_trans = {}
    uspace = ord(' ')
    for x in SPACES:
        unicode_whitespace_trans[ord(x)] = uspace

    def _munge_whitespace(self, text):
        """_munge_whitespace(text : string) -> string

        Munge whitespace in text: expand tabs and convert all other
        whitespace characters to spaces.  Eg. " foo\\tbar\\n\\nbaz"
        becomes " foo    bar  baz".
        """
        text = text.expandtabs(self.tabsize)
        text = text.translate(self.unicode_whitespace_trans)
        return text


    def __attrs_post_init__(self):
        self.start_paragraph()


    def len_so_far(self):
        """Count only visible characters in line_so_far."""
        return sum(x[0] for x in self.line_so_far)


    def get_line_so_far_prefix(self, numchars):
        """Return the number of elements of line_so_far that make up at most numchars.
        """
        prefix = 0
        for num_elems, x in enumerate(self.line_so_far, 1):
            if x[0]:
                prefix += 1
            if prefix == numchars:
                return num_elems
        return num_elems


    def get_line_so_far(self):
        return "".join(x[1] for x in self.line_so_far)
        

    def split_line_so_far(self, index, strip_first=False):

        charlen = sum(x[0] for x in self.line_so_far[:index])

        complete_line = "".join(x[1] for x in self.line_so_far[:index])

        len0 = len(complete_line)
        complete_line = complete_line.rstrip()
        charlen -= len0 - len(complete_line)

        self.lines.append((charlen, complete_line))

        # Strip leading spaces.
        if strip_first:
            new_line = self.line_so_far[index+1:]
        else:
            new_line = self.line_so_far[index:]
            
        self.line_so_far = new_line
        self.pos = self.len_so_far()

        # for i, l in enumerate(self.lines, 1):
        #     print(f'    {i:>2}. "{l}"')

        self.last_space_pos = -1
        self.last_space_i = -1


    def _write(self, s, invis=False):
        # Trivial: nothing is wrapped, nothing changes.
        if invis:
            self.line_so_far += [(False, x) for x in s]
            return

        skip_spaces = False
        for c in s:
            # Record where the last space was.
            if c == " ":
                if skip_spaces:
                    continue
                self.last_space_i = len(self.line_so_far)
                self.last_space_pos = self.pos
                if self.single_space:
                    skip_spaces = True
            else:
                skip_spaces = False

            self.line_so_far.append((True, c))
            self.pos += 1

            if self.pos >= self.width:
                if self.last_space_pos > 0:
                    lsi = self.last_space_i
                    self.split_line_so_far(self.last_space_i, True)
                else:
                    # Split a single long word. First, calculate the number of
                    # line_so_far elements that make up self.width characters.
                    prefix = self.get_line_so_far_prefix(self.width)
                    self.split_line_so_far(prefix)
                    

    def write(self, s):
        munged = self._munge_whitespace(s)

        # First characters of the first line of the paragraph? Then left strip
        # too.
        if not self.lines and not self.line_so_far:
            munged = munged.lstrip()

        if munged:
            self._write(munged)


    def write_nobr(self, s):
        self._write(self._munge_whitespace(s).translate({" ": "\xa0"}))


    def write_escape_sequence(self, s):
        self._write(s, invis=True)


    def start_paragraph(self, start_pos=0):
        self.last_space_i = -1
        self.last_space_pos = -1
        self.lines = []
        self.line_so_far = []
        self.pos = start_pos
        if self.indent:
            self.pos += self.indent


    def end_paragraph(self):
        # Is this an empty paragraph?
        if not self.lines:
            if not self.line_so_far:
                return []       # Completely empty paragraph
            if len(self.line_so_far) == 1 and self.line_so_far[0][1].strip() == "":
                return []       # Paragraph made entirely of white space

        # print("END PARA, len(lines)={}, len(line_so_far)={}, line_so_far={}".format(
        #     len(self.lines), len(self.line_so_far), self.line_so_far))

        self.split_line_so_far(len(self.line_so_far))

        return self.lines



@define(kw_only=True)
class TerminalInfo:
    """This is a tiny, naïve, specialised subset of terminfo, but a lot more
    readable."""
    cols: int                   = field(default=80)
    rows: int                   = field(default=23)
    has_escape_sequences: bool  = field(default=True)

    can_reposition_cursor: bool = field(default=True)
    can_turn_off_attrs: bool    = field(default=True)

    has_colour: bool            = field(default=None, init=False)

    has_ansi_colours: bool      = field(default=True)
    has_16_colours: bool        = field(default=False) # Actual 16 colours, not CGA style.
    has_256_colours: bool       = field(default=False)
    has_truecolour: bool        = field(default=False)
    palette: list               = field(default=colour.CGA_PALETTE)

    has_fg: bool                = field(default=True)
    has_bg: bool                = field(default=True)
    has_bold: bool              = field(default=True)
    has_dim: bool               = field(default=True)
    has_italic: bool            = field(default=False)
    has_underline: bool         = field(default=True)
    has_blink: bool             = field(default=True)
    has_inverse: bool           = field(default=True)
    has_invisible: bool         = field(default=True)
    has_strikethrough: bool     = field(default=False)


    @classmethod
    def from_config(cls, config):
        # Generate a terminfo structure.
        ti = cls()
        for attr in ti.__slots__:
            if attr[0] == "_":
                continue
            if attr in config:
                setattr(ti, attr, config[attr])

        if ti.has_256_colours:
            ti.palette = colour.XTERM256COLOUR_PALETTE

        if ti.palette is not None:
            ti.palette = [ colour.parse_colour(x) for x in ti.palette ]

        ti.has_colour = ti.has_ansi_colours or ti.has_16_colours or \
            ti.has_256_colours or ti.has_truecolour

        # These make looping through attributes easier
        ti.has_fg = ti.has_colour
        ti.has_bg = ti.has_colour

        return ti


@define(kw_only=True)
class Terminal:
    """This class represents the capabilities and state of the user's terminal. By
    keeping track of this information we can optimise control sequences, know
    when to pause at the end of the page, provide text wrapping, etc.
    """

    DEFAULT_ATTRS = {
        "fg": "37",             # Encoded as SGR fragments
        "bg": "40",
        "bold": False,
        "dim": False,
        "italic": False,
        "underline": False,
        "blink": False,
        "inverse": False,
        "invisible": False,
        "strikethrough": False,
    }

    ATTR_VALUES = {
        "bold":          [ 1, 22 ],
        "dim":           [ 2, 22 ],
        "italic":        [ 3, 23 ],
        "underline":     [ 4, 24 ],
        "blink":         [ 5, 25 ],
        "inverse":       [ 7, 27 ],
        "invisible":     [ 8, 28 ],
        "strikethrough": [ 9, 29 ],
    }

    ALIGN_LEFT = 1
    ALIGN_CENTRE = 2
    ALIGN_CENTER = 2
    ALIGN_RIGHT = 3
    ALIGN_JUSTIFY = 4

    name: str              = field()
    terminfo: TerminalInfo = field(repr=False)

    # Terminal attribtues and colours, style stack
    attrs: dict            = field(default=copy(DEFAULT_ATTRS), repr=False, init=False)
    stack: list            = field(default=[], repr=False, init=False)

    # Cursor position
    x: int                 = field(default=0, repr=False, init=False)
    y: int                 = field(default=0, repr=False, init=False)
    is_nonstop: bool       = field(default=False, repr=False, init=False)

    # Formatting, alignment, etc. state.
    align: int             = field(default=ALIGN_LEFT, repr=False, init=False)
    block_mode: bool       = field(default=False, repr=False, init=False)
    max_width: int         = field(default=0xffffffff, repr=False, init=False)
    margin_left: int       = field(default=0, repr=False, init=False)
    margin_right: int      = field(default=0, repr=False, init=False)
    margin_top: int        = field(default=0, repr=False, init=False)
    margin_bottom: int     = field(default=0, repr=False, init=False)
    indent: int            = field(default=0, repr=False, init=False)
    wrapper                = field(default=None, repr=False, init=False)
    content_width: int     = field(default=79, repr=False, init=False)
    centre_point: int      = field(default=38, repr=False, init=False)


    @classmethod
    def from_config(cls, name, config):
        """Create a terminal definition from a config file entry."""
        terminfo = TerminalInfo.from_config(config)
        return cls(name=name, terminfo=terminfo)


    #@functools.cache
    def handle_colour(self, colspec, fg=False):
        """Convert an (r,g,b) triplet to a terminal-native colour code, suitable for
        using in an SGR sequence."""
        if colspec == "":
            return ""

        # Is the colspec already cooked? It is, if it's either a
        # single integer (in a string), or a series of integers.
        try:
            if type(colspec) == str and int(colspec) >= 0:
                return colspec
        except ValueError:
            if type(colspec) == str and ";" in colspec:
                return colspec
        
        # Easy! (but also rare)
        if self.terminfo.has_truecolour:
            if fg:
                return "38;2;{};{};{}".format(*colspec)
            else:
                return "48;2;{};{};{}".format(*colspec)

        # Look for the closest colour in our palette.
        index, rgb = colour.rgb_quantise(colspec, self.terminfo.palette)

        # 256-colour terminals
        if self.terminfo.has_256_colours and index < 256:
            if fg:
                return "38;5;" + str(index)
            else:
                return "48;5;" + str(index)

        # Full 16-colour terminals (e.g. xterm, but NOT ANSI)
        elif self.terminfo.has_16_colours and index < 16:
            base = [40, 30][fg]
            if index >= 8 and index < 16:
                base += 60
            return str(base + index)

        # ANSI-style terminals (8 colours, bold makes foreground brighter)
        elif self.terminfo.has_ansi_colours and index < 16:
            base = [40, 30][fg]
            if fg and index > 7:
                return "1;" + str(base + index)
            # Silently convert bright backgrounds to their dark
            # equivalents. The colours might not match perfectly, but this is
            # what ANSI does anyway.
            return str(base + (index & 7))

        raise RuntimeError("Don't know how to handle colour {} on this terminal".format(index))


    def reset_attrs(self):
        """Reset attributes to their default."""
        self.attrs['fg'] = ""            # Light grey text, default on ANSI.
        self.attrs['bg'] = ""            # Light grey text, default on ANSI.
        self.attrs = copy(self.DEFAULT_ATTRS)


    def full_sgr(self):
        """Return an SGR for the whole attribute state. Include an attribute reset.
        """
        ti = self.terminfo
        sgr = "\033["
        for key in self.attrs:
            if self.attrs.key and getattr(ti, "has_" + key):
                sgr += str(self.ATTR_VALUES[key][0]) + ";"

        # Strip off the trailing semicolon and add the 'm' (SGR sequence).
        self.write_escape_sequence(sgr.rstrip(";") + "m")


    def push_attr_state(self):
        """Get the terminal attribute state"""
        self.stack.append(copy(self.attrs))


    def pop_attr_state(self):
        """Set the attribute state using a value retrieved from save_attr_state()"""
        try:
            attrs = self.stack.pop()
            return self.update_attrs(push=False, **attrs)
        except IndexError:
            pass


    def update_attrs(self, push=True, reset=False, fg=None, bg=None, **kwargs):
        """Update terminal attributes based on what has been requested here. Arguments
        fg and bg should be provided as RGB triplets (0-255) per channel. These
        are quantised and converted to terminal-native colours. Features not
        supported by the terminal are silently ignored.
        
        """
        # Nothing to do
        if not self.terminfo.has_escape_sequences:
            return

        if push:
            self.push_attr_state()

        # If reset is set, reset all attributes to their defaults, update them
        # from our keyword argument, and enable any specified here (leaving an
        # attribute out means ‘off’).
        if reset:
            self.reset_attrs()
            if fg is not None and fg != "":
                self.attrs['fg'] = self.handle_colour(fg, fg=True)
            if bg is not None and bg != "":
                self.attrs['bg'] = self.handle_colour(bg, fg=False)
            for key in self.attrs:
                attrs[key] = kwargs.get(key, False)
            return self.full_sgr()

        sgr = "\033["
        need_reset = False

        # Update attributes from supplied keyword arguments, but only if we
        # need to.
        for key in self.attrs:
            # Ignore missing features
            if not getattr(self.terminfo, "has_" + key):
                continue
            flag = kwargs.get(key, None)

            if flag is True and not self.attrs[key]:
                self.attrs[key] = True
                sgr += str(self.ATTR_VALUES[key][0]) + ";"

            elif flag is False and self.attrs[key]:
                self.attrs[key] = False
                if self.terminfo.can_turn_off_attrs:
                    sgr += str(self.ATTR_VALUES[key][1]) + ";"
                else:
                    need_reset = True

        # Get the colours first. Changing foregrounds on ANSI might require a
        # full reset of all the colours.
        if bg is not None and bg != "":
            newbg = self.handle_colour(bg, fg=False)
            if newbg != self.attrs['bg']:
                sgr += newbg + ";"
            self.attrs['bg'] = newbg

        if fg is not None:
            newfg = self.handle_colour(fg, fg=True)

            if newfg != self.attrs['fg']:
                # If the foreground SGR starts with 1;, it's for an ANSI-like
                # terminal that can only access bright colours through
                # bold. This also means that it can't reset attributes, so if
                # we're going from a dark to a bright colour or vice vesa, a
                # full reset is required.
                if (newfg[:2] == "1;" and self.attrs['fg'][:2] != "1;") or \
                   (newfg[:2] != "1;" and self.attrs['fg'][:2] == "1;"):
                    need_reset = True
                else:
                    sgr += newfg + ";"

            self.attrs['fg'] = newfg

        # At this point, if need_reset is specified, we can just output all the
        # attributes at once.
        if need_reset:
            self.full_sgr()
            return

        # If not, we can return the incremental SGR we constructed: but only if
        # it's not empty.
        if sgr[-1] != "[":
            self.write_escape_sequence(sgr.strip(";") + "m")


    def write_escape_sequence(self, s):
        """Add a sequence of characters to the output that are considered to
        be zero length, i.e. do not advance the cursor. This is used
        for terminal escape sequences.

        """

        # TODO: Make this send to the proper file descriptor.
        if self.block_mode:
            self.wrapper.write_escape_sequence(s)
        else:
            sys.stdout.write(s)
        

    def write(self, s):
        # TODO: Make this send to the proper file descriptor.
        if self.block_mode:
            self.wrapper.write(s)
        else:
            sys.stdout.write(s)


    ###############################################################################
    #
    # CURSOR AND PAUSING
    #
    ###############################################################################

    def set_size(self, cols, rows):
        """Update the screen size."""
        self.terminfo.cols = cols
        self.terminfo.rows = rows


    def cursor_tof(self):
        """Set the cursor to the top-of-form, i.e. top of the simulated
        screen. This is done e.g. whenever a user prompt is displayed,
        so we can pause the screen after terminfo.rows and display a
        whole screenfull after the last prompt before pausing.
        """
        self.x, self.y = 0, 0


    def cursor_newline(self):
        self.x = 0
        self.y + 1
        

    def cursor_advance(self, dx, wrap=True):
        if wrap:
            self.x += (dx % self.terminfo.cols)
            self.y += (dx // self.terminfo.cols)
        else:
            self.x += dx


    def should_pause(self):
        return self.y >= (self.terminfo.rows - 1) and not self.is_nonstop


    ###############################################################################
    #
    # TEXT ALIGNMENT, WRAPPING, ETC.
    #
    ###############################################################################

    def start_block_formatting(self, align=None, min_width=None, max_width=None,
                               margin_left=None, margin_right=None,
                               margin_top=None, margin_bottom=None,
                               indent=None):
        """Start block-level formatting.


        The box model works like this:

        Terminal Width
        +--------------------------------------------------+
        |             |<--max_width-->:     |              |
        | margin_left | CONTENT       :     | margin_right |
        |             |               :     |              |
        :             :               :     :              :


        ``margin_left``: the number of spaces from the left edge of the
        screen. Paragraphs will be indented to this level. 0 means no
        indent.

        ``margin-right``: the number of spaces from the right edge of the
        screen. 0 means characters can reach the last column (minus
        one, to avoid terminals and terminal emulators with broken
        last-column wrapping).

        ``margin-top``: the number of blank lines before the
        paragraph.

        ``margin-bottom``: the number of blank lines after the
        paragraph.

        The usable space is then the width of the terminal minus
        ``margin-left`` and ``margin-right``.

        Because this can be too wide to read comfortably, paragraph
        width can be further capped to `max_width`. English-language
        typography suggests 64 characters are ideal for reading
        comfort.

        Given all this, some terminals are too narrow to display
        paragraphs using this technique. To degrade gracefully, if the
        final paragraph width is less than ``min_width``, margins are
        ignored and paragraphs use the entire width of the terminal.

        In all cases, the first line of each paragraph is indented by
        ``indent`` spaces.

        """

        if self.wrapper is None:
            self.wrapper = Wrapper()

        self.block_mode = True

        # Update box model.
        if align is not None:
            self.align = align
        if min_width is not None:
            self.min_width = min_width
        if max_width is not None:
            self.max_width = max_width
        if margin_left is not None:
            self.margin_left = margin_left
        if margin_right is not None:
            self.margin_right = margin_right
        if margin_top is not None:
            self.margin_top = margin_top
        if margin_bottom is not None:
            self.margin_bottom = margin_bottom
        # if border_left is not None:
        #     self.border_left = border_right
        # if border_right is not None:
        #     self.border_right = border_right
        if indent is not None:
            self.indent = indent
            self.wrapper.indent = indent
        else:
            self.wrapper.indent = 0
        
        self.recalculate_box_model()
        self.wrapper.width = self.content_width
        self.wrapper.start_paragraph()


    def recalculate_box_model(self):
        """Recalculate widths and parameters for the box model."""
        # Calculate the usable width.
        self.content_width = self.terminfo.cols - self.margin_left - self.margin_right

        # Cap to the max_width
        self.centre_point = min(self.content_width, self.terminfo.cols - 1)
        self.content_width = min(self.content_width, self.max_width)

        # Make sure we don't use the full width of the terminal. This
        # is to avoid automatic wrap-arounds on terminals that don't
        # do it like the VT-100 did and modern terminal emulators do.
        self.content_width = min(self.content_width, self.terminfo.cols - 1)


    def stop_block_formatting(self):
        self.paragraph()
        self.block_mode = False


    def paragraph(self):
        """End a block-level paragraph, ship it out to the user, and prepare for a new
        one. This has functionality equivalent to that of the HTML 1.0 <p> tag
        used as a separator.

        """

        # Get a list of (length, string) tuples representing lines to
        # print.
        wrapped_para = self.wrapper.end_paragraph()

        # Do nothing if the paragraph is empty.
        if not wrapped_para:
            return

        # Print the top margin.
        blank_line = None
        if self.margin_top >= 1:
            blank_line = self.output_block_line([[0, ""]], last_line=True)
            for n in range(self.margin_top - 1):
                self.output_line(blank_line)

        # Single line paragraph.
        if len(wrapped_para) == 1:
            self.output_block_line(*wrapped_para[0], first_line=True, last_line=True)
            return

        # Two lines or more:
        self.output_block_line(*wrapped_para[0], first_line=True)
        for length, line in wrapped_para[1:-1]:
            self.output_block_line(length, line)
        self.output_block_line(*wrapped_para[-1], last_line=True)

        # Print the bottom margin
        if self.margin_bottom >= 1:
            if blank_line is None:
                blank_line = self.output_block_line(0, "", last_line=True)
            for n in range(self.margin_bottom - 1):
                self.output_line(blank_line)

        # Start a new paragraph.
        self.wrapper.start_paragraph()

        # TODO: This is here for testing only. Remove it.
        #print("***<inter-paragraph>")


    def output_line(self, s):
        sys.stdout.write(s + "\n\r")
        return s


    def output_block_line(self, line_len, line, first_line=False, last_line=False):
        """Format a complete line within the block model and output to the
        user. ``line_len`` is the number of visible (cursor-advancing)
        characters in the line.

        """

        # Calculate the first-line paragraph indentation.
        if first_line:
            parindent = " " * self.indent
        else:
            parindent = ""

        ml = " " * self.margin_left # Left margin

        if self.align == self.ALIGN_LEFT:
            output = ml + parindent + line

        elif self.align == self.ALIGN_RIGHT:
            pad = ' ' * (self.content_width - line_len)
            output = ml + pad + parindent + line

        elif self.align == self.ALIGN_CENTRE:
            pad = ' ' * ((self.centre_point - line_len + 1) >> 1)
            output = ml + pad + parindent + line

        elif self.align == self.ALIGN_JUSTIFY:
            if first_line:
                # Account for the parident on the first line.
                output = ml + parindent + justify(line, line_len, self.content_width - self.indent)
            elif last_line:
                # No justification for the last line
                output = ml + parindent + line
            else:
                # Justify median paragraph lines
                output = ml + parindent + justify(line, line_len, self.content_width)

        else:
            # Catch-all case, same as ALIGN_LEFT
            output = ml + parindent + line

        #print("\033[0;7mSHIPOUT\033[0m", line, "\033[0m")
        # TODO: Make this write to the correct file descriptor
        # TODO: Handle page pausing here.
        return self.output_line(output)



    ###############################################################################
    #
    # BBSSESSION FUNCTIONALITY
    #
    ###############################################################################

    def _bbssession_command(self, opcode, payload=None):
        """Send out a bbssession in-band command. These look like terminal
        escape sequences, and follow the form:

        ESC \x01 <OPCODE> [ <PAYLOAD> ] \x01

        They must be sent to bbssession as a single, atomic
        transaction so we use flush the output buffers first, and send
        out the data packet unbuffered.
        """
        self.stream.flush()
        op_byte = opcode.to_bytes(1, 'big') # byte order meaningless here
        if payload is None:
            os.write(1, b"\033\001" + op_byte + b"\001")
        else:
            payload_bytes = payload.encode("us-ascii")
            os.write(1, b"\033\001" + op_byte + payload_bytes + b"\001")


    def set_encoding(self, encoding):
        """Instruct the bbssession handler to change the encoding. Also
        enables transcoding implicitly."""
        self._bbssession_command(BBSS_SET_ENCODING, encoding)


    def text_mode(self, state):
        """Enable transcoding of characters."""
        self._bbssession_command(BBSS_TEXT)


    def binary_mode(self, state):
        """Disable transcoding when e.g. binary transmissions are happening."""
        self.stream.flush()
        self._bbssession_command(BBSS_BINARY)
    
        

# End of file.
