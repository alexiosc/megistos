# Megistos Dæmons

In 1993, I was a Linux newbie and thought dæmons were the coolest thing ever. Simple programs that did one thing, did it well, and did so *in the background*. (I was an MS-DOS evacuee). Megistos espoused this, and so we have a bunch of dæmons here:

* **bbsd**: the BBS Daemon. The core of the BBS. This synchronises everything, is responsible for maintaining global statistics, charging credits, time-limiting users (I think), managing BBS channels (TTYs, telnet, SSH sessions, etc). If this one goes down, the entire BBS goes down.
* **emud**: a watchdog dæmon. Makes sure all dæmons are running properly. If any exit, `bbsinit` restarts it. This is also needed to restart `bbsd` when it exits (if no users are online and it's been running for a while, it exits to avoid memory leaks).
* **bbslockd**: serialises locking to avoid race conditions. (I was young and foolish and could have used semaphores but didn't because older Unix programs didn't)
* **emud**: a fork of the `ttysnoops` project by Carl Declerck. It allows a Sysop to ‘emulate’ (see what a user is seeing and type for the user, often to provide help) the user session. It's spawned immediately after connection and is the first thing that receives user input from a TTY.
* **msgd**: reindexes the message area databases in the background, and moves RFC 822 email to user's BBS inboxes.
* **rpc.metabbs**: MetaBBS was the Megistos equivalent of FidoNet, and this is its dæmon. MetaBBS was never properly tested. It runs on top of Sun's RPC like NFS and allows BBSes to exchange data. Mutually trusting BBSes, mind. There's very little authentication. The mid-90s were a simpler time.
* **statd**: this dæmon collects various system-wide statistics. It's a little bit like a modern `collectd`. Sysops can access the metrics it grabs and graph them by various simple criteria.