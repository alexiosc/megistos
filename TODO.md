# To do list for Megistos BBS rationalisation and modernisation

* Use unicode (or a superset thereof) for the internal representation
  of strings.

* Use XML for message blocks and other configuration files.

* emud: use `getpt(3)` or similar.

* emud: use `iconv(3)` or similar for character translation. Add an
  extra lynx-like layer for irreversible translations.

* output.c: use `termcap` and/or `terminfo` for terminal handling,
  incorporate this into the terminal question: ONLY after XML
  conversion.

* MetaBBS: rewrite using the bot infrastructure for communications
  (and libexpect for the client).

* Privilege separation.

* Write and document a sample bot.

* Document a sample module (e.g. news [it's small and supports
  virtually all options of the system]).

* URL (ftp/http) download/upload protocol.

* RSYNC download/upload protocol.

* SCP download/upload protocol.

* Dialogue box for above protocols (URL/hostname, options, username --
  password is asked for by the underlying UNIX program).

* `libmegistos/bbsdialog`: All dialogues and prompts must support
  options storage (as defaults for next time). Can be implemented
  transparently. Passwords are never recorded. Add a per-field and a
  per-dialogue flag to disable this.

* Modernise `/#`

* Write converters to generate XML config files from all old file
  formats.

* Write XML-to-MSG-to-MBK converter. We want to use the MBK format as
  our compiled config file format. It's generic enough for that
  (teleactions.msg, an automatically generated list of actions for the
  teleconferences module, proves this is possible even for
  arbitrary-length structures).

* bbslogin: modernise and rationalise (remove calls to `sh -e stty` when
  using `termios` would do).

* emud: autodetect screen size changes is signals are sent.

* gcs_global: add commands to switch terminal size/type.

* remove ANSI settings in favour of terminal type settings. Use ANSI
  settings as the ‘beginner’ mode, full terminal type as the ‘advanced’
  mode.

* Add terminal autodetection code.

* Write converters from text files/typhoon to SQL.

* Modify `msgidx` to store parsed message blocks and settings into the
  database.

* Modify `libmegistos/prompt.c` to construct the in-memory block from
  the database (at startup? Per-message as needed?)

* `mkmtree`, `menuman`: fix EXIT page

## Tasks below have been completed

* Debianise library

* Make prefixes soft.

* Use GNU build tools.

* Use I18N for built-in messages.

* menuman: separate compilation into `menuman` (module), `gcs_go` (GCS),
  and `mkmtree` (program).

* Ensure all necessary directories are built.

* `msgd`: move to a subdirectory of the emailclubs module (it needs much
  of the emailclubs infrastructure in place before it can be
  built). DONE, but used libclubhdr instead.

