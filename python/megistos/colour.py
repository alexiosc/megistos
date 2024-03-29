#!/usr/bin/python3

from colormath.color_conversions import convert_color
from colormath.color_objects import sRGBColor, LabColor
from colormath.color_diff import delta_e_cie2000
from attr import define, field


# The web-safe colours
NAMED_COLOURS = {
    "aliceblue":             (240, 248, 255),
    "antiquewhite":          (250, 235, 215),
    "aqua":                  (  0, 255, 255),
    "aquamarine":            (127, 255, 212),
    "azure":                 (240, 255, 255),
    "beige":                 (245, 245, 220),
    "bisque":                (255, 228, 196),
    "black":                 (  0,   0,   0),
    "blanchedalmond":        (255, 235, 205),
    "blue":                  (  0,   0, 255),
    "blueviolet":            (138,  43, 226),
    "brown":                 (165,  42,  42),
    "burlywood":             (222, 184, 135),
    "cadetblue":             ( 95, 158, 160),
    "chartreuse":            (127, 255,   0),
    "chocolate":             (210, 105,  30),
    "coral":                 (255, 127,  80),
    "cornflowerblue":        (100, 149, 237),
    "cornsilk":              (255, 248, 220),
    "crimson":               (220,  20,  60),
    "cyan":                  (  0, 255, 255),
    "darkblue":              (  0,   0, 139),
    "darkcyan":              (  0, 139, 139),
    "darkgoldenrod":         (184, 134,  11),
    "darkgray":              (169, 169, 169),
    "darkgreen":             (  0, 100,   0),
    "darkgrey":              (169, 169, 169),
    "darkkhaki":             (189, 183, 107),
    "darkmagenta":           (139,   0, 139),
    "darkolivegreen":        ( 85, 107,  47),
    "darkorange":            (255, 140,   0),
    "darkorchid":            (153,  50, 204),
    "darkred":               (139,   0,   0),
    "darksalmon":            (233, 150, 122),
    "darkseagreen":          (143, 188, 143),
    "darkslateblue":         ( 72,  61, 139),
    "darkslategray":         ( 47,  79,  79),
    "darkslategrey":         ( 47,  79,  79),
    "darkturquoise":         (  0, 206, 209),
    "darkviolet":            (148,   0, 211),
    "deeppink":              (255,  20, 147),
    "deepskyblue":           (  0, 191, 255),
    "dimgray":               (105, 105, 105),
    "dimgrey":               (105, 105, 105),
    "dodgerblue":            ( 30, 144, 255),
    "firebrick":             (178,  34,  34),
    "floralwhite":           (255, 250, 240),
    "forestgreen":           ( 34, 139,  34),
    "fuchsia":               (255,   0, 255),
    "gainsboro":             (220, 220, 220),
    "ghostwhite":            (248, 248, 255),
    "goldenrod":             (218, 165,  32),
    "gold":                  (255, 215,   0),
    "gray":                  (128, 128, 128),
    "green":                 (  0, 128,   0),
    "greenyellow":           (173, 255,  47),
    "grey":                  (128, 128, 128),
    "honeydew":              (240, 255, 240),
    "hotpink":               (255, 105, 180),
    "indianred":             (205,  92,  92),
    "indigo":                ( 75,   0, 130),
    "ivory":                 (255, 255, 240),
    "khaki":                 (240, 230, 140),
    "lavenderblush":         (255, 240, 245),
    "lavender":              (230, 230, 250),
    "lawngreen":             (124, 252,   0),
    "lemonchiffon":          (255, 250, 205),
    "lightblue":             (173, 216, 230),
    "lightcoral":            (240, 128, 128),
    "lightcyan":             (224, 255, 255),
    "lightgoldenrodyellow":  (250, 250, 210),
    "lightgray":             (211, 211, 211),
    "lightgreen":            (144, 238, 144),
    "lightgrey":             (211, 211, 211),
    "lightpink":             (255, 182, 193),
    "lightsalmon":           (255, 160, 122),
    "lightseagreen":         ( 32, 178, 170),
    "lightskyblue":          (135, 206, 250),
    "lightslategray":        (119, 136, 153),
    "lightslategrey":        (119, 136, 153),
    "lightsteelblue":        (176, 196, 222),
    "lightyellow":           (255, 255, 224),
    "lime":                  (  0, 255,   0),
    "limegreen":             ( 50, 205,  50),
    "linen":                 (250, 240, 230),
    "magenta":               (255,   0, 255),
    "maroon":                (128,   0,   0),
    "mediumaquamarine":      (102, 205, 170),
    "mediumblue":            (  0,   0, 205),
    "mediumorchid":          (186,  85, 211),
    "mediumpurple":          (147, 112, 219),
    "mediumseagreen":        ( 60, 179, 113),
    "mediumslateblue":       (123, 104, 238),
    "mediumspringgreen":     (  0, 250, 154),
    "mediumturquoise":       ( 72, 209, 204),
    "mediumvioletred":       (199,  21, 133),
    "midnightblue":          ( 25,  25, 112),
    "mintcream":             (245, 255, 250),
    "mistyrose":             (255, 228, 225),
    "moccasin":              (255, 228, 181),
    "navajowhite":           (255, 222, 173),
    "navy":                  (  0,   0, 128),
    "oldlace":               (253, 245, 230),
    "olive":                 (128, 128,   0),
    "olivedrab":             (107, 142,  35),
    "orange":                (255, 165,   0),
    "orangered":             (255,  69,   0),
    "orchid":                (218, 112, 214),
    "palegoldenrod":         (238, 232, 170),
    "palegreen":             (152, 251, 152),
    "paleturquoise":         (175, 238, 238),
    "palevioletred":         (219, 112, 147),
    "papayawhip":            (255, 239, 213),
    "peachpuff":             (255, 218, 185),
    "peru":                  (205, 133,  63),
    "pink":                  (255, 192, 203),
    "plum":                  (221, 160, 221),
    "powderblue":            (176, 224, 230),
    "purple":                (128,   0, 128),
    "rebeccapurple":         (102,  51, 153),
    "red":                   (255,   0,   0),
    "rosybrown":             (188, 143, 143),
    "royalblue":             ( 65, 105, 225),
    "saddlebrown":           (139,  69,  19),
    "salmon":                (250, 128, 114),
    "sandybrown":            (244, 164,  96),
    "seagreen":              ( 46, 139,  87),
    "seashell":              (255, 245, 238),
    "sienna":                (160,  82,  45),
    "silver":                (192, 192, 192),
    "skyblue":               (135, 206, 235),
    "slateblue":             (106,  90, 205),
    "slategray":             (112, 128, 144),
    "slategrey":             (112, 128, 144),
    "snow":                  (255, 250, 250),
    "springgreen":           (  0, 255, 127),
    "steelblue":             ( 70, 130, 180),
    "tan":                   (210, 180, 140),
    "teal":                  (  0, 128, 128),
    "thistle":               (216, 191, 216),
    "tomato":                (255,  99,  71),
    "turquoise":             ( 64, 224, 208),
    "violet":                (238, 130, 238),
    "wheat":                 (245, 222, 179),
    "white":                 (255, 255, 255),
    "whitesmoke":            (245, 245, 245),
    "yellow":                (255, 255,   0),
    "yellowgreen":           (154, 205,  50),

    # The CGA colours
    #"black":                (  0,   0,   0), # Black -- already defined
    "dkred":                 (170,   0,   0), # Red
    "dkgreen":               (  0, 170,   0), # Green
    "dkbrown":               (170,  85,   0), # Brown
    "dkblue":                (  0,   0, 170), # Blue
    "dkmagenta":             (170,   0, 170), # Magenta
    "dkcyan":                (  0, 170, 170), # Cyan
    "ltgrey":                (170, 170, 170), # Light Grey
    "ltgray":                (170, 170, 170), # Light Grey
    "dkgrey":                ( 85,  85,  85), # Dark Grey
    "dkgray":                ( 85,  85,  85), # Dark Grey
    "ltred":                 (255,  85,  85), # Bright red
    "ltgreen":               ( 85, 255,  85), # Bright Green
    "ltyellow":              (255, 255,  85), # Yellow
    "ltblue":                ( 85,  85, 255), # Bright Blue
    "ltmagenta":             (255,  85, 255), # Bright Magenta
    "ltcyan":                ( 85, 255, 255), # Bright Cyan
    #"white":                (255, 255, 255), # White -- already defined
}


