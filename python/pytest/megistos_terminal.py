#!/usr/bin/python3

import pytest
import megistos.terminal as terminal
import megistos.colour as colour

# Simulate a standard CGA/EGA/VGA text mode
config = {
    "really_dumb": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": False
    },
    "dumb": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": True,
        "has_ansi_colours": False,
        "can_reposition_cursor": False,
        "can_turn_off_attrs": False,
    },
    "cga": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": True,
        "has_ansi_colours": True,
        "can_reposition_cursor": True,
        "can_turn_off_attrs": False,
        "has_bold": True, # not really, but it'sconvention to call it bold
        "has_blink": True,
        "has_inverse": True,
    },
    "vt220": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": True,
        "has_16_colours": True, 
        "can_reposition_cursor": True,
        "can_turn_off_attrs": True,
        "has_bold": True, # not really, but it'sconvention to call it bold
        "has_blink": True,
        "has_italic": True,
        "has_underline": True,
        "has_blink": True,
        "has_inverse": True,
        "has_invisible": True,
        "has_strikethrough": True,
    },
    "256colour": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": True,
        "has_256_colours": True, 
        "can_reposition_cursor": True,
        "can_turn_off_attrs": True,
        "has_bold": True, # not really, but it'sconvention to call it bold
        "has_blink": True,
        "has_italic": True,
        "has_underline": True,
        "has_blink": True,
        "has_inverse": True,
        "has_invisible": True,
        "has_strikethrough": True,
    },
    "truecolour": {
        "cols": 80, "rows": 25,
        "has_escape_sequences": True,
        "has_truecolour": True, 
        "can_reposition_cursor": True,
        "can_turn_off_attrs": False,
        "has_bold": True, # not really, but it'sconvention to call it bold
        "has_blink": True,
        "has_italic": True,
        "has_underline": True,
        "has_blink": True,
        "has_inverse": True,
        "has_invisible": True,
        "has_strikethrough": True,
    },
    # This terminal sets everything to non-default values, so we can
    # check initialisation is happening on all properties.
    "christmas_tree": {
        "cols": 91, "rows": 87,
        "has_escape_sequences": False,
        "can_turn_off_attrs": False,
        "can_reposition_cursor": True,
        "has_ansi_colours": True,
        "has_16_colours": True, 
        "has_256_colours": True, 
        "has_truecolour": True, 
        "has_bold": True,
        "has_dim": True,
        "has_italic": True,
        "has_underline": True,
        "has_blink": True,
        "has_inverse": True,
        "has_invisible": True,
        "has_strikethrough": True,
    },
    "reverse_christmas_tree": {
        "cols": 91, "rows": 87,
        "has_escape_sequences": True,
        "can_turn_off_attrs": True,
        "can_reposition_cursor": False,
        "has_ansi_colours": False,
        "has_16_colours": False, 
        "has_256_colours": False, 
        "has_truecolour": False, 
        "has_bold": False,
        "has_dim": False,
        "has_italic": False,
        "has_underline": False,
        "has_blink": False,
        "has_inverse": False,
        "has_invisible": False,
        "has_strikethrough": False,
    }
}


def test_rgb2sgr_cga(capsys, tmpdir):
    """Provide good coverage of rgb2sgr."""
    t = terminal.Terminal.from_config("cga", config["cga"])
    assert t.rgb2sgr("") == ""
    assert t.rgb2sgr("\033[0;1;32m") == "\033[0;1;32m"
    assert t.rgb2sgr("10") == "10"

    assert t.rgb2sgr((0,0,0), fg=False) == "40"
    assert t.rgb2sgr((255,0,0), fg=False) == "41"
    assert t.rgb2sgr((0,255,0), fg=False) == "42"
    assert t.rgb2sgr((255,255,0), fg=False) == "43"
    assert t.rgb2sgr((0,0,255), fg=False) == "44"
    assert t.rgb2sgr((255,0,255), fg=False) == "45"
    assert t.rgb2sgr((0,255,255), fg=False) == "46"
    assert t.rgb2sgr((255,255,255), fg=False) == "47"

    assert t.rgb2sgr((0,0,0), fg=True) == "30"
    assert t.rgb2sgr((255,0,0), fg=True) == "1;31"
    assert t.rgb2sgr((0,255,0), fg=True) == "1;32"
    assert t.rgb2sgr((255,255,0), fg=True) == "1;33"
    assert t.rgb2sgr((0,0,255), fg=True) == "1;34"
    assert t.rgb2sgr((255,0,255), fg=True) == "1;35"
    assert t.rgb2sgr((0,255,255), fg=True) == "1;36"
    assert t.rgb2sgr((255,255,255), fg=True) == "1;37"


