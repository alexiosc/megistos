# The Emulation Dæmon

## What is ‘Emulation’?

*Emulation* is a Major BBS term. It's a Sysop function that allows them to ‘ride’ a user's session for help or technical support. They can see what the user is seeing and type for the user. It's the BBS equivalent of something like TeamViewer.

Linux doesn't readily do this, so we must provide an additional dæmon that sits between the hardware TTY and the BBS to allow I/O to be intercepted.

## What does it do?

The original `emud` provides a couple of kludgy ring buffers so Sysops can *emulate* Users.

While it's at it, and because of its very privileged place in the TTY↔BBS pipeline, the `emud` performs a number of other tasks:

1. It provides **lossy character translation**. For example, if the user is using a 7-bit plain ASCII terminal, `emud` will translate box drawing characters to ASCII characters.
1. It implements session timeouts.
1. It handles the `injoth()` mechanism, where one user's process can write to another's output (e.g. for pages, notifications, etc.)

## Plans

It's oh so kludgy! I think I was in a hurry to get something working, and I must have suddenly realised I didn't have the Unix programming skills to get this done back in 1995, so it's messy as.

To make things better, let's move a bunch of other functions over to the emud:

* Session capturing for the user: saves the user's session to a local file, which the user can then download later. Done by telecoms software, but not many people use those these days.
* Better encoding translation support: all of Megistos should be UTF-8 now that everything's decided on that as a standard encoding. It's up to `emud` to translate the the target encoding. Mechanisms for doing this include GNU `iconv`, the [unidecode](https://github.com/avian2/unidecode) library, and custom translation tables. (e.g. for the weird, custom encodings of some 8-bit micros, *cough***Commodore***cough*)
* Handle session termination directly. (e.g. user kicked out)
* Handle per-minute credit charges and update system-wide statistics *somehow*, possibly by messaging `bbsd` every minute.
* Handle session *lengths* in addition to timeouts (e.g. user running out of credits)
* Perform input translation from the input encoding to UTF-8. The BBS should only be receiving UTF-8 characters.
* **Tentative**: handle paging (the ‘Continue?’ message when a full page is printed). This requires two things:
  * Two-way communication between BBS and `emud` (e.g. when the user stops the listing, `emud` will need to let `libmesgistos` know, which will need to stop the listing.
  * Calls to notify `emud` of the user's terminal size. Due to our privileged placement right next to the TTY file descriptors, we can also get notifications (`SIGWINCH`) from the kernel about the size of the terminal if it runs in a GUI window.
* **Tentative**: handle formatting, e.g. be a terminal emulator for the Megistos terminal sequences such as `ESC ! ...` for text formatting.
* Act as a local, command-line BBS *client*, using the TTYs already open by a user.

Whatever happens, the original mechanisms for things must remain in place.