CGA_PALETTE = [
    [ (  0,   0,   0) ],                   # Black
    [ (170,   0,   0),  (32, 0, 0) ],      # Red
    [ (  0, 170,   0),  (0, 32, 0) ],      # Green
    [ (170,  85,   0),  (32, 32, 0) ],     # Brown
    [ (  0,   0, 170),  (0, 0, 32) ],      # Blue
    [ (170,   0, 170),  (32, 0, 32) ],     # Magenta
    [ (  0, 170, 170),  (0, 32, 32) ],     # Cyan
    [ (170, 170, 170),  (128, 128, 128) ], # Light Grey
    [ ( 85,  85,  85),  (32, 32, 32) ],    # Dark Grey
    [ (255,  85,  85),  (255, 0, 0 ) ],    # Bright Red
    [ ( 85, 255,  85),  (0, 255, 0) ],     # Bright Green
    [ (255, 255,  85),  (255, 255, 0) ],   # Yellow
    [ ( 85,  85, 255),  (0, 0, 255 ) ],    # Bright Blue
    [ (255,  85, 255),  (255, 0, 255 ) ],  # Bright Magenta
    [ ( 85, 255, 255),  (0, 255, 255 ) ],  # Bright Cyan
    [ (255, 255, 255) ],                   # White
]


