#!/usr/bin/env python3

import megistos.format
import megistos.terminal
import megistos.config as megistos_config
import sys
import pprint
import textwrap


###############################################################################
#
# TEST JUST THE WRAPPER CLASS
#
###############################################################################

print("Testing Wrapper class.\n")

w = megistos.terminal.Wrapper(indent=0, width=30)
w.start_paragraph()
w.write("""(0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789)""")

w.write("""Reformat the single """)
w.write_escape_sequence("\033[4m")
w.write("paragraph in 'text'")
w.write_escape_sequence("\033[0m")
w.write(""" so it fits in lines of
         no more than 'self.width' columns, and return a list of wrapped
lines.  Tabs in 'text' are expanded with string.expandtabs(),
and all other whitespace characters (including newline) are
converted to space.""")

#pprint.pprint(w.end_paragraph(), width=200)

print("         ", "=" * w.width)
for num, (length, line) in enumerate(w.end_paragraph(), 1):
    print(f'{num:>2}. l={length:>2} "{line}"')
print("         ", "=" * w.width)


###############################################################################
#
# TEST THE WHOLE TERMINAL
#
###############################################################################

print("\n\nTesting Terminal class.\n")

fe = megistos.format.FormatterEngine()
#fe.load_config()

fe.set_term("ansi")
fe.load_style("styles.yaml")
term = fe.terminal

print("Testing SGR generation")
term = fe.terminal
print("Test                            SGR")
print("-------------------------------------------------------------------------------")
def sgr_test(what, b):
    sgr = term.get_sgr(True, term.DEFAULT_ATTRS, b)
    print("\033[;1m{:30.30s}\033[0m  \"{}\"".format(what, sgr.replace("\033", "ESC ")))

sgr_test("Just Reset", bytearray((0xaa, 0xaa, 0xaa, 0, 0, 0, 0)))
sgr_test("Bold", bytearray((0xaa, 0xaa, 0xaa, 0, 0, 0, term.BOLD)))
sgr_test("Inverse", bytearray((0xaa, 0xaa, 0xaa, 0, 0, 0, term.INVERSE)))
sgr_test("Bold red", bytearray((0xff, 0, 0, 0, 0, 0, term.BOLD)))
sgr_test("Bright red", bytearray((0xff, 0, 0, 0, 0, 0, 0)))

print("\n")

print("Testing attributes\n")
print("Test                            SGR")
print("-------------------------------------------------------------------------------")
def attr_test(what, **kwargs):
    sgr = term.update_attrs(output=False, **kwargs)
    print("\033[;1m{:30.30s}\033[0m  \"{}\"".format(what, sgr.replace("\033", "ESC ")))

attr_test("Just Reset", reset=True)
attr_test("Reset & bold", reset=True, bold=True)
attr_test("Bold Red", bold=True, fg=(255,0,0))


print("Testing inline styles.\n")

fe.write("This is a test.\n")
fe.write("<em>This is a <b>test</b>. This no longer bold.</em>\n")

print("\nTesting block handling (wrapped and formatted)\n")

print("-"*80)
fe.write("""<format max-width="40" indent="4" margin-bottom=1 margin-left="0" margin-right="0" align="j">
<p>The licenses for most software and other practical works are designed
<span bg="#222222" fg="#ff9999">to take away</span> your freedom to share and change the works. By contrast,
the <b>GNU General Public License</b> is intended to <em>guarantee</em> your freedom to
share and change all versions of a program--to make sure it remains free
software for all its users.  We, the Free Software Foundation, use the
GNU General Public License for most of our software; it applies also to
any other work released this way by its authors.  You can apply it to
your programs, too.

<p>

<b>When we speak of free software</b>, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
them if you wish), that you receive source code or can get it if you
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.

<p>To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights.  Therefore, you have
certain responsibilities if you distribute copies of the software, or if
you modify it: responsibilities to respect the freedom of others.

</format>""")
print("-"*80)