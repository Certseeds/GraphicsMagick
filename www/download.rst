.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

=======================
GraphicsMagick Download
=======================

.. _Bob Friesenhahn : mailto:bfriesen@graphicsmagick.org
.. _SourceForge Download : http://sourceforge.net/projects/graphicsmagick/files/

.. contents::
  :local:

Download Sites
==============

The source distribution of GraphicsMagick as well as pre-compiled
binaries may be downloaded from the `SourceForge Download`_ page.
This is also where 'snapshot' distribution archives may be found.

Until recently (December, 2021) GraphicsMagick provided its own ftp
site for downloads but this has been disabled due to abusive download
practices (by using it as the primary download site) and because
support for FTP has been removed from popular browsers.  This is
unfortunate since the same site also provided PNG-related files and a
libtiff mirror.  The ftp site directory tree continues to exist and
will be maintained.  If you are an administrator of a high-bandwidth
ftp or https mirror site and would like to provide a GraphicsMagick
mirror, please contact `Bob Friesenhahn`_ and we will work something
out.

Verifying The Download
======================

Using a PGP key
---------------

GraphicsMagick is software which runs on a computer, and if its code
(source or binary code) was subtly modified (perhaps on the download
server, or modified after download), it could do almost anything!  Due
to this, it is useful to verify the download before you use it.

Distributed packages may be verified (both for integrity and origin)
using GnuPG (gpg).  GnuPG is normally provided as a package for your
operating system (often already installed), or may be downloaded from
https://gnupg.org/download/.  The installed program on your system
might be named 'gpg', 'gpg2', or 'gpg1'.

The signing key used (currently DSA key id
EBDFDB21B020EE8FD151A88DE301047DE1198975) may be downloaded from a
public key server like::

  gpg --recv-keys EBDFDB21B020EE8FD151A88DE301047DE1198975

or it may be extracted from
http://www.graphicsmagick.org/security.html.

If extracting the key from the web page, (rather than using a key
server) to obtain the key, then copy the entire block of text
including the all of the "BEGIN" and "END" lines to a file
(e.g. `gm-sigs.asc`) and import it into your collection of keys.  For
example::

  gpg --import gm-sigs.asc

After importing the key, you can easily verify any GraphicsMagick
distribution file with an associated ".sig" file (requires downloading
two files) by doing this::

  gpg --verify GraphicsMagick-1.3.37.tar.xz.sig

and you should see output similar to::

  gpg: assuming signed data in 'GraphicsMagick-1.3.37.tar.xz'
  gpg: Signature made Sun Dec 12 15:30:02 2021 CST
  gpg:                using DSA key EBDFDB21B020EE8FD151A88DE301047DE1198975
  gpg: Good signature from "Bob Friesenhahn <bfriesen@simple.dallas.tx.us>" [ultimate]
  gpg:                 aka "Bob Friesenhahn <bfriesen@simplesystems.org>" [ultimate]
  gpg:                 aka "Bob Friesenhahn <bfriesen@graphicsmagick.org>" [ultimate]
  gpg:                 aka "Bob Friesenhahn <bobjfriesenhahn@gmail.com>" [ultimate]
  gpg:                 aka "[jpeg image of size 4917]" [ultimate]

Using a SHA-256 or SHA-1 checksum
---------------------------------

While verifying distribution files using GnuPG is by far the most
secure way to validate a release file, you may find SHA-256 or SHA-1
checksums in a distribution release announcement (e.g. from the
graphicsmagick-announce list at
https://sourceforge.net/p/graphicsmagick/mailman/graphicsmagick-announce/
which you *should* subscribe to).  In this case you may do this for a
SHA-256 checksum::

  sha256sum GraphicsMagick-1.3.37.tar.xz

and this for a SHA-1 checksum::

  sha1sum GraphicsMagick-1.3.37.tar.xz

and then compare the generated checksum (hex format) with the checksum
provided in the release announcement.  While this is much more secure
than doing nothing, it does not fully defend against forgery.  If
someone is able to forge a modified release archive as well as a
release announcment, then you could be duped!
