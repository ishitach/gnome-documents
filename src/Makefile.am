AM_CPPFLAGS = \
    -I$(top_builddir)/config \
    -I$(top_srcdir)	\
    -L$(top_srcdir)/src \
    -DGNOME_DOCUMENTS_LIBDIR=\"$(libdir)\" \
    -DGNOME_DOCUMENTS_DATADIR=\"$(datadir)\" \
    -DGNOME_DOCUMENTS_PKGDATADIR=\"$(pkgdatadir)\" \
    -DGNOME_DOCUMENTS_TOP_SRCDIR=\"$(abs_top_srcdir)\" \
    -DGNOME_DOCUMENTS_BUILDDIR=\"$(abs_top_builddir)\"

girdir = $(pkgdatadir)/gir-1.0
typelibdir = $(pkglibdir)/girepository-1.0

BUILT_SOURCES =
EXTRA_DIST =
CLEANFILES =
pkglib_LTLIBRARIES =
INTROSPECTION_GIRS =
gir_DATA =
typelib_DATA =
bin_SCRIPTS =
libexec_PROGRAMS =
libexec_SCRIPTS =

# convenience command for doing Makefile variable substitutions in non-Makefile
# files (scripts, service files, etc.)
do_subst = sed -e 's|@abs_top_srcdir[@]|$(abs_top_srcdir)|g' \
               -e 's|@abs_top_builddir[@]|$(abs_top_builddir)|g' \
               -e 's|@localedir[@]|$(localedir)|g' \
               -e 's|@bindir[@]|$(bindir)|g' \
               -e 's|@libdir[@]|$(libdir)|g' \
               -e 's|@libexecdir[@]|$(libexecdir)|g' \
               -e 's|@pkglibdir[@]|$(pkglibdir)|g' \
               -e 's|@pkgdatadir[@]|$(pkgdatadir)|g' \
               -e 's|@GJS_CONSOLE[@]|$(GJS_CONSOLE)|g' \
               -e 's|@PACKAGE_NAME[@]|$(PACKAGE_NAME)|g' \
               -e 's|@PACKAGE_VERSION[@]|$(PACKAGE_VERSION)|g' \
               -e 's|@GETTEXT_PACKAGE[@]|$(GETTEXT_PACKAGE)|g'

include $(INTROSPECTION_MAKEFILE)
include Makefile-lib.am
include Makefile-js.am

resource_files = $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/gnome-documents.gresource.xml)
gnome-documents.gresource: gnome-documents.gresource.xml $(resource_files)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(srcdir) $<
EXTRA_DIST += gnome-documents.gresource.xml $(resource_files)

resourcedir = $(pkgdatadir)
resource_DATA = gnome-documents.gresource

CLEANFILES += gnome-documents.gresource

gir_DATA += $(INTROSPECTION_GIRS)
typelib_DATA += $(gir_DATA:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)

service_in_files = org.gnome.Documents.service.in org.gnome.Books.service.in
servicedir = $(datadir)/dbus-1/services
service_DATA = org.gnome.Documents.service org.gnome.Books.service

org.gnome.Documents.service: org.gnome.Documents.service.in
	$(AM_V_GEN) $(do_subst) $< > $@

org.gnome.Books.service: org.gnome.Books.service.in
	$(AM_V_GEN) $(do_subst) $< > $@

CLEANFILES += $(service_DATA)
EXTRA_DIST += $(service_in_files)

bin_SCRIPTS += gnome-documents
gnome-documents: gnome-documents.in
	$(AM_V_GEN) $(do_subst) $< > $@
	chmod +x $@

CLEANFILES += gnome-documents
EXTRA_DIST += gnome-documents.in

bin_SCRIPTS += gnome-books
gnome-books: gnome-books.in
	$(AM_V_GEN) $(do_subst) $< > $@
	chmod +x $@

CLEANFILES += gnome-books
EXTRA_DIST += gnome-books.in

-include $(top_srcdir)/git.mk