def test_rgb2sgr_vt220(capsys, tmpdir):
    """Provide good coverage of rgb2sgr."""
    colour._rgb_palette = []
    colour._lab_palette = []
    t = terminal.Terminal.from_config("vt220", config["vt220"])
    assert len(t.terminfo.palette.rgb_palette) == 16

    assert t.rgb2sgr("") == ""
    assert t.rgb2sgr("\033[0;1;32m") == "\033[0;1;32m"
    assert t.rgb2sgr("10") == "10"

    assert t.rgb2sgr((0,0,0), fg=True) == "30"
    assert t.rgb2sgr((128,0,0), fg=True) == "31"
    assert t.rgb2sgr((0,128,0), fg=True) == "32"
    assert t.rgb2sgr((128,128,0), fg=True) == "33"
    assert t.rgb2sgr((0,0,128), fg=True) == "34"
    assert t.rgb2sgr((128,0,128), fg=True) == "35"
    assert t.rgb2sgr((0,128,128), fg=True) == "36"
    assert t.rgb2sgr((128,128,128), fg=True) == "37"

    assert t.rgb2sgr((0,0,0), fg=False) == "40"
    assert t.rgb2sgr((128,0,0), fg=False) == "41"
    assert t.rgb2sgr((0,128,0), fg=False) == "42"
    assert t.rgb2sgr((128,128,0), fg=False) == "43"
    assert t.rgb2sgr((0,0,128), fg=False) == "44"
    assert t.rgb2sgr((128,0,128), fg=False) == "45"
    assert t.rgb2sgr((0,128,128), fg=False) == "46"
    assert t.rgb2sgr((128,128,128), fg=False) == "47"

    assert t.rgb2sgr((85,85,85), fg=False) == "100"
    assert t.rgb2sgr((255,0,0), fg=False) == "101"
    assert t.rgb2sgr((0,255,0), fg=False) == "102"
    assert t.rgb2sgr((255,255,0), fg=False) == "103"
    assert t.rgb2sgr((0,0,255), fg=False) == "104"
    assert t.rgb2sgr((255,0,255), fg=False) == "105"
    assert t.rgb2sgr((0,255,255), fg=False) == "106"
    assert t.rgb2sgr((255,255,255), fg=False) == "107"

    assert t.rgb2sgr((85,85,85), fg=True) == "90"
    assert t.rgb2sgr((255,0,0), fg=True) == "91"
    assert t.rgb2sgr((0,255,0), fg=True) == "92"
    assert t.rgb2sgr((255,255,0), fg=True) == "93"
    assert t.rgb2sgr((0,0,255), fg=True) == "94"
    assert t.rgb2sgr((255,0,255), fg=True) == "95"
    assert t.rgb2sgr((0,255,255), fg=True) == "96"
    assert t.rgb2sgr((255,255,255), fg=True) == "97"


def test_rgb2sgr_256colour(capsys, tmpdir):
    """Provide good coverage of rgb2sgr."""
    t = terminal.Terminal.from_config("256colour", config["256colour"])
    assert len(t.terminfo.palette.rgb_palette) == 256
    
    assert t.rgb2sgr("") == ""
    assert t.rgb2sgr("\033[0;1;32m") == "\033[0;1;32m"
    assert t.rgb2sgr("10") == "10"

    assert t.rgb2sgr((0,0,0), fg=True) == "38;5;0"
    assert t.rgb2sgr((128,0,0), fg=True) == "38;5;1"
    assert t.rgb2sgr((0,128,0), fg=True) == "38;5;2"
    assert t.rgb2sgr((128,128,0), fg=True) == "38;5;3"
    assert t.rgb2sgr((0,0,128), fg=True) == "38;5;4"
    assert t.rgb2sgr((128,0,128), fg=True) == "38;5;5"
    assert t.rgb2sgr((0,128,128), fg=True) == "38;5;6"
    assert t.rgb2sgr((0xc0, 0xc0, 0xc0), fg=True) == "38;5;7"

    assert t.rgb2sgr((0,0,0), fg=False) == "48;5;0"
    assert t.rgb2sgr((128,0,0), fg=False) == "48;5;1"
    assert t.rgb2sgr((0,128,0), fg=False) == "48;5;2"
    assert t.rgb2sgr((128,128,0), fg=False) == "48;5;3"
    assert t.rgb2sgr((0,0,128), fg=False) == "48;5;4"
    assert t.rgb2sgr((128,0,128), fg=False) == "48;5;5"
    assert t.rgb2sgr((0,128,128), fg=False) == "48;5;6"
    assert t.rgb2sgr((192,192,192), fg=False) == "48;5;7"

    assert t.rgb2sgr((128,128,128), fg=False) == "48;5;8"
    assert t.rgb2sgr((255,0,0), fg=False) == "48;5;9"
    assert t.rgb2sgr((0,255,0), fg=False) == "48;5;10"
    assert t.rgb2sgr((255,255,0), fg=False) == "48;5;11"
    assert t.rgb2sgr((0,0,255), fg=False) == "48;5;12"
    assert t.rgb2sgr((255,0,255), fg=False) == "48;5;13"
    assert t.rgb2sgr((0,255,255), fg=False) == "48;5;14"
    assert t.rgb2sgr((255,255,255), fg=False) == "48;5;15"

    assert t.rgb2sgr((128,128,128), fg=True) == "38;5;8"
    assert t.rgb2sgr((255,0,0), fg=True) == "38;5;9"
    assert t.rgb2sgr((0,255,0), fg=True) == "38;5;10"
    assert t.rgb2sgr((255,255,0), fg=True) == "38;5;11"
    assert t.rgb2sgr((0,0,255), fg=True) == "38;5;12"
    assert t.rgb2sgr((255,0,255), fg=True) == "38;5;13"
    assert t.rgb2sgr((0,255,255), fg=True) == "38;5;14"
    assert t.rgb2sgr((255,255,255), fg=True) == "38;5;15"

    # Spot-test a few of the extra colours
    assert t.rgb2sgr((0, 0x5f, 0), fg=True) == "38;5;22"
    assert t.rgb2sgr((0, 0x87, 0xff), fg=True) == "38;5;33"
    assert t.rgb2sgr((0xdf, 0xdf, 0), fg=True) == "38;5;184"
    assert t.rgb2sgr((0xd7, 0, 0), fg=True) == "38;5;160"
    assert t.rgb2sgr((0x87, 0xaf, 0xff), fg=True) == "38;5;111"
    assert t.rgb2sgr((0x5f, 0xd7, 0x87), fg=True) == "38;5;78"