XTERM256COLOUR_PALETTE = [
    (  0,   0,   0), (128,   0,   0), (  0, 128,   0), (128, 128,   0),
    (  0,   0, 128), (128,   0, 128), (  0, 128, 128), (192, 192, 192),
    (128, 128, 128), (255,   0,   0), (  0, 255,   0), (255, 255,   0),
    (  0,   0, 255), (255,   0, 255), (  0, 255, 255), (255, 255, 255),
    (  0,   0,   0), (  0,   0,  95), (  0,   0, 135), (  0,   0, 175),
    (  0,   0, 215), (  0,   0, 255), (  0,  95,   0), (  0,  95,  95),
    (  0,  95, 135), (  0,  95, 175), (  0,  95, 215), (  0,  95, 255),
    (  0, 135,   0), (  0, 135,  95), (  0, 135, 135), (  0, 135, 175),
    (  0, 135, 215), (  0, 135, 255), (  0, 175,   0), (  0, 175,  95),
    (  0, 175, 135), (  0, 175, 175), (  0, 175, 215), (  0, 175, 255),
    (  0, 215,   0), (  0, 215,  95), (  0, 215, 135), (  0, 215, 175),
    (  0, 215, 215), (  0, 215, 255), (  0, 255,   0), (  0, 255,  95),
    (  0, 255, 135), (  0, 255, 175), (  0, 255, 215), (  0, 255, 255),
    ( 95,   0,   0), ( 95,   0,  95), ( 95,   0, 135), ( 95,   0, 175),
    ( 95,   0, 215), ( 95,   0, 255), ( 95,  95,   0), ( 95,  95,  95),
    ( 95,  95, 135), ( 95,  95, 175), ( 95,  95, 215), ( 95,  95, 255),
    ( 95, 135,   0), ( 95, 135,  95), ( 95, 135, 135), ( 95, 135, 175),
    ( 95, 135, 215), ( 95, 135, 255), ( 95, 175,   0), ( 95, 175,  95),
    ( 95, 175, 135), ( 95, 175, 175), ( 95, 175, 215), ( 95, 175, 255),
    ( 95, 215,   0), ( 95, 215,  95), ( 95, 215, 135), ( 95, 215, 175),
    ( 95, 215, 215), ( 95, 215, 255), ( 95, 255,   0), ( 95, 255,  95),
    ( 95, 255, 135), ( 95, 255, 175), ( 95, 255, 215), ( 95, 255, 255),
    (135,   0,   0), (135,   0,  95), (135,   0, 135), (135,   0, 175),
    (135,   0, 215), (135,   0, 255), (135,  95,   0), (135,  95,  95),
    (135,  95, 135), (135,  95, 175), (135,  95, 215), (135,  95, 255),
    (135, 135,   0), (135, 135,  95), (135, 135, 135), (135, 135, 175),
    (135, 135, 215), (135, 135, 255), (135, 175,   0), (135, 175,  95),
    (135, 175, 135), (135, 175, 175), (135, 175, 215), (135, 175, 255),
    (135, 215,   0), (135, 215,  95), (135, 215, 135), (135, 215, 175),
    (135, 215, 215), (135, 215, 255), (135, 255,   0), (135, 255,  95),
    (135, 255, 135), (135, 255, 175), (135, 255, 215), (135, 255, 255),
    (175,   0,   0), (175,   0,  95), (175,   0, 135), (175,   0, 175),
    (175,   0, 215), (175,   0, 255), (175,  95,   0), (175,  95,  95),
    (175,  95, 135), (175,  95, 175), (175,  95, 215), (175,  95, 255),
    (175, 135,   0), (175, 135,  95), (175, 135, 135), (175, 135, 175),
    (175, 135, 215), (175, 135, 255), (175, 175,   0), (175, 175,  95),
    (175, 175, 135), (175, 175, 175), (175, 175, 215), (175, 175, 255),
    (175, 215,   0), (175, 215,  95), (175, 215, 135), (175, 215, 175),
    (175, 215, 215), (175, 215, 255), (175, 255,   0), (175, 255,  95),
    (175, 255, 135), (175, 255, 175), (175, 255, 215), (175, 255, 255),
    (215,   0,   0), (215,   0,  95), (215,   0, 135), (215,   0, 175),
    (215,   0, 215), (215,   0, 255), (215,  95,   0), (215,  95,  95),
    (215,  95, 135), (215,  95, 175), (215,  95, 215), (215,  95, 255),
    (215, 135,   0), (215, 135,  95), (215, 135, 135), (215, 135, 175),
    (215, 135, 215), (215, 135, 255), (215, 175,   0), (215, 175,  95),
    (215, 175, 135), (215, 175, 175), (215, 175, 215), (215, 175, 255),
    (215, 215,   0), (215, 215,  95), (215, 215, 135), (215, 215, 175),
    (215, 215, 215), (215, 215, 255), (215, 255,   0), (215, 255,  95),
    (215, 255, 135), (215, 255, 175), (215, 255, 215), (215, 255, 255),
    (255,   0,   0), (255,   0,  95), (255,   0, 135), (255,   0, 175),
    (255,   0, 215), (255,   0, 255), (255,  95,   0), (255,  95,  95),
    (255,  95, 135), (255,  95, 175), (255,  95, 215), (255,  95, 255),
    (255, 135,   0), (255, 135,  95), (255, 135, 135), (255, 135, 175),
    (255, 135, 215), (255, 135, 255), (255, 175,   0), (255, 175,  95),
    (255, 175, 135), (255, 175, 175), (255, 175, 215), (255, 175, 255),
    (255, 215,   0), (255, 215,  95), (255, 215, 135), (255, 215, 175),
    (255, 215, 215), (255, 215, 255), (255, 255,   0), (255, 255,  95),
    (255, 255, 135), (255, 255, 175), (255, 255, 215), (255, 255, 255),
    (  8,   8,   8), ( 18,  18,  18), ( 28,  28,  28), ( 38,  38,  38),
    ( 48,  48,  48), ( 58,  58,  58), ( 68,  68,  68), ( 78,  78,  78),
    ( 88,  88,  88), ( 96,  96,  96), (102, 102, 102), (118, 118, 118),
    (128, 128, 128), (138, 138, 138), (148, 148, 148), (158, 158, 158),
    (168, 168, 168), (178, 178, 178), (188, 188, 188), (198, 198, 198),
    (208, 208, 208), (218, 218, 218), (228, 228, 228), (238, 238, 238)
]


