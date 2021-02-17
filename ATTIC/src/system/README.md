# System Tools and Modules

Special programs that don't quiet fit the module model.

* **bbscleanup** implements a MajorBBS-like nightly clean-up. Unlike the MajorBBS, the BBS doesn't need to be down during it. Any module that needs regular activities will add a `cleanup` hook for itself and be called daily. This process replenishes people's time quota (credits), deletes expired messages, archives stuff, etc.
* **bbsdeluser** implements the user deletion hook. Modules storing user-specific data use this functionality to delete data when a user gets removed from the system.
* **bbsgetty** is a fork of the Unix `mgetty` meant for BBSing uses.
* **bbslogin** is an impelemntation of the Unix `login` utility implementing BBS-specific stuff like sign-ups.
* **bbslogout** logs out a user, printing end-of-session messages etc.
* **events** system-wide events like shutting down.
* **menuman** this is a special module, acting like the shell of a user's interaction. It implements the entire menu tree of the BBS (outside of modules). Each node in the tree is a ‘page’, and pages can be modules, static files printed out, external programs, or menus of other pages. Every page has a name, and this module adds a `/go NAME` command that can take you directly to that page without navigating manus.
* **metabbs** Experimental FidoNet-like networking for Megistos. Never got tested properly.
* **protocols** A framework for file transfer protocols. The generality of this allows pretty arbitraty things to be implemeted as file ‘transfer’ protocols, not just `[XYZ]-Modem`. E.g. listing the contents of compressed archives (ZIP, tar.gz, etc) is implemented as a protocol.
* **signup** The new user sign-up module.