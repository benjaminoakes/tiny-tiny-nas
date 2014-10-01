tiny-tiny-nas
=============

Sideloaded NAS features for MIPS-based embedded Linux (tested with Actiontec C1000A router).

This project started because I found out my Actiontec C1000A router had an unused, "unsupported" USB3 port.  Turns out it's running Linux, grants root access, and can mount attached USB storage just fine -- if coaxed.

It's a really tiny box!  It's an embedded system without a ton of resources to spare, but it takes almost no power, would be left running all day anyway, and can do some useful tasks.

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
    * Uses configured feed on external server
  * HTTP downloader
    * Submit a URL and close your laptop; come back later and the file will be downloaded.
    * Redis-based
  * Offsite backup
    * Rsync backups offsite over SSH
