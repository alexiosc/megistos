#!/usr/bin/python3

import pytest
import megistos.colour as colour


def test_colours(capsys, tmpdir):
    """
    Test colour utilities
    """
    # p = colour.Palette.from_list(colour.CGA_PALETTE)
    # assert len(p.rgb_palette) == 16

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

    pal = colour.Palette.from_list(colour.CGA_PALETTE)
    assert len(pal.rgb_palette) == 16

    assert pal.rgb_quantise((0,0,0))       == (0, (0, 0, 0))
    assert pal.rgb_quantise((96,0,0))      == (1, (170, 0, 0))
    assert pal.rgb_quantise((180,85,85))   == (9, (255, 85, 85))
    assert pal.rgb_quantise((255,32,32))   == (9, (255, 85, 85))

    assert pal.rgb_quantise((64,64,64))    == (8, (85, 85, 85))
    assert pal.rgb_quantise((128,128,128)) == (7, (170, 170, 170))
    assert pal.rgb_quantise((255,255,255)) == (15, (255, 255, 255))
    assert pal.rgb_quantise((255,255,0))   == (11, (255, 255, 85))

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
        assert pal.rgb_quantise(colspec) == retval, \
        "Should have used {} for {}".format(name, colspec)

    with pytest.raises(ValueError):
        pal.rgb_quantise(-1)



def test_set_palette(capsys, tmpdir):
    cga_palette = [
        (  0,   0,   0), # Black
        (170,   0,   0), # Red
        (  0, 170,   0), # Green
        (170,  85,   0), # Brown
        (  0,   0, 170), # Blue
        (170,   0, 170), # Magenta
        (  0, 170, 170), # Cyan
        (170, 170, 170), # Light Grey
        ( 85,  85,  85), # Dark Grey
        (255,  85,  85), # Bright red
        ( 85, 255,  85), # Bright Green
        (255, 255,  85), # Yellow
        ( 85,  85, 255), # Bright Blue
        (255,  85, 255), # Bright Magenta
        ( 85, 255, 255), # Bright Cyan
        (255, 255, 255), # White
    ]

    bad_palette1 = ["foo"]
    bad_palette2 = [ [0,0,0], "foo" ]
    bad_palette3 = [ (0, 0, 0), (0, 0, "foo" ) ]

    # This should succeed.
    pal = colour.Palette.from_list(colour.CGA_PALETTE)
    assert pal.rgb_palette == cga_palette

    # Check that the size of the palette is in repr(), just to
    # increase test coverage. ;)
    assert str(len(pal.rgb_palette)) in repr(pal)

    # These should fail.
    with pytest.raises(ValueError):
        colour.Palette.from_list(bad_palette1)

    with pytest.raises(ValueError):
        colour.Palette.from_list(bad_palette2)

    with pytest.raises(ValueError):
        colour.Palette.from_list(bad_palette3)

    with pytest.raises(ValueError):
        colour.Palette.from_list("foo")

    with pytest.raises(ValueError):
        colour.Palette.from_list(None)

    with pytest.raises(ValueError):
        colour.Palette.from_list([1.5])


if __name__ == "__main__":
    print("Run this with pytest!")


# End of file.
