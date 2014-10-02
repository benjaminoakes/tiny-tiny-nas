tiny-tiny-nas
=============

Sideloaded NAS features for MIPS-based embedded Linux (tested with Actiontec C1000A router).

This project started because I found out my Actiontec C1000A router had an unused, "unsupported" USB3 port.  Turns out it's running Linux, grants root access, and can mount attached USB storage just fine -- if coaxed.

It's a really tiny box!  It's an embedded system without a ton of resources to spare, but it takes almost no power, would be left running all day anyway, and can do some useful tasks.

(NOTE: work in progress -- I'm using a version of this, but a lot of the current code is hardcoded for my use!)

Features
--------

Servers:

  * File server (FTP)
  * Rsync server
  * Web server (HTTP)

Other services:

  * Simple file browser
    * Lists
  * Podcast downloader (HTTP only)
    * Uses configured feed on an external server
  * HTTP downloader
    * Submit a URL and close your laptop; come back later and the file will be downloaded.
    * Redis-based
  * Offsite backup
    * Rsync backups offsite over SSH

Installation
------------

This is intentionally *NOT* a firmware replacement.  Unplug your USB disk and everything will be back to normal.  However, you'll have to manually start the services you want.

Volume must be formatted as ext3 (not ext2 or ext4).  FAT also works, but symlinks aren't supported, so it's not a good solution.

TODO

Notes
-----

I'm not sure why, but the Actiontec firmware changes the name of the root user to "admin".

Thanks
------

  * Aboriginal Linux
  * BusyBox
  * Dropbear
  * Rsync
  * Redis
