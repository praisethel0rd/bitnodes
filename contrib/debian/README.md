
Debian
====================
This directory contains files used to package bitnodesprod/bitnodespro-qt
for Debian-based Linux systems. If you compile bitnodesprod/bitnodespro-qt yourself, there are some useful files here.

## bitnodespro: URI support ##


bitnodespro-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitnodespro-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitnodespro-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitnodespro128.png` to `/usr/share/pixmaps`

bitnodespro-qt.protocol (KDE)

