tiny-tiny-nas
=============

Sideloaded NAS features for MIPS-based embedded Linux (tested with Actiontec C1000A router).

**Update (March 2019):** A firmware update makes `sh` now require a login with an unknown password.  I'm archiving this repository as a result, but the content will remain here for historical purposes.

This project started because I found out my Actiontec C1000A router had an unused, "unsupported" USB3 port.  Turns out it's running Linux, grants root access, and can mount attached USB storage just fine -- if coaxed.

It's a really tiny box!  It's an embedded system without a ton of resources to spare, but it takes almost no power, would be left running all day anyway, and can do some useful tasks.

Features
--------

Services:

  * Cron
  * File server (FTP)
  * Rsync server
  * Web server (HTTP)

Other services:

  * Simple file browser
    * Lists files accessible over HTTP
  * Podcast downloader (HTTP only)
    * Uses configured feed on an external server
    * Removes old files based on configuration
    * See [Doccaster](https://github.com/benjaminoakes/doccaster)
  * Background downloader
    * Submit a URL and close your laptop; come back later and the file will be downloaded.
    * See [Doccaster](https://github.com/benjaminoakes/doccaster)
  * Offsite backup
    * Rsync backups to an offsite server over SSH

Installation
------------

This is intentionally *NOT* a firmware replacement.  If something goes wrong, restart the router, unplug your USB disk, and everything will be back to normal.  However, you'll have to manually start the services you want if the router ever turns off.

This has only been tested on the Actiontec C1000A.  It shouldn't be hard to port to other devices, though.

Installation steps:

  * Format a USB Mass Storage volume (a flash drive or hard drive) as ext3
  * Download this project onto the volume via your computer: `git clone git@github.com:benjaminoakes/tiny-tiny-nas.git`
    * Configuration goes into `etc`
    * Your files go into `serv`
  * Plug the USB volume into your router
  * Find the admin password for your router
  * `telnet 192.168.0.1` using username `admin` and your password
  * You'll be at a `>` prompt.  Type `sh` then enter.
  
**Update (March 2019):** A firmware update makes `sh` now require a login with an unknown password.  I'm archiving this repository as a result, but the content will remain here for historical purposes.
  
  * You'll be at a `#` prompt.  Now it's time to mount your USB disk, do some first time setup, and start the services:

First time setup:

    mkdir -p /var/mnt/usbms
    mount /dev/sda1 /var/mnt/usbms
    cd /var/mnt/usbms
    # # First time only:
    # usr/local/bin/install-precompiled-binaries
    sh start_sh
    sh sbin/init

At this point, you'll have `crond`, `httpd`, `ftpd`, and `rsync` running.  However, there are no cronjobs enabled by default.  Edit `etc/crontabs/admin` to enable.

Things to try:

  * Open [http://192.168.0.1/](http://192.168.0.1/) in your web browser.  You should see the files from the USB drive attached to the router.
  * Connect to ftp://192.168.0.1 in a FTP client.  You can upload and download files from a desktop or mobile device.
  * Set up rsync shares and use them to back up computers.  (I have Duplicity back up to a local folder which then gets rsynced to the NAS.)
  * Set up SSH keys and a remote server and push backups offsite every night.
  * Set up Doccaster and hook in Podcast feeds and personal ad-hoc downloads for the NAS to download in the background.

Notes
-----

I'm not sure why, but the Actiontec firmware changes the name of the root user to `admin`.

Thanks
------

  * Aboriginal Linux
  * BusyBox
  * Dropbear
  * Rsync
  * Redis