def parse_colour(col):
    """Parse a colour designation in various formats, and return an ``(r,
    g, b)`` triplet with values in the range 0–255.

    Raise ``ValueError`` on parse errors or sanity checks.

    You can use named colours registered in :meth:``NAMED_COLOURS``::

    >>> parse_colour("black")
    (0, 0, 0)
    >>> parse_colour("white")
    (255, 255, 255)
    >>> parse_colour("ltyellow")
    (255, 255, 85)

    You can also use 12 and 24-bit X11-style triplets::

    >>> parse_colour("#369")
    (51, 102, 153)
    >>> parse_colour("#336699")
    (51, 102, 153)

    And you can also use RGB triplets like the ones returned by this
    function::

    >>> parse_colour((51, 102, 153))
    (51, 102, 153)
    >>> parse_colour([51, 102, 153])
    (51, 102, 153)

    """
    # Easy.
    if type(col) in (list, tuple) and len(col) == 3:
        return tuple(col)

    # Try a named colour
    try:
        return NAMED_COLOURS[col.lower()]
    except AttributeError:
        raise ValueError("Failed to parse color '{}'".format(col))
    except KeyError:
        # No match. Let's try parsing an RGB triplet.
        pass

    # Parse an X11-style triplet
    if len(col) == 7 and col[0] == '#':
        # Parse #RRGGBB
        return (int(col[1:3], 16),
                int(col[3:5], 16),
                int(col[5:7], 16))
    elif len(col) == 4 and col[0] == '#':
        # Parse #RGB
        return (int(col[1], 16) * 17,
                int(col[2], 16) * 17,
                int(col[3], 16) * 17)

    raise ValueError("Failed to parse color '{}'".format(col))


