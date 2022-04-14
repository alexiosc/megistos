# Megistos 2 Format language

This is a very simple HTML-like language.

* Everything is in UTF-8.

* There is no DOM, and in most cases we don't care if tags are closed
  or not.

* The language controls both content and appearance and purposefully
  avoids being opinionated on this. This isn't a web browser we're
  talking to. But if you try to use the content markup, things will
  work on more terminal types without tweaking.
  

## Tags

### Block Level Tags

* `<p>`
* `<info>`
* `<warn>`
* `<error>`

### Inline tags

* `<kbd>text</kbd>`
* `<a href="URL">text</a>`

## Global Tag Attributes

These tag attributes are handled by every tag and set output
attributes (text appearance) for the content of the tag, unless of
course they are overridden by other similar attributes inside the tag.

Note that not all attributes are supported everywhere.

* `fg="COLOR"`: set the foreground colour.
* `bg="COLOR"`: set the background colour.
* `bold="(1|0)"`: enable or disabled bold. On terminals that handle
  bold properly, this enables an actual boldface. On terminals like
  emulated IBM textmodes where ‘bold’ is really a brighter colour,
  bold does nothing.
* `underline="(1|0)"`: enable or disabled underline text.
* `blink="(1|0")`: enable or disable blinking characters.
* `inverse="(1|0")`: enable or disable inverse video: the foreground
  and background are reversed temporarily. Note that this may not
  behave as expected on some terminals, notably those that have
  different numbers of colours for the foreground and background.
* `italic="(1|0")`: enable or disable the italic font.
* `strikethrough="(1|0")`: enable or disable the strikethrough font.

	
### Colours

Colours can be specified as:

* Indices 0-7 or 0-15. These match the ANSI X.364 colours.
* Names.
* The X11-style colour specification known from the web: `#000` or
  `#000000`.
* There are 16 named colours, too.

ANSI X.364 colours (with equivalent IBM CGA RGB triplets) are listed
below.

|--------|-----------|------|
| Number | Name      | RGB  |
|--------|-----------|------|
| 0      | black     | #000 |
| 1      | red       | #a00 |
| 2      | green     | #0a0 |
| 3      | brown     | #a50 |
| 4      | blue      | #00a |
| 5      | magenta   | #a0a |
| 6      | cyan      | #aa0 |
| 7      | ltgrey    | #aaa |
| 8      | dkgrey    | #555 |
| 9      | ltred     | #f00 |
| 10     | ltgreen   | #0f0 |
| 11     | yellow    | #ff0 |
| 12     | ltblue    | #00f |
| 13     | ltmagenta | #f0f |
| 14     | ltcyan    | #ff0 |
| 15     | white     | #fff |


## Entities and Characters

Standard HTML entity references like `&amp;` (&) or `&lt;` (<) or
`&aacute;` (á) work.

HTML character references like `&#64;` → `@` (decimal) or `&#x7e;` →
`~` (hexadecimal) work. These reference Unicode codepoints.

**TODO**: (maybe) add BBS-oriented entities by name, like block graphics etc.

## Styling

Simple stylesheets are defined in YAML for each terminal. These
stylesheets are based on the simplifying assumption that all terminals
use roughly the same escape sequencces. This isn't quite true, but
most common terminal types are more or less compatible with the X.364
standard and we can get away with it.

Stylesheets are defined per terminal type, and contain entries
matching tags.

`
styles:
  - ansi:
      p:
	    reset
      kbd:
	    fg: yellow
		bold: 1
	  info:
	    fg: ltgreen
		bold: 1
	  em:
	    italic: 1
	  em:
	    inside: em
		italic: 0

`