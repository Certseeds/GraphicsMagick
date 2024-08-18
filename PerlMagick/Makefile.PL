# Copyright (C) 2003-2018 GraphicsMagick Group
# Copyright (C) 2002 ImageMagick Studio
# Copyright (C) 1998,1999 E. I. du Pont de Nemours and Company
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
# NOTE: set TEST_VERBOSE=1 in order to see verbose output from tests.
#
#   In order to run just one test verbosely do something like
#     make TEST_VERBOSE=1 TEST_FILES=t/filter.t test

use ExtUtils::MakeMaker;
use Config;

my $magick_CPPFLAGS='-D_LIB -D_MT';
my $magick_DEFS=' -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES=1 -DHAVE_CONFIG_H';
my $magick_CFLAGS='-fopenmp -g -O2 -Wall';
my $magick_CC='gcc';
my $magick_CPPFLAGS='-I../ -I.. -D_LIB -D_MT';
my $magick_LDFLAGS='';
my $magick_BIN_DIR="$ENV{'DESTDIR'}/mingw64/bin";
my $magick_API_LIBS='-lGraphicsMagick -lgdi32 -luser32 -lzstd -lz -lm -lpthread -lgomp';
my $magick_PERLMAINCC='';
my $magick_LIB_DIR="$ENV{'DESTDIR'}/mingw64/lib";

# Compute test specification
my $delegate_tests='t/*.t';
my $delegate;
foreach $delegate (qw/zlib/) {
  if( -d "t/$delegate" ) {
    $delegate_tests .= " t/$delegate/*.t";
  }
}

# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile
  (
   # Module description
   'ABSTRACT'   => 'GraphicsMagick PERL Extension',

   # Perl module name is Graphics::Magick
   'NAME'       => 'Graphics::Magick',

   # Module author
   'AUTHOR'     => 'GraphicsMagick Group',

   # Module version
   'VERSION'    => '1.4' =~ /^([\d\.]+)/g,

   # Preprocessor defines
   'DEFINE'     => $magick_DEFS,     # e.g., '-DHAVE_SOMETHING'

   # Header search specification and preprocessor flags
   'INC'        => $magick_CPPFLAGS,

   # C compiler
   'CC'         => $magick_CC,

   # C pre-processor flags (e.g. -I & -D options)
   # 'CPPFLAGS'    => "$Config{'cppflags'} $magick_CPPFLAGS",

   # C compiler flags (e.g. -O -g)
   'CCFLAGS'    => "$Config{'ccflags'} $magick_CFLAGS",

   # Linker
   'LD'         => $Config{'ld'} == $Config{'cc'} ? $magick_CC : $Config{'ld'},

   # Linker flags for building an executable
   'LDFLAGS'    =>  "-L$magick_LIB_DIR $Config{'ldflags'}",

   # Linker flags for building a dynamically loadable module
   'LDDLFLAGS'  => "-L$magick_LIB_DIR $Config{'lddlflags'}",

   # Install PerlMagick binary into GraphicsMagick bin directory
   'INSTALLBIN' => $magick_BIN_DIR,

   # Library specification
   'LIBS'       => ["-L$magick_LIB_DIR $magick_LDFLAGS $magick_API_LIBS"],

   # Perl binary name (if a Perl binary is built)
   'MAP_TARGET' => 'PerlMagick',

   # Let CFLAGS drive optimization flags by setting OPTIMIZE to empty
   # 'OPTIMIZE' => '',

   # Use same compiler as GraphicsMagick
   'PERLMAINCC' => $magick_PERLMAINCC,

   # Set Perl installation prefix to GraphicsMagick installation prefix
#   'PREFIX'    => '/mingw64',

   # Include delegate directories in tests
   test         => { TESTS      =>      $delegate_tests},

   ($Config{'archname'} =~ /-object$/i ? ('CAPI' => 'TRUE') : ()),
);


#
# Substitutions for "makeaperl" section.
#
sub MY::makeaperl {
     package MY; # so that "SUPER" works right
     my $inherited = shift->SUPER::makeaperl(@_);

     # Stinky ExtUtils::MM_Unix likes to append its own library path to $(CC),
     # prior to any user-specified library path so that an installed library is
     # used rather than the library just built.  This substitution function
     # tries to insert our library path first. Also, use the same compiler used
     # to build perlmain.c to link so that a C++ compiler may be used if
     # necessary.
     $inherited =~ s:MAP_LINKCMD\s.*\s*\$\(CC\):MAP_LINKCMD   = \$(PERLMAINCC) -L/mingw64/lib: ;
     $inherited;
 }

#
# Substitutions for "test" section.
#
#sub MY::test {
#     package MY; # so that "SUPER" works right
#     my $inherited = shift->SUPER::test(@_);
#
     # Run tests in our environment
#     $inherited =~ s:PERL_DL_NONLAZY=1:/bin/sh ../rungm.sh PERL_DL_NONLAZY=1:g ;
#     $inherited;
# }