def test_rgb2sgr_truecolour(capsys, tmpdir):
    """Provide good coverage of rgb2sgr."""
    t = terminal.Terminal.from_config("cga", config["cga"])
    # Test true-colour support. soup

    t = terminal.Terminal.from_config("truecolour", config["truecolour"])
    assert t.rgb2sgr("") == ""
    assert t.rgb2sgr("\033[0;1;32m") == "\033[0;1;32m"
    assert t.rgb2sgr("10") == "10"
    assert t.rgb2sgr((11,22,33), fg=True) == "38;2;11;22;33"
    assert t.rgb2sgr((11,22,33), fg=False) == "48;2;11;22;33"
    


def test_terminfo_init(capsys, tmpdir):
    """Test that terminfo structures are initialised correctly."""
    for term_name, term_config in config.items():
        t = terminal.Terminal.from_config(term_name, config[term_name])
        for key, value in term_config.items():
            assert getattr(t.terminfo, key) == term_config[key], \
                "Terminfo key {} not initiliased correctly!".format(key)
        

def test_sgr_really_dumb(capsys, tmpdir):
    """Test attributes on REALLY dumb terminals. This terminal type has
    no escape sequences at all, so we should just be getting empty
    strings no matter what we request.
    """
    
    t = terminal.Terminal.from_config("really_dumb", config["really_dumb"])
    assert t.terminfo.has_escape_sequences == False
    t.reset_attrs()
    for reset in (True, False):
        for x in range(256):
            t.attrs[6] = x
            assert t.get_sgr(reset, t.DEFAULT_ATTRS, t.attrs) == ""

        sgr = t.update_attrs(push=False, output=False, reset=reset, fg=(255,0,0))
        assert sgr == ""
        sgr = t.update_attrs(push=False, output=False, reset=reset, bg=(255,0,0))
        assert sgr == ""


def test_sgr_dumb(capsys, tmpdir):
    """Test attributes on REALLY dumb terminals. This terminal type has
    no escape sequences at all, so we should just be getting empty
    strings no matter what we request.
    """
    
    t = terminal.Terminal.from_config("dumb", config["dumb"])
    assert t.terminfo.has_escape_sequences == True
    assert t.terminfo.has_colour == False
    assert t.terminfo.has_bold == False
    t.reset_attrs()
    for x in range(256):
        t.attrs[6] = x
        assert t.get_sgr(False, t.DEFAULT_ATTRS, t.attrs) == "", \
            "Non-empty SGR generated. reset=False, x={:08b}".format(x)
        assert t.get_sgr(True, t.DEFAULT_ATTRS, t.attrs) == "\033[0m", \
            "Non-empty SGR generated. reset=True, x={:08b}".format(x)

    sgr = t.update_attrs(push=False, output=False, reset=False, fg=(255,0,0))
    assert sgr == ""
    sgr = t.update_attrs(push=False, output=False, reset=True, fg=(255,0,0))
    assert sgr == "\033[0m"


