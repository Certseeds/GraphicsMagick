#!/usr/local/bin/perl
# Copyright (C) 2003 GraphicsMagick Group
# Copyright (C) 2002 ImageMagick Studio
# Copyright (C) 1991-1999 E. I. du Pont de Nemours and Company
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
#
# Test reading WMF files
#
# Whenever a new test is added/removed, be sure to update the
# 1..n ouput.
#
BEGIN { $| = 1; $test=1; print "1..4\n"; }
END {print "not ok $test\n" unless $loaded;}
use Graphics::Magick;
$loaded=1;

require 't/subroutines.pl';

chdir 't/wmf' || die 'Cd failed';

print("Rendering wizard.wmf ...\n");
testReadCompare('wizard.wmf', '../reference/wmf/wizard.gif',
                q//, 0.004, 0.9);
++$test;
print("Rendering clock.wmf ...\n");
testReadCompare('clock.wmf', '../reference/wmf/clock.gif',
                q//, 0.003, 0.9);
++$test;
print("Rendering ski.wmf ...\n");
testReadCompare('ski.wmf', '../reference/wmf/ski.gif',
                q//, 0.03, 1.0);
++$test;
print("Rendering fjftest.wmf ...\n");
testReadCompare('fjftest.wmf', '../reference/wmf/fjftest.gif',
                q//, 0.004, 0.5);
