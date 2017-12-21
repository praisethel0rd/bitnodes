
Debian
====================
This directory contains files used to package bitnodesd/bitnodes-qt
for Debian-based Linux systems. If you compile bitnodesd/bitnodes-qt yourself, there are some useful files here.

## bitnodes: URI support ##


bitnodes-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitnodes-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitnodes-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitnodes128.png` to `/usr/share/pixmaps`

bitnodes-qt.protocol (KDE)

