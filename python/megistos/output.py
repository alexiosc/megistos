#!/usr/bin/python3

import re
import os
import io
import sys
import tty
import termios
import logging
import codecs
import textwrap

from attr import define, field

from . import config as megistos_config

# Character attributes

ATTR_R_MASK        = 0x00ff0000
ATTR_G_MASK        = 0x0000ff00
ATTR_B_MASK        = 0x000000ff

ATTR_BOLD          = 0x01000000
ATTR_UNDERLINE     = 0x02000000
ATTR_BLINK         = 0x04000000
ATTR_INVERSE       = 0x08000000
ATTR_ITALIC        = 0x10000000
ATTR_STRIKETHROUGH = 0x20000000



# bbssession command opcodes
BBSS_SET_ENCODING = 1
BBSS_TEXT = 2
BBSS_BINARY = 3

# How to deal with terminal directives.
OUT_ANSI_X364 = 0               # Output ANSI.X364 sequences as-is.
OUT_ANSI_SYS = 1                # Compatibility mode for ANSI.SYS.
OUT_STRIP = 2                   # Strip escape sequences entirely.

OUT_PLAIN = 0
OUT_ALIGN_LEFT = 1
OUT_ALIGN_RIGHT = 2
OUT_CENTER = 3
OUT_CENTRE = OUT_CENTER
OUT_JUSTIFY = 4


# @define
# class LCGRandom:
#     seed: int = field()
#
#     def __init__(self, seed=1):
#         self.state = seed
#
#     def randint(self, mod):
#         self.state = (self.state * 1103515245 + 12345) & 0x7fffffff
#         return self.state % mod


@define(kw_only=True)
class Channel:
    name: str        = field()
    group_name: str  = field()
    dev: str         = field()
    config: dict     = field(repr=False)
    modem_type: str  = field()
    modem_def: dict  = field(repr=False)


@define()
class Coords:
    x: int = field()
    y: int = field()

    def tof(self):
        """Set at top-of-form."""
        self.y = 0


    def newline(self):
        """Go to next line."""
        self.x = 0
        self.y += 1