def test_cga(capsys, tmpdir):
    """Test attributes on REALLY dumb terminals. This terminal type has
    no escape sequences at all, so we should just be getting empty
    strings no matter what we request.
    """
    
    t = terminal.Terminal.from_config("cga", config["cga"])
    assert t.terminfo.has_escape_sequences == True
    assert t.terminfo.has_ansi_colours == True
    assert t.terminfo.has_colour == True
    assert t.terminfo.has_bold == True
    t.reset_attrs()

    def sgr(**kwargs):
        t.reset_attrs()
        retval = t.update_attrs(push=False, output=False, **kwargs)
        return retval

    assert sgr() == ""

    assert sgr(reset=True, fg=(170,170,170)) in ("\033[0;37m", "\033[0m")
    assert sgr(reset=True, fg=(255,0,0)) == "\033[0;1;31m"
    assert sgr(reset=True, fg=(192,0,0)) == "\033[0;31m"
    assert sgr(reset=True, fg=(128,0,0)) == "\033[0;31m"

    assert sgr(reset=True, fg=(0,255,0)) == "\033[0;1;32m"
    assert sgr(reset=True, fg=(0,192,0)) == "\033[0;32m"
    assert sgr(reset=True, fg=(0,128,0)) == "\033[0;32m"

    assert sgr(reset=True, fg=(255,255,0)) == "\033[0;1;33m"
    assert sgr(reset=True, fg=(192,192,0)) == "\033[0;1;33m" # There's no dark yellow!
    assert sgr(reset=True, fg=(128,128,0)) == "\033[0;33m"

    assert sgr(reset=True, fg=(0,0,255)) == "\033[0;1;34m"
    assert sgr(reset=True, fg=(0,0,192)) == "\033[0;34m"
    assert sgr(reset=True, fg=(0,0,128)) == "\033[0;34m"

    assert sgr(reset=True, fg=(255,0,255)) == "\033[0;1;35m"
    assert sgr(reset=True, fg=(192,0,192)) == "\033[0;35m"
    assert sgr(reset=True, fg=(128,0,128)) == "\033[0;35m"

    assert sgr(reset=True, fg=(0,255,255)) == "\033[0;1;36m"
    assert sgr(reset=True, fg=(0,192,192)) == "\033[0;36m"
    assert sgr(reset=True, fg=(0,128,128)) == "\033[0;36m"



    assert sgr(reset=False, fg=(0,255,0)) == "\033[1;32m"
    assert sgr(reset=False, fg=(0,192,0)) == "\033[32m"
    assert sgr(reset=False, fg=(0,128,0)) == "\033[32m"

    assert sgr(reset=False, fg=(255,255,0)) == "\033[1;33m"
    assert sgr(reset=False, fg=(192,192,0)) == "\033[1;33m" # There's no dark yellow!
    assert sgr(reset=False, fg=(128,128,0)) == "\033[33m"

    assert sgr(reset=False, fg=(0,0,255)) == "\033[1;34m"
    assert sgr(reset=False, fg=(0,0,192)) == "\033[34m"
    assert sgr(reset=False, fg=(0,0,128)) == "\033[34m"

    assert sgr(reset=False, fg=(255,0,255)) == "\033[1;35m"
    assert sgr(reset=False, fg=(192,0,192)) == "\033[35m"
    assert sgr(reset=False, fg=(128,0,128)) == "\033[35m"

    assert sgr(reset=False, fg=(0,255,255)) == "\033[1;36m"
    assert sgr(reset=False, fg=(0,192,192)) == "\033[36m"
    assert sgr(reset=False, fg=(0,128,128)) == "\033[36m"

    assert sgr(reset=True, bold=True) == "\033[0;1m"
    assert sgr(reset=True, dim=True) == "\033[0m" # CGA can't do dim!
    assert sgr(reset=True, italic=True) == "\033[0m" # ...or italic
    assert sgr(reset=True, underline=True) == "\033[0m" # (there's not much it CAN do, really)
    assert sgr(reset=True, blink=True) == "\033[0;5m"   # But it can blink!
    assert sgr(reset=True, inverse=True) == "\033[0;7m"   # And do reverse video.



text = """The licenses for most software and other practical works are
designed to take away your freedom to share and change the works. By
contrast, the GNU General Public License is intended to guarantee your
freedom to share and change all versions of a program--to make sure it
remains free software for all its users."""


def test_wrapper(capsys, tmpdir):

    for width in range(20, 200, 5):
        w = terminal.Wrapper(indent=0, width=width)
        w.start_paragraph()
        w.write(text)
        res = w.end_paragraph()

        import pprint
        pprint.pprint(res, width=200)
        for linelen, line in res:
            assert type(linelen) == int
            assert linelen <= width

        # Reconstruct the text and make sure it's still intacct
        assert " ".join(x[1] for x in res) == text.replace("\n", " "), \
            "Reconstructed text was not broken properly."

if __name__ == "__main__":
    print("Run this with pytest!")


# End of file.
