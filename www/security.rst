.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

=======================
GraphicsMagick Security
=======================

Background
----------

Although GraphicsMagick is image processing software, security is a
very important consideration for GraphicsMagick.  GraphicsMagick may
be used to open files produced by an untrusted party.  Given a
suitable weakness (which we make every effort to prevent), an
intentionally constructed file might be able to cause the software to
crash, leak memory, or in the worst case execute arbitrary code,
including shell code.  GraphicsMagick is very powerful and complex
software supporting many capabilities and so untrusted parties should
never be allowed to submit arbitrary requests into it.

The GraphicsMagick project is continually striving to eliminate
conditions in the software which might pose a risk for its users.

Reporting Issues
----------------

.. _`GraphicsMagick Security`: mailto:graphicsmagick-security@graphicsmagick.org

.. _`GraphicsMagick Bug Tracker`: https://sourceforge.net/p/graphicsmagick/bugs/

If you become aware of a serious security issue with GraphicsMagick,
then it may be addressed by email directly to the GraphicsMagick
maintainers or to the `GraphicsMagick Security`_ mail address.  More
minor issues are best addressed via the `GraphicsMagick Bug Tracker`_
at SourceForge.

Reporting an issue will allow us to fix it so that future releases of
the software won't suffer from the problem.


Safe Use Of The Software
------------------------

You are the first line of defense when it comes to GraphicsMagick
security!

If you are operating a server which supports file uploads from
untrusted users, or delivered via a network protocol such as http,
ftp, or email, then you should take steps to assure that a problem
with opening/processing the file does not place the whole server at
risk.  These are steps which can be taken:

.. _`graphicsmagick-announce` : https://lists.sourceforge.net/lists/listinfo/graphicsmagick-announce

1. Subscribe to the `graphicsmagick-announce`_ mailing list so that
   you are informed about new GraphicsMagick releases or special
   security bulletins.

2. Make sure that GraphicsMagick is up to date as reported on the
   GraphicsMagick web site.  Don't simply trust that packages from
   your operating system vendor are kept up to date or are updated to
   include security fixes.  Keeping GraphicsMagick up to date might
   require that you compile GraphicsMagick yourself from source code.

.. _`Container` : https://en.wikipedia.org/wiki/Operating-system-level_virtualization
.. _`FreeBSD Jail` : https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/jails.html
.. _`Solaris Zone` : https://illumos.org/man/5/zones
.. _`chrooted` : https://en.wikipedia.org/wiki/Chroot

3. Execute the software in a `Container`_, `FreeBSD Jail`_, `Solaris
   Zone`_, or `chrooted`_ environment such that it can not cause harm
   to the system running it.

4. Normalize input file names or any other external inputs so that
   they are under your control and not controlled by an untrusted
   party.

5. Enforce that uploaded files are passed to the expected reader.  For
   example, the uploaded file "file.jpg" is forced to be read by the
   JPEG reader (rather than a reader selected based on header magic
   testing) by using the file name "jpg:file.jpg".  If the file is not
   really what was indicated, then an error is reported.

   GraphicsMagick supports a great many file types and auto-detects
   many file types based on their content rather than file extension.
   The file which pretends to be an ordinary PNG or JPEG file might be
   something else entirely.  Note that even using independent file
   header testing may not be sufficient since it is possible to
   construct valid files with a header which appears to be several
   different types, but the first type which matches while testing the
   header will be selected.

6. Consider using the `MAGICK_CODER_STABILITY` environment variable to
   constrain the supported file formats to the subsets selected by
   `PRIMARY` or `STABLE`.  After setting this environment variable
   (e.g. `export MAGICK_CODER_STABILITY=PRIMARY`), use `gm
   convert -list format` and verify that the format support you need
   is enabled.


.. |copy|   unicode:: U+000A9 .. COPYRIGHT SIGN

Copyright |copy| GraphicsMagick Group 2002 - 2016
