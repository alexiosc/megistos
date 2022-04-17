#!/usr/bin/python3

import pytest
import megistos.terminal as terminal

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


def test_terminfo_init(capsys, tmpdir):
    """Test that terminfo structures are initialised correctly."""
    for term_name, term_config in config.items():
        t = terminal.Terminal.from_config(term_name, config)
        for key, value in term_config.items():
            assert getattr(t.terminfo, key) == term_config[key], \
                "Terminfo key {} not initiliased correctly!".format(key)
        

def test_sgr_really_dumb(capsys, tmpdir):
    """Test attributes on REALLY dumb terminals. This terminal type has
    no escape sequences at all, so we should just be getting empty
    strings no matter what we request.
    """
    
    t = terminal.Terminal.from_config("really_dumb", config)
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
    
    t = terminal.Terminal.from_config("dumb", config)
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
    
    t = terminal.Terminal.from_config("cga", config)
    assert t.terminfo.has_escape_sequences == True
    assert t.terminfo.has_ansi_colours == True
    assert t.terminfo.has_colour == True
    assert t.terminfo.has_bold == True
    t.reset_attrs()

    def sgr(**kwargs):
        t.reset_attrs()
        retval = t.update_attrs(push=False, output=False, **kwargs)
        return retval

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

if __name__ == "__main__":
    print("Run this with pytest!")


# End of file.
