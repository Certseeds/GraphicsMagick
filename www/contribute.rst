.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

==============================
Contributing to GraphicsMagick
==============================

The future and success of GraphicsMagick depends on your contributions.
By contributing to GraphicsMagick you will benefit from the
features/fixes you contribute, can take pride in taking part in the
development of a quality product, and you can tell your friends that you
contribute to the GraphicsMagick project.

There are a number of ways you can contribute:

* Submit bug reports to the GraphicsMagick bug tracking system at
  SourceForge.

* Submit patches to the GraphicsMagick patch submission system at
  SourceForge.

* Perform test builds on unusual systems and report the results.

* Submit ideas and proposed designs to the graphicsmagick-core
  mailing list.

* Create a new language interface, dependent library, or application.

* Join the GraphicsMagick Group as a full-fledged developer with
  Mercurial commit access.

Regardless of how you choose to contribute, your contributions will be
treated with the respect and value that they deserve.

Becoming a member of the GraphicsMagick Group requires a majority vote
from existing members. Your chances of being admitted to the group are
increased significantly if you have a proven track-record of success
on other open source projects, are a recognized expert in the field,
or have already demonstrated your capabilities and commitment by
contributing to the project in other ways. Please contact Bob
Friesenhahn <bobjfriesenhahn@gmail.com> in order to be considered for
group membership.

Areas To Contribute
-------------------

The following are areas where significant contributions may be made to
the GraphicsMagick project:

* Create a language interface using SWIG <http://www.swig.org/> to
  support scripting in Perl, Python, TCL/TK, Guile, MzScheme, Ruby,
  Java, PHP, and CHICKEN, based on a common implementation.

* Create a new utility command parser based on a separate LALR or
  XML-based syntax definition, and using an approach suitable to
  replace the existing error-prone command parsers in magick/command.c

* Create a vector encoder for EPS, Postscript, PDF, SVG
  <http://www.w3.org/Graphics/SVG/>, WebCGM
  <http://www.w3.org/Graphics/WebCGM/>, or WMF.

* Create an OpenEXR coder based on the OpenEXR
  <http://www.openexr.com/> library from Industrial Light & Magic.

* Create a *pstoedit* module to import Postscript, EPS, and PDF
  files as vector data using pstoedit <http://www.pstoedit.net/> which
  already includes a high-quality driver to render Postscript vectors via
  GraphicsMagick. This module could also export vector data in many
  formats using pstoedit's output drivers.

* Add integrated Adobe XMP
  <http://www.adobe.com/products/xmp/index.html> profile support for
  TIFF, JPEG, PNG, PDF, EPS, and Postscript.

* Port Erik Reinhard's super-cool Parameter Estimation For
  Photographic Tone Reproduction
  <http://www.cs.ucf.edu/~reinhard/Reinhard02/> algorithm to
  GraphicsMagick.

* Create portable GUI which can work under Microsoft Windows, OS-X,
  X11, and Wayland (via a portable widget toolkit), to replace the
  outdated X11 GUI implmentation.

* Create an interface between GraphicsMagick and OpenOffice.org.
  <http://www.openoffice.org/> so that OpenOffice may load and save
  any format supported by GraphicsMagick. OpenOffice.org offers a
  separate SDK so there may be a number of other opportunities to
  explore.
