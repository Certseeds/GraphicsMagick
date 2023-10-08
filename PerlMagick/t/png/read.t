#!/usr/local/bin/perl
# Copyright (C) 2003-2023 GraphicsMagick Group
# Copyright (C) 2002 ImageMagick Studio
# Copyright (C) 1991-1999 E. I. du Pont de Nemours and Company
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
#
# Test reading PNG images
#
# Contributed by Bob Friesenhahn <bfriesen@simple.dallas.tx.us>
#

BEGIN { $| = 1; $test=1; print "1..7\n"; }
END {print "not ok $test\n" unless $loaded;}
use Graphics::Magick;
$loaded=1;

require 't/subroutines.pl';

chdir 't/png' || die 'Cd failed';

#
# 1) Test Black-and-white, bit_depth=1 PNG
#
print( "1-bit grayscale PNG ...\n" );
testRead( 'input_bw.png', q//,
  '552ee0b3b9159ceedc4ce30125e9db38d2045d53b941844a72ac5f5f38335454' );

#
# 2) Test Monochrome PNG
#
++$test;
print( "8-bit grayscale PNG ...\n" );
testRead( 'input_mono.png', q//,
  '19da3123692c66d023074dd1e272119ab2357b9a34855a393ad18c88af01ae86' );

#
# 3) Test 16-bit Portable Network Graphics
#
++$test;
print( "16-bit grayscale PNG ...\n" );
testRead( 'input_16.png', q//,
  'a6c3f3ce8772cd6aa973ae1f3ebd94ee65292112d3f1e8e86171bf4d931bd181',
  'c87cc12715f3e0619d6fe871bd8132f88facffb3d38dd8869cb262ec6b9c4cef' );
#
# 4) Test 256 color pseudocolor PNG
#
++$test;
print( "8-bit indexed-color PNG ...\n" );
testRead( 'input_256.png', q//,
  'd1340caccc7351834f1ca9693489ee780ac326a0d6bb660cd550c5c28711b2fe' );

#
# 5) Test TrueColor PNG
#
++$test;
print( "24-bit Truecolor PNG ...\n" );
testRead( 'input_truecolor.png', q//,
  'b84c31bbe78d84d0432c7414b25c58599484aa2c7174af8332509966d07f265b' );

#
# 6) Test Multiple-image Network Graphics
#
++$test;
print( "MNG with 24-bit Truecolor PNGs...\n" );
testRead( 'input.mng', q//,
  'eb089161ebc5ab3964cdec1b72628c4d1c29ebd78f333a3d4a0d47c614fb3897' );

#
# 7) Test PNG in BMP format

# FIXME: Somehow we get an extra preceding blank frame from the
# PNG-compressed BMP reader/sample although there is no other evidence
# of multiple frames from the BMP reader!
++$test;
print( "PNG in BMP format ...\n" );
testRead( 'input_PNG.bmp[1]', q//,
  '88956c2242aab1c8f23d4074ed4f313316413cf79ccf1fea8f650f30bd8e2e42' );
