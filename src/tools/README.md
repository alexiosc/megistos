# Tools

Here's a list of tools used by many other modules.

* **bbsdialog** implements full-screen dialog boxes and forms. This is done using special terminal directives in such a way that the form can also be shown on dumb terminals: instead of a full-screen display, you get a serialised flow of questions.
* **checksup** performs some basic checks on the information supplied by new users signing up.
* **lined** is a line editor for dumb terminals, in the spirit of `ed` or `EDLIN.COM`, but easier to use.
* **updown** is a front-end to the `protocols` framework. Given one or more files, it selects appropriate file transfer protocols for the files (and their number) and the user, and displays a menu to allow transfer of the file.
* **vised** is a full-screen (visual) text file editor in the spirit of µEmacs or pico. It can be used to compose messages, etc. and gracefully falls back to `lined` in case of trouble. (or if the user prefers it)