@define(kw_only=True, slots=True)
class Palette:
    rgb_palette: list = field(default=None, repr=False)
    lab_palette: list = field(default=None, repr=False)
    _cache: dict = field(default=None, repr=False)

    @classmethod
    def from_list(cls, palette):
        pal = cls()
        pal.rgb_palette = []
        pal.lab_palette = []
        pal._cache = {}
        
        try:
            for index, colspec in enumerate(palette):
                # A palette list with quantisation ‘aliases’
                if type(colspec) in (tuple, list) and type(colspec[0]) in (tuple, list, str):
                    rgb = parse_colour(colspec[0])
                    pal.rgb_palette.append(rgb)
                    for col in colspec:
                        col_rgb = parse_colour(col)
                        lab = convert_color(sRGBColor(*col_rgb, is_upscaled=True), LabColor)
                        pal.lab_palette.append((index, rgb, lab))
                elif type(colspec) in (tuple, list, str):
                    rgb = parse_colour(colspec)
                    lab = convert_color(sRGBColor(*rgb, is_upscaled=True), LabColor)
                    pal.rgb_palette.append(rgb)
                    pal.lab_palette.append((index, rgb, lab))
                else:
                    raise TypeError
    
        except (ValueError, TypeError):
            raise ValueError("unable to parse palette")
    
        # import pprint
        # pprint.pprint(_lab_palette, width=200)

        return pal


    def __repr__(self):
        return "Palette({} entries)".format(len(self.rgb_palette))


    def __len__(self):
        return len(self.rgb_palette)


    def rgb_quantise(self, col):
        """Find the closest matching colour in a palette.
    
        This version uses colormath to get the distance of colours in LAB
        space for a considerably more accurate quantisation.
    
        """

        # Try a cached version first.
        try:
            return self._cache[col]
        except KeyError:
            pass
        
        try:
            colour = convert_color(sRGBColor(*col, is_upscaled=True), LabColor)
        except (TypeError, ValueError) as e:
            raise ValueError("Invalid colour triplet '{}'".format(col)) from e
    
        bestcol = None
        mindist = 1e100
        l, a, b = colour.lab_l, colour.lab_a, colour.lab_b
        for i, rgbcol, palette_colour in self.lab_palette:
            # This is a LOT slower, and doesn't give perfect results anyway.
            #dist = delta_e_cie2000(colour, palette_colour)
            dist = (l - palette_colour.lab_l) ** 2 + \
                (a - palette_colour.lab_a) ** 2 + \
                (b - palette_colour.lab_b) ** 2
    
            if dist == 0:
                return i, rgbcol
            if dist < mindist:
                mindist = dist
                bestcol = i, rgbcol

        self._cache[col] = bestcol
        return bestcol


# End of file.
