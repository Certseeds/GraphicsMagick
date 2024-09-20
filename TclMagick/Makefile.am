# Makefile for creating libTclMagick and libTkMagick

# Copyright David N. Welton <davidw@dedasys.com>, 2004, with many
# thanks to Bob Friesenhahn for all the help.

AUTOMAKE_OPTIONS = 1.12 subdir-objects dist-zip dist-xz no-dist-gzip foreign
ACLOCAL_AMFLAGS = -I unix/m4
AM_DISTCHECK_CONFIGURE_FLAGS = --with-tcl=${TCL_BIN_DIR} --with-tk=${TK_BIN_DIR} --with-magick=${wand_config} --exec-prefix="$$dc_install_base"

EXTRA_DIST=LICENSE tests images doc pkgIndex.tcl

TCLSH_ENV	= TCL_LIBRARY=`@CYGPATH@ $(TCL_SRC_DIR)/library`
PKG_ENV		= @LD_LIBRARY_PATH_VAR@="$(EXTRA_PATH):$(@LD_LIBRARY_PATH_VAR@)" \
		  PATH="$(EXTRA_PATH):$(PATH)" \
		  TCLLIBPATH="$(TCLLIBPATH)"

TCLSH		= $(TCLSH_ENV) $(PKG_ENV) $(TCLSH_PROG)

# Put this in its own package directory.
generic_lib_magickdir = @libdir@/TclMagick@VERSION@
generic_lib_magick_LTLIBRARIES =  generic/libttkcommon.la generic/TclMagick.la generic/TkMagick.la

generic_libttkcommon_la_SOURCES = generic/libttkcommon.c generic/libttkcommon.h
generic_libttkcommon_la_LDFLAGS = @GM_LDFLAGS@ -no-undefined
generic_libttkcommon_la_LIBADD = @TCL_STUB_LIB_SPEC@ @TCL_LIBS@ @TCL_LIBS@ @GM_LIBS@
generic_libttkcommon_la_CPPFLAGS = -Igeneric/ @TCL_INCLUDES@ @GM_CPPFLAGS@

generic_TclMagick_la_SOURCES = generic/TclMagick.c generic/TclMagick.h generic/libttkcommon.h
generic_TclMagick_la_LDFLAGS = @GM_LDFLAGS@ -L$(generic_lib_magickdir) -no-undefined -module
generic_TclMagick_la_LIBADD = @TCL_STUB_LIB_SPEC@ @TCL_LIBS@ @TCL_LIBS@ @GM_LIBS@ generic/libttkcommon.la
generic_TclMagick_la_CPPFLAGS = -Igeneric/ @TCL_INCLUDES@ @GM_CPPFLAGS@

generic_TkMagick_la_SOURCES = generic/TkMagick.c generic/TclMagick.h generic/libttkcommon.h
generic_TkMagick_la_LDFLAGS = @GM_LDFLAGS@ -L$(generic_lib_magickdir) -no-undefined -module
generic_TkMagick_la_LIBADD = @TCL_STUB_LIB_SPEC@ @TK_STUB_LIB_SPEC@ @TCL_LIBS@ @TK_LIBS@ @GM_LIBS@ generic/libttkcommon.la
generic_TkMagick_la_CPPFLAGS = -Igeneric/ @TCL_INCLUDES@ @GM_CPPFLAGS@ @TK_INCLUDES@ @TK_XINCLUDES@

CLEANFILES = generic/pkgIndex.tcl


install-data-local:
	$(mkinstalldirs) $(DESTDIR)@libdir@/TclMagick@VERSION@
	$(INSTALL_DATA) $(top_srcdir)/pkgIndex.tcl $(DESTDIR)@libdir@/TclMagick@VERSION@

uninstall-local:
	rm -v $(DESTDIR)@libdir@/TclMagick@VERSION@/pkgIndex.tcl

test:
	cd generic && $(TCLSH) `@CYGPATH@ $(srcdir)/tests/test-wand.tcl` $(TESTFLAGS) \
		-load "package ifneeded $(PACKAGE_NAME)3 $(PACKAGE_VERSION) \
			[list load `@CYGPATH@ $(PKG_LIB_FILE)` [string totitle $(PACKAGE_NAME)3]]"

# Run Clang analyzer on the project.
# In order for this to work, you must have first installed the 'clang'
# and 'clang-tools' packages on your system.
# The project should have been configured to use clang.
#	-enable-checker security.insecureAPI.DeprecatedOrUnsafeBufferHandling
scan-build:
	scan-build-15 -k --html-title='TclMagick@VERSION@' \
	-maxloop 10000 \
	-disable-checker deadcode.DeadStores \
	-enable-checker security.insecureAPI.bcmp \
	-enable-checker security.insecureAPI.bcopy \
	-enable-checker security.insecureAPI.bzero \
	-enable-checker security.insecureAPI.strcpy \
	-enable-checker valist.CopyToSelf \
	-enable-checker valist.Uninitialized \
	-enable-checker valist.Unterminated \
	--use-cc $(CC) $(MAKE)
