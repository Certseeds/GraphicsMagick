.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

=======================
GraphicsMagick Download
=======================

.. _Bob Friesenhahn : mailto:bfriesen@graphicsmagick.org
.. _SourceForge Download : https://sourceforge.net/projects/graphicsmagick/files/
.. _tar : https://en.wikipedia.org/wiki/Tar_(computing)

.. contents::
  :local:

Download Sites
==============

The source distribution of GraphicsMagick as well as pre-compiled
binaries may be downloaded from the `SourceForge Download`_ page.
This is also where 'snapshot' distribution archives may be found.

Download Formats
================

The GraphicsMagick source files may be available in several different
archive formats:

tar.gz
------

This is a POSIX tar_ file compressed using the legacy GNU gzip format ('gz'
extension) by Jean-loup Gailly and Mark Adler. Gzip is available from
https://www.gzip.org/.  Gzip is the the most readily available
compressor on the planet.

tar.bz2
-------

This is a POSIX tar_ file compressed using the legacy bzip2 format ('bz2'
extension) by Julian Seward.  Bzip2 is available from http://sourceware.org/bzip2/.

tar.xz
------

This is a POSIX tar_ file compressed using XZ Utils ('xz' extension) by
Lasse Collin starting with Igor Pavlov's LZMA-SDK.  XZ Utils is
available from https://tukaani.org/xz/.  XZ Utils is very popular and
readily available.

tar.zst
-------

This is a POSIX tar_ file compressed using Facebook's Zstandard format
('zst' extension) by Yann Collet.  Zstd is available from
https://facebook.github.io/zstd/.  While Zstd is not yet popular for
source archive distribution, it is supported by Automake and GNU tar,
and its compression ratio is very good.

tar.lz
------

This is a POSIX tar_ file compressed using Lzip ('lz' extension).
Lzip is available from https://lzip.nongnu.org/lzip.html.  In our
experience, Lzip produces the smallest source archive files and uses a
compact and portable implementation (as compared with 'xz', which is
its primary competitor).

7z
---

This is a 7-Zip archive file ('7z' extension) by Igor Pavlov.  7-Zip
is available from https://www.7-zip.org/.  This format is used for the
Microsoft Windows sources since 7-Zip is much more widely available
under Windows than 'tar' is.

Verifying The Download
======================

Using a PGP key
---------------

GraphicsMagick is software which runs on a computer, and if its code
(source or binary code) was subtly modified (perhaps on the download
server, or modified after download), it could do almost anything!  Due
to this, it is useful to verify the download before you use it.  This
is especially important if you are preparing binaries for others to
use.

Distributed packages may be verified (both for integrity and origin)
using GnuPG (gpg).  GnuPG is normally provided as a package for your
operating system (often already installed), or may be downloaded from
https://gnupg.org/download/.  The installed program on your system
might be named 'gpg', 'gpg2', or 'gpg1'.

The signing key used (currently DSA key id
EBDFDB21B020EE8FD151A88DE301047DE1198975) may be downloaded in several
different ways.

The key may be downloaded directly from
http://www.simplesystems.org/users/bfriesen/public-key.txt, or it may
be extracted from the text of
http://www.graphicsmagick.org/security.html.

It may be also downloaded from a public key server (if you are lucky)
like::

  gpg --recv-keys EBDFDB21B020EE8FD151A88DE301047DE1198975

however, there are known dangers to your keystore if the keys on the
public key server have been spammed.

If extracting the key from the
http://www.graphicsmagick.org/security.html web page, then copy the
entire block of text including the all of the "BEGIN" and "END" lines
to a file (e.g. `gm-sigs.asc`).

If you have chosen to download the public key to a file
(e.g. `gm-sigs.asc`) you can import it into your collection of keys.
For example::

  gpg --import gm-sigs.asc

After importing the key, you can easily verify any GraphicsMagick
distribution file with an associated ".sig" (binary OpenPGP format
signature) or ".asc" (ASCII armored format signature) file.  The
distribution file and a signature file must be
downloaded. Verification is performed by doing this::

  gpg --verify GraphicsMagick-1.3.40.tar.xz.sig GraphicsMagick-1.3.40.tar.xz

and you should see output similar to::

  gpg: assuming signed data in 'GraphicsMagick-1.3.40.tar.xz'
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

  sha256sum GraphicsMagick-1.3.40.tar.xz

and this for a SHA-1 (legacy) checksum::

  sha1sum GraphicsMagick-1.3.40.tar.xz

and then compare the generated checksum (hex format) with the checksum
provided in the release announcement.  While this is much more secure
than doing nothing, it does not fully defend against forgery.  If
someone is able to forge a modified release archive as well as a
release announcement, then you could be duped!
