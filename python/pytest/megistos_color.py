#!/usr/bin/python3

import pytest
import megistos.colour as colour


def test_colours(capsys, tmpdir):
    """
    Test colour utilities
    """
    # Test basic named colours
    assert colour.parse_colour("white") == (255, 255, 255)
    assert colour.parse_colour("WHITE") == (255, 255, 255)
    assert colour.parse_colour("ltyellow") == (255, 255, 85)

    # Test CGA colours
    assert colour.parse_colour("black") == (0, 0, 0)
    assert colour.parse_colour("dkred") == (170, 0, 0)
    assert colour.parse_colour("dkbrown") == (170, 85,  0)
    assert colour.parse_colour("dkblue") == (0,  0, 170)
    assert colour.parse_colour("dkmagenta") == (170,  0, 170)
    assert colour.parse_colour("dkcyan") == (0, 170, 170)
    assert colour.parse_colour("ltgrey") == (170, 170, 170)
    assert colour.parse_colour("ltgray") == (170, 170, 170)
    assert colour.parse_colour("dkgrey") == (85, 85, 85)
    assert colour.parse_colour("dkgray") == (85, 85, 85)
    assert colour.parse_colour("ltred") == (255, 85, 85)
    assert colour.parse_colour("ltgreen") == (85, 255, 85)
    assert colour.parse_colour("ltyellow") == (255, 255, 85)
    assert colour.parse_colour("ltblue") == (85, 85, 255)
    assert colour.parse_colour("ltmagenta") == (255, 85, 255)
    assert colour.parse_colour("ltcyan") == (85, 255, 255)
    assert colour.parse_colour("white") == (255, 255, 255)

    assert colour.parse_colour("#369") == (51, 102, 153)
    assert colour.parse_colour("#336699") == (51, 102, 153)

    assert colour.parse_colour((51, 102, 153)) == (51, 102, 153)
    assert colour.parse_colour([51, 102, 153]) == (51, 102, 153)

    for bad_value in ["foo", "#36", "#11223344", "#", "", False, None,
                      (1, 2), [1, 2]]:
        with pytest.raises(ValueError):
            colour.parse_colour(bad_value)


def test_quantisation(capsys, tmpdir):
    """
    Test colours are quantised as we expect.
    """

    colour.set_palette(colour.CGA_PALETTE)
    assert colour.rgb_quantise((0,0,0))       == (0, (0, 0, 0))
    assert colour.rgb_quantise((96,0,0))      == (1, (170, 0, 0))
    assert colour.rgb_quantise((180,85,85))   == (9, (255, 85, 85))
    assert colour.rgb_quantise((255,32,32))   == (9, (255, 85, 85))

    assert colour.rgb_quantise((64,64,64))    == (8, (85, 85, 85))
    assert colour.rgb_quantise((128,128,128)) == (7, (170, 170, 170))
    assert colour.rgb_quantise((255,255,255)) == (15, (255, 255, 255))
    assert colour.rgb_quantise((255,255,0))   == (11, (255, 255, 85))

    # Test common approximations, likely to be used in stylesheets.
    approx = [
        [ (96, 0, 0), "Dark red", (1, (170, 0, 0)) ],
        [ (128, 0, 0), "Dark red", (1, (170, 0, 0)) ],
        [ (192, 0, 0), "Dark red", (1, (170, 0, 0)) ],
        [ (0, 96, 0), "Dark green", (2, (0, 170, 0)) ],
        [ (0, 128, 0), "Dark green", (2, (0, 170, 0)) ],
        [ (0, 192, 0), "Dark green", (2, (0, 170, 0)) ],
        [ (0, 0, 96), "Dark blue", (4, (0, 0, 170)) ],
        [ (0, 0, 128), "Dark blue", (4, (0, 0, 170)) ],
        [ (0, 0, 192), "Dark blue", (4, (0, 0, 170)) ],

        [ (255, 32, 32), "Bright red", (9, (255, 85, 85)) ],
        [ (255, 64, 64), "Bright red", (9, (255, 85, 85)) ],
        [ (0, 255, 0), "Bright green", (10, (85, 255, 85)) ],
        [ (32, 255, 32), "Bright green", (10, (85, 255, 85)) ],
        [ (64, 255, 64), "Bright green", (10, (85, 255, 85)) ],
        [ (128, 255, 128), "Bright green", (10, (85, 255, 85)) ],
        [ (255, 255, 0), "Yellow", (11, (255, 255, 85)) ],
        [ (255, 255, 32), "Yellow", (11, (255, 255, 85)) ],
        [ (255, 255, 64), "Yellow", (11, (255, 255, 85)) ],
        [ (255, 255, 128), "Yellow", (11, (255, 255, 85)) ],
        [ (0, 0, 255), "Bright Blue", (12, (85, 85, 255)) ],
        [ (32, 32, 255), "Bright Blue", (12, (85, 85, 255)) ],
        [ (64, 64, 255), "Bright Blue", (12, (85, 85, 255)) ],
        [ (128, 128, 255), "Bright Blue", (12, (85, 85, 255)) ],
        [ (255, 0, 255), "Bright magenta", (13, (255, 85, 255)) ],
        [ (255, 32, 255), "Bright magenta", (13, (255, 85, 255)) ],
        [ (255, 64, 255), "Bright magenta", (13, (255, 85, 255)) ],
        [ (255, 128, 255), "Bright magenta", (13, (255, 85, 255)) ],
        [ (0, 255, 255), "Bright cyan", (14, (85, 255, 255)) ],
        [ (32, 255, 255), "Bright cyan", (14, (85, 255, 255)) ],
        [ (64, 255, 255), "Bright cyan", (14, (85, 255, 255)) ],
        [ (128, 255, 255), "Bright cyan", (14, (85, 255, 255)) ],

        [ (32, 32, 32), "Dark Grey", (8, (85, 85, 85)) ],
        [ (64, 64, 64), "Dark Grey", (8, (85, 85, 85)) ],
        [ (128, 128, 128), "Light Grey", (7, (170, 170, 170)) ],
        [ (192, 192, 192), "Light Grey", (7, (170, 170, 170)) ],
        [ (255, 255, 255), "White", (15, (255, 255, 255)) ],
    ]

    for colspec, name, retval in approx:
        assert colour.rgb_quantise(colspec) == retval, \
        "Should have used {} for {}".format(name, colspec)


if __name__ == "__main__":
    print("Run this with pytest!")


# End of file.
