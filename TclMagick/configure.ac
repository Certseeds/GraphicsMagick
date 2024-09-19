#!/bin/bash -norc
dnl This file is an input file used by the GNU "autoconf" program to
dnl generate the file "configure", which is run during Tcl installation
dnl to configure the system for the local environment.
#
AC_INIT([TclMagick],[0.46])

# Specify directory where m4 macros may be found.
AC_CONFIG_MACRO_DIR([unix/m4])

# Directory where autotools helper scripts lives.
AC_CONFIG_AUX_DIR([unix/config])

# Generate configure header.
AC_CONFIG_HEADERS([generic/config.h])

# Initalize Automake
AM_INIT_AUTOMAKE

# Add configure option --enable-maintainer-mode which enables dependency
# checking and generation useful to package maintainers.  This is made an
# option to avoid confusing end users.
AM_MAINTAINER_MODE

# Enable support for silent build rules
AM_SILENT_RULES

# Configure for the compiler
AC_PROG_CC

# Initialize libtool
LT_INIT
AC_SEARCH_LIBS([strerror],[cposix])

dnl Allow the user to specify the GraphicsMagick config script to use.
dnl Note that TclMagick no longer works with ImageMagick
dnl since it changed its enum lists (and many other things).
AC_ARG_WITH([magick],
            AS_HELP_STRING([--with-magick],
                           [location of GraphicsMagick-config script]),
            [with_magick=${withval}])

dnl First check to see if --with-magick-config was specified.
GM_CPPFLAGS=''
GM_LDFLAGS=''
GM_LIBS=''
wand_config=''
if test x"${with_magick}" != x
then
  if test -x "${with_magick}"
  then
    wand_config=${with_magick}
  else
    AC_MSG_ERROR([${with_magick} is not an executable file])
  fi
fi
if test x"${wand_config}" = x
then
  AC_PATH_PROGS(wand_config,[GraphicsMagickWand-config],,)
fi
if test x"${wand_config}" = x
then
  AC_MSG_ERROR([Please specify the GraphicsMagickWand-config script with --with-magick!])
fi

dnl It actually calls another script, so the PATH needs to be set.
PATH=$PATH:`dirname ${wand_config}`
export PATH
AC_MSG_CHECKING([for GraphicsMagick Wand configuration script])
AC_MSG_RESULT(${wand_config})
GM_CPPFLAGS=`${wand_config} --cppflags`
AC_SUBST(GM_CPPFLAGS)
GM_LDFLAGS=`${wand_config} --ldflags`
AC_SUBST(GM_LDFLAGS)
GM_LIBS=`${wand_config} --libs`
AC_SUBST(GM_LIBS)

CPPFLAGS_SAVE=$CPPFLAGS
LDFLAGS_SAVE=$LDFLAGS
LIBS_SAVE=$LIBS
CPPFLAGS="$CPPFLAGS $GM_CPPFLAGS"
LDFLAGS="$LDFLAGS $GM_LDFLAGS"
LIBS="$GM_LIBS $LIBS"
AC_CHECK_FUNCS([MagickSetImageFormat])
CPPFLAGS=$CPPFLAGS_SAVE
LDFLAGS=$LDFLAGS_SAVE
LIBS=$LIBS_SAVE

TEA_INIT([3.10])

TEA_PATH_TCLCONFIG
TEA_LOAD_TCLCONFIG

TEA_PATH_TKCONFIG
TEA_LOAD_TKCONFIG

TEA_PREFIX

TEA_SETUP_COMPILER

TEA_ADD_HEADERS([])
TEA_ADD_INCLUDES([])
TEA_ADD_LIBS([])
TEA_ADD_CFLAGS([])
TEA_ADD_STUB_SOURCES([])
TEA_ADD_TCL_SOURCES([])

TEA_PUBLIC_TCL_HEADERS
TEA_PUBLIC_TK_HEADERS

TEA_ENABLE_THREADS

TEA_ENABLE_SHARED

TEA_CONFIG_CFLAGS

AC_DEFINE(USE_TCL_STUBS)
AC_DEFINE(USE_TK_STUBS)

TEA_MAKE_LIB

TEA_PROG_TCLSH
TEA_PROG_WISH

AC_CONFIG_FILES(\
Makefile \
generic/Makefile \
generic/pkgIndex.tcl)

AC_OUTPUT
