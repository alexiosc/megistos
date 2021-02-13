# BBS Modules

Modules provide functionality to the BBS. Most modules work independently. Here's a list of available modules.

* **account** allows access to your account details, changing your password, basic preferences, etc. Trivia: this was the first module written for Megistos, and let's face it, it makes sense.
* **adventure** is a wrapper for [Z-Machine](https://en.wikipedia.org/wiki/Z-machine) adventure games. It'll play Infocom titles etc.
* **bulletins** allows the storage and management of bulletins—articles and other content that isn't discussion threads. The module works with the `emailclubs` module to provide bulletin support for ‘clubs’ (SIGs, groups, etc.
* **cookie** displays random quips on logout or using the `/cookie` global command.
* **emailclubs** implements private messaging, including an optional Internet email bridge. It also provides public discussion groups called Clubs. Clubs interoperate with the `bulletins`, `files` and `teleconf` modules to provide special interest bulletins/articles, file download areas, and chat rooms.
* **files** implements the file repositories, with uploads, downloads and their management. It allows for CD-ROM libraries (read-only repositories of files) as well as local files.
* **gallups** implements questionnaires with statistics.
* **graffiit** is the ‘graffiti wall’, where users can write short anonymous quips.
* **mailer** provides a [QWK](https://en.wikipedia.org/wiki/QWK_(file_format))-compatible off-line mailer. It works with the `emailclubs` and `bulletins` modules.
* **news** displays the system's latest news on login.
* **notify** is a little like a friend list. It allows users to be notified when certain people log in.
* **registry** implements users' public profiles.
* **remsys** provides a Sysop administration area for remote sysops.
* **stats** displays system statistics.
* **telecon** is similar to the Major BBS teleconferencing module. It provides for public and private chat rooms, including more intimate character-by-character chatting like the Unix `talk` utility. It also has an extension system for teleconference-based games, action verbs, and other goodies.