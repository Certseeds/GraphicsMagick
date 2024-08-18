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
# Test definitions.
#
# Contributed by Alex Kent Hajnal <graphicsmagick@alephnull.net>
#
BEGIN { $| = 1; $test=1, print "1..17\n"; }
END {print "not ok 1\n" unless $loaded;}
use Graphics::Magick;
$loaded=1;

push @INC, '.';  # Needed if running outside of make test
require 't/subroutines.pl';

chdir 't' || die 'Cd failed';

# Create temporary image
my $image = Graphics::Magick->new;

# (no definitions set)

print("Reading an unset definition ...\n");
testAccessDefinition( $image, 'png', 'test', undef );

++$test;
print("Adding png:test=TEST ...\n");
testAddDefinition( $image, 'png', 'test', 'TEST', 1 );

# png:test=TEST

++$test;
print("Checking that png:test=TEST ...\n");
testAccessDefinition( $image, 'png', 'test', 'TEST' );

++$test;
print("Changing png:test to Test ...\n");
testAddDefinition( $image, 'png', 'test', 'Test', 1 );

# png:test=Test

++$test;
print("Verifying the change ...\n");
testAccessDefinition( $image, 'png', 'test', 'Test' );

++$test;
print("Adding abc:DEF=ghi and 123:456=789 ...\n");
testAddDefinitions( $image, 'abc:DEF=ghi,123:456=789', 1 );

# png:test=Test  abc:DEF=ghi  123:456=789

++$test;
print("Verifying the changes ...\n");
testAccessDefinition( $image, 'png', 'test', 'Test' );
++$test;
testAccessDefinition( $image, '123', '456', '789' );
++$test;
testAccessDefinition( $image, 'abc', 'DEF', 'ghi' );

++$test;
print("Removing png:test and 123:456 ...\n");
testRemoveDefinitions( $image, 'png:test,123:456', 1 );

# abc:DEF=ghi

++$test;
print("Verifying the changes ...\n");
testAccessDefinition( $image, 'png', 'test', undef );
++$test;
testAccessDefinition( $image, '123', '456', undef );
++$test;
testAccessDefinition( $image, 'abc', 'DEF', 'ghi' );

++$test;
print("Removing all definitions ...\n");
testRemoveDefinitions( $image, '*', 1 );

# (no definitions set)

++$test;
print("Verifying the changes ...\n");
testAccessDefinition( $image, 'png', 'test', undef );
++$test;
testAccessDefinition( $image, '123', '456', undef );
++$test;
testAccessDefinition( $image, 'abc', 'DEF', undef );

1;
