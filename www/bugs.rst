.. -*- mode: rst -*-
.. This text is in reStucturedText format, so it may look a bit odd.
.. See http://docutils.sourceforge.net/rst.html for details.

===================
GraphicsMagick Bugs
===================

The following bugs are known to exist in GraphicsMagick. Please report
any additional bugs to the GraphicsMagick `bug tracker
<https://sourceforge.net/p/graphicsmagick/_list/tickets>`_ at SourceForge.

 * BMP reader is not working for some obscure low-color packed files.

 * DPX reader/writer does not properly handle subformats where row
   samples spill over the storage word boundary. This means that
   single-channel/grayscale 10-bit DPX files will only work for widths
   evenly divisible by three. (SF 1533184)

 * The PSD reader is disabled by default because it does not work well
   enough and several man-years worth of dedicated volunteer time is
   required to make it work properly.

 * Scitex reader is not working for some files.

 * SVG writer works only if you are particularly luckly and so it is
   not included in the build by default..

 * SVG reader mishandles basic units and many other syntax elements (SF
   1231547, 1298606).