class OutputEngine:
    def __init__(self, config):
        self.config = config
        self.stream = sys.stdout
        self.fd = self.stream.fileno()

        # Stop box model formatting if there's less than this many
        # usable characters per line.
        self.absolute_minimum_text_width = 20
        
        self.size = Coords(80, 23) # A safe default screen size
        self.curs = Coords(0, 0)

        self.line_mode_on = False
        self.set_line_mode(OUT_PLAIN)

        self.ansi_x364_mode = OUT_ANSI_X364

        self.put_state = 0

        self.line_so_far = ""
        self.last_space_index = -1
        self.last_space_pos = -1
        self.esc_so_far = ""
        self.indent = 0
        self.left_margin = 0
        self.right_margin = 0
        self.max_width = 0
        self.left_border = ""
        self.right_border = ""
        self.just_re = None

        self.esc_bang_regexp = re.compile(r"((?P<arg1>\d+)(?P<f1>[lrwi])|" +
                                          r"(?P<f2>[LCWRJ()Z])|" +
                                          "(?P<arg3>.*)\007(?P<f3>.))")

        self.old_termios = termios.tcgetattr(self.fd)
        tty.setraw(self.fd)


    def done(self):
        """Flush all output and restore the terminal to its previous settings."""
        self.stop_formatting()
        termios.tcsetattr(self.fd, termios.TCSAFLUSH, self.old_termios)


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


    def set_term(self, term):
        """Set the terminal"""
        print("Not implemented yet")


    def text_mode(self, state):
        """Enable transcoding of characters."""
        self._bbssession_command(BBSS_TEXT)


    def binary_mode(self, state):
        """Disable transcoding when e.g. binary transmissions are happening."""
        self.stream.flush()
        self._bbssession_command(BBSS_BINARY)


    def set_size(self, cols, rows):
        """Set the terminal size."""
        self.size.x = cols
        self.size.y = rows


    def set_line_mode(self, mode, and_start_formatting=False):
        """Set the line formatting mode."""
        self.mode = mode
        if and_start_formatting:
            self.line_mode_on = True
        if mode == OUT_JUSTIFY and self.just_re is None:
            self.just_re = re.compile(r"((?:^|\s+)\S+)")


    def _emit(self, s):
        self.stream.write(s)


    def box_model_fmt(self, line, line_width):
        """Format a line in the box model and return it. The line's width in
        printable characters is provided in line_width.

        Box model:

        |    *** Lorem Ipsum                                                                     |


        |    *** Lorem ipsum dolor sit amet, consectetur
        |    *** adipiscing elit.  Suspendisse a ultrices
        |    *** arcu. Nullam vel sem non ex lacinia
        |    *** convallis.  Interdum et malesuada fames ac
        |    *** ante ipsum primis in faucibus. Morbi at
        |    *** imperdiet diam, vel vestibulum
        |    *** orci. Mauris suscipit sem vel nisl
        |    *** egestas, quis pulvinar quam
        |    *** ullamcorper. Nunc et placerat magna, in
        |    *** gravida diam. Praesent cursus egestas
        |    *** turpis. In volutpat
        
        
        |<-- Terminal width (self.size) ------------------------------------->|
        |                                                                     |
        |<- A -->|                                                            |
        |        ***                                                              |
        |                                                                     |
        |                                                                     |
        |                                                                     |
        |                                                                     |
        |                                                                     |
        +--TERMINAL-----------------------------------------------------------+

        """

    def box_model_recalc(self):
        """Recalculate the parameters of the box model."""
        
        # Start with the maximum width of the terminal.
        self.inner_width = self.size.x

        # Take away the left margin and left border
        self.inner_width -= self.left_margin + len(self.left_border)

        # Take away the right border and right margin
        self.inner_width -= len(self.right_border) + self.right_margin

        # print(f"Size.x:       {self.size.x}\r")
        # print(f"Left margin:  {self.left_margin}\r")
        # print(f"Right margin: {self.right_margin}\r")
        # print(f"Max width:    {self.max_width}\r")
        # print(f"Inner_width:  {inner_width}\r")
        # print(f"Left border:  '{self.left_border}'\r")
        # sys.exit(0)

        if self.inner_width > self.absolute_minimum_text_width:
            self.bl, self.br = self.left_border, self.right_border
            self.ml, self.mr = " " * self.left_margin, " " * self.right_margin
        else:
            # Defeat the margin/border logic if we don't have enough space for anything reasonable.
            self.bl, self.br, self.ml, self.mr = "", "", "", ""
        


    def _handle_esc_bang(self, c):
        """These custom sequences affect formatting, so we interpret them here and
        never output them to the client.

        This is the documentation from Megistos 1:

        <ESC>!<command>           or                                 
        <ESC>!<number><command>                                      
                                                                     
        These are the commands:                                      
                                                                     
        L: Start formatting text. Format mode will be left-flush.    
                                                                     
        R: Start formatting text. Format mode will be right-flush.   
                                                                     
        C: Start formatting text. Format mode will be centering.     
                                                                     
        W: Start formatting text. Format mode will be wrap-around.  This mode
           allows you to format ragged-edge text so that words are not split in
           two lines.
                                                                     
        J: Start formatting text. Format mode will be justify. This one
           produces straight-edge text from left to right border.
                                                                     
        l (lower case 'L'): Place left margin. If preceded by a number, this
           sets the left margin to <number> characters:
                                                                     
           |<--------- physical line length -------->|               
           |<-- number-->|Left Margin                |               
                                                                     
           If not preceded by a number, this command sets the left margin to
           the current cursor position.
                                                                     
        i: Works just like 'l', but sets the left margin AFTER the current line
           ('l' affects the current line too). This is useful for paragraphs
           like the one you are reading now, where an indentation is required
           for all but the first paragraph line.
                                                                     
        r: Place right margin. If preceded by a number, this sets the right
           margin to <number> characters:
                                                                     
           |<--------- physical line length -------->|               
           |               Right Margin|<-- number-->|               
                                                                     
           If not preceded by a number, this command sets the right margin to
           the current cursor position.
                                                                     
        F: If preceded by a number, this command repeats the char following it
           <number> times. That is, <esc>!10F- will format as ----------. If
           not preceded by a number, the character following the 'F' is
           repeated all the way to the right border.
                                                                     
        ( (open parenthsesis): Begin formatting using last set mode.  This
           begins formatting, starts taking into account margins, etc. When
           wrapping/justifying, use this to begin a new paragraph.
                                                                     
        ): Stop formatting. All subsequent output will be dumped to the output
           stream as-is, until another format command is encountered. Stops
           using set margins, etc. When wrap- ping/justifying, use this to end
           a paragraph so that newline characters are not transformed into
           horizontal spacing.
                                                                     
        Z: Zero the horizontal position counter. Start formatting from this
           position.
                                                                     
        v: Set parsing of variables (@VAR@-style embedded vars).  Requires a
           value. A value of 0 inhibits parsing of vars, allowing normal use of
           the '@' symbol (use this in places where the user is likely to use
           this symbol, eg pages, reading mail, etc. A non-zero value enables
           variables, giving the '@' symbol its special meaning (ie you'll have
           to use '@@' to echo '@', etc).
                                                                     
        P: Force a pause, wait for the user to press any key.

        """

        # Some ESC ! directives contain arbitrary character strings. These are
        # terminated by a \007 (BEL) character. Others contain zero or one
        # numeric arguments and are terminated by an alphanumeric character.

        # Directives with numeric arguments

        self.esc_so_far += c
        m = self.esc_bang_regexp.match(self.esc_so_far)
        if not m:
            # Stop processing after 80 characters, in case something went REALLY wrong.
            if len(self.esc_so_far) > 80:
                err = '[unterminated format sequence ESC "!' + self.esc_so_far + '"]'
                self.line_so_far += err
                self.curs.x += len(err)
                self.put_state = 0
                self.esc_so_far = ""
            return

        # So, we matched. Let's see what exactly.
        gd = m.groupdict()
        self.put_state = 0

        try:
            if gd['f1'] is not None:
                arg, f = int(gd['arg1']), gd['f1']
                if f == "l":
                    # Set left margin
                    self.left_margin = int(arg)

                elif f == "r":
                    # Set right margin
                    self.right_margin = int(arg)

                elif f == "w":
                    # Set max width
                    self.max_width = int(arg)

                elif f == "i":
                    # Set indentation
                    self.indentation = int(arg)

                self.box_model_recalc()
                    

            elif gd['f2'] is not None:
                f = gd['f2']
                
                if f == "L":
                    # Set non-wrapped left alignment (plain output)
                    self.set_line_mode(OUT_PLAIN)
                    self.line_mode_on = False

                elif f == "C":
                    # Wrap lines and centre
                    self.set_line_mode(OUT_CENTRE, and_start_formatting=True)

                elif f == "W":
                    # Wrap lines and left-align
                    self.set_line_mode(OUT_ALIGN_LEFT, and_start_formatting=True)

                elif f == "R":
                    # Wrap lines and right-align
                    self.set_line_mode(OUT_ALIGN_RIGHT, and_start_formatting=True)

                elif f == "J":
                    # Fully justification of lines.
                    self.set_line_mode(OUT_JUSTIFY, and_start_formatting=True)

                elif f == ")":
                    # Temporarily stop formatting. Output the line so far.
                    self.line_mode_on = False

                elif f == "(":
                    # Resume formatting.
                    self.line_mode_on = True

                elif f == "Z":
                    # Zero the horizontal position.
                    self.curs.x = 0

                else:
                    raise ValueError()
                
            elif gd['f3'] is not None:
                f = gd['f3']
                if f == "L":
                    self.left_border = gd['arg3']
                    self.box_model_recalc()

                elif f == "R": 
                    self.right_border = gd['arg3']
                    self.box_model_recalc()

                elif f == "F":
                    self.fill(arg)

                else:
                    pass
                    
                    
        except ValueError as e:
            err = '[invalid format sequence ESC "!' + self.esc_so_far + '"]'
            self.line_so_far += err
            self.curs.x += len(err)
            self.put_state = 0
            self.esc_so_far = ""

        # try:
        #     if self.escape_so_far:
        #         if c == "\007":
        #             # This is an arbitrary string terminator.
                    
        #         if c == "l":
        #             # Set left margin
        #             self.left_margin = int(arg)
        #             self.fmt_in_esc = False
        #         elif c == "r":
        #             # Set right margin
        #             self.right_margin = int(arg)
        #             self.fmt_in_esc = False
        #         elif c == "i":
        #             # Set right margin
        #             self.indentation = int(arg)
        #             self.fmt_in_esc = False

        #         elif c == "\007" or (c >= "0" and c <= "9"
        #             self.escape_so_far += c
        #             return
        #         else:
        #             raise ValueError()

            

        # if len(self.esc_so_far) < 2:
        #     return

        # arg = self.esc_so_far[1:-1]
        # f = self.esc_so_far[-1]
            
        # try:

        # except ValueError:
        #     self._emit('[bad format sequence ESC "' + self.esc_so_far + '"]')
        #     self.fmt_in_esc = False



    def _handle_csi(self, f):
        """Handle an accumulated ANSI X.364 CSI sequence that ends with character f.
        """
        if self.ansi_x364_mode == OUT_ANSI_X364:
            # Output as-is.
            self.line_so_far += "\033[" + self.esc_so_far + f

        elif self.ansi_x364_mode == OUT_ANSI_SYS:
            # Well, crap. It's a DOS ANSI.SYS terminal. We'll have to fake a
            # couple of things.
            if f == "J":
                self.line_so_far += "\033[J" # ANSI.SYS can't erase parts of the display.
            elif f == "K":
                self.line_so_far += "\033[K" # ANSI.SYS can't erase parts of a line.
            else:
                self.line_so_far += "\033[" + self.esc_so_far + f

        else:
            # We're stripping CSI sequences, so do nothing.
            return


    def _justify(self, s, swidth, width):
        """Fully justify the string s by adding spaces between words until it's the
        same width as width. The argument swidth is the number of visible
        characters in s. If s contains no escape sequences, this is the same as
        len(s).
        """
        parts = self.just_re.findall(s)
        num_interwords = len(parts) - 1
        if num_interwords == 0:
            return s # Can't justify a single word!

        spaces_needed = width - swidth
    
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


    def stop_formatting(self):
        """Stop formatting and output line so far."""


    def _handle_character(self, c):
        """Handle a printable or control character (anything but escape sequences.)"""
        if self.mode == OUT_PLAIN or not self.line_mode_on:
            # Are there any formatting leftovers? If so, the last line
            # of a paragraph needs to be printed. Only right alignment
            # and centre alignment need special handling here.
            if self.line_so_far:
                xdiff = self.inner_width - self.curs.x
                if self.mode == OUT_ALIGN_RIGHT:
                    line = self.line_so_far.rjust(xdiff)
                elif self.mode == OUT_CENTRE:
                    line = (" " * (xdiff // 2)) + self.line_so_far
                else:
                    line = self.line_so_far
                self._emit(self.ml + self.bl + line + self.br + self.mr + "\n\r")
                self.curs.y += 1
                self.line_so_far = ""
                
            if c == "\n":
                self._emit("\n\r")
                self.curs.newline()
            else:
                self._emit(c)
            return

        # If we need to break a line, we'll need these before they're
        # potentially updated below.
        last_space_index = self.last_space_index
        last_space_pos = self.last_space_pos

        # White space becomes space. Special spaces (e.g. non-breaking) are
        # left as-is.
        if c.isspace():
            self.line_so_far += " " # Fold white space to ASCII 32
            self.last_space_index = len(self.line_so_far)
            self.last_space_pos = self.curs.x
            #print("(((last_space_pos={})))\n\r".format(self.last_space_pos))
        else:
            self.line_so_far += c

        self.curs.x += 1

        # Do we need to wrap?
        if self.curs.x >= min(self.inner_width, self.max_width):
            # msg = "(((c='{}' curs={} --- {})))\r\n".format(c, self.curs, self.line_so_far)
            # print("{:<80.80s}".format(msg), file=sys.stderr)
            
            # Chop the string up
            line = self.line_so_far[:last_space_index - 1]
            self.line_so_far = self.line_so_far[last_space_index:]

            # Adjust the cursor position. Note, the cursor adjustment isn't the
            # same as the length of the string, because the string may include
            # invisible escape sequences that don't add to the visible
            # character count.
            self.curs.x -= last_space_pos + 1

            # OUT_ALIGN_LEFT: we don't need to do anything here.
            # OUT_ALIGN_RIGHT:
            #print("((({})))\n\r".format(last_space_pos))
            xdiff = self.inner_width - last_space_pos
            #print("((({}, {})))\n".format(xdiff, self.curs))
            if self.mode == OUT_ALIGN_RIGHT:
                line = (" " * xdiff) + line
            elif self.mode == OUT_CENTRE:
                line = (" " * (xdiff // 2)) + line
            elif self.mode == OUT_JUSTIFY:
                # Fill the line. self.last_space_pos is the number of visible
                # characters on this line, and xdiff is the desired number.
                line = self._justify(line, last_space_pos, xdiff)

            # After having wrapped the line, the line will have no
            # spaces as (by definition) we're starting it with a
            # single word. If the last character was a space, that
            # space is basically deleted and not wrapped. So, in
            # either case, we start ‘spaceless’, at -1.
            self.last_space_pos = -1
            self.last_space_idx = -1

            self._emit(self.ml + self.bl + line + self.br + self.mr + "\n\r")
            self.curs.y += 1


    def put(self, s, flush=False):
        """Output a string s."""

        # Process the string character by character. We will handle some
        # special ANSI X.364 directives ourselves, and also apply formatting
        # rules.
        #
        # This mirrors the functionality in format.c.

        for c in s:
            # Did we see an escape? This always takes us to the escape-parsing
            # state.
            if c == "\033":
                self.put_state = 1
                continue

            if self.put_state == 0:
                # Handle a plain character.
                self._handle_character(c)
                continue

            # Handle the first char after an ESC.
            if self.put_state == 1:
                if c == "[":
                    self.put_state = 2
                    self.esc_so_far = ""
                    continue

                elif c == "!":
                    self.put_state = 3
                    self.esc_so_far = ""
                    continue

                else:
                    # This is probably a two-character ANSI X.364 escape
                    # sequence. Output it to the user's terminal.
                    if self.ansi_x364_mode == OUT_ANSI_X364:
                        # But only in full X.363 mode.
                        self._emit("\033" + self.esc_so_far)
                    self.put_state = 0
                    continue

            # Handle ESC [ (CSI) control sequences.

            if self.put_state == 2:
                # CSI sequences terminate on any character >= 0x40
                if c >= "@":
                    self.put_state = 0
                    self._handle_csi(c)
                else:
                    self.esc_so_far += c

                continue

            # Handle ESC ! (Megistos formatting control sequences)
            if self.put_state == 3:
                self._handle_esc_bang(c)
                continue

        if flush:
            self.stream.flush()
            
        return


        if self.mode == OUT_PLAIN:
            return self._put_plain(s)
        else:
            # If nothing matches, just pretend we're in PLAIN mode.
            return self._put_plain(s)


    def _put_line(self, s):
        """Accumulate parts of lines and output once the line is full. This is
        used for most line-based formatting modes.

        """
        inner_width = self.size.x - self.left_margin - len(self.left_border)
        inner_width -= len(self.right_border) - self.right_border

        if inner_width > 20:
            bl, br = self.left_border, self.right_border
            ml, mr = " " * self.left_margin, " " * self.right_margin
        else:
            # Defeat the margin/border logic if we don't have enough space for anything reasonable.
            bl, br, ml, mr = "", "", "", ""


        lines = s.splitlines()
        for line in lines:
            self.line_so_far += line + " "
            
            self.curs.x += len(line)
            self.stream.write(line + "\n\r")
            self.curs.newline()
    

    def _put_plain(self, s):
        """Output plain lines without wrapping."""
        lines = s.splitlines()
        for line in lines:
            self.curs.x += len(line)
            self.stream.write(line + "\n\r")
            self.curs.newline()


# End of file.
