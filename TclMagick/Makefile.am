AUTOMAKE_OPTIONS = 1.11 dist-zip dist-bzip2 foreign
ACLOCAL_AMFLAGS = -I unix/m4
AM_DISTCHECK_CONFIGURE_FLAGS = --with-tcl=${TCL_BIN_DIR} --with-tk=${TK_BIN_DIR} --with-magick=${wand_config} --exec-prefix=${prefix}

EXTRA_DIST=LICENSE tests images doc pkgIndex.tcl
SUBDIRS = generic

TCLSH_ENV	= TCL_LIBRARY=`@CYGPATH@ $(TCL_SRC_DIR)/library`
PKG_ENV		= @LD_LIBRARY_PATH_VAR@="$(EXTRA_PATH):$(@LD_LIBRARY_PATH_VAR@)" \
		  PATH="$(EXTRA_PATH):$(PATH)" \
		  TCLLIBPATH="$(TCLLIBPATH)"

TCLSH		= $(TCLSH_ENV) $(PKG_ENV) $(TCLSH_PROG)


install-data-local:
	$(mkinstalldirs) $(DESTDIR)@libdir@/TclMagick@VERSION@
	$(INSTALL_DATA) $(top_srcdir)/pkgIndex.tcl $(DESTDIR)@libdir@/TclMagick@VERSION@

uninstall-local:
	rm -v $(DESTDIR)@libdir@/TclMagick@VERSION@/pkgIndex.tcl

test:
	cd generic && $(TCLSH) `@CYGPATH@ $(srcdir)/tests/test-wand.tcl` $(TESTFLAGS) \
		-load "package ifneeded $(PACKAGE_NAME)3 $(PACKAGE_VERSION) \
			[list load `@CYGPATH@ $(PKG_LIB_FILE)` [string totitle $(PACKAGE_NAME)3]]"
