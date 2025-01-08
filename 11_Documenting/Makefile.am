SUBDIRS = src po

@DX_RULES@

all-local:	doxygen-doc

doxygen-doc/man/man1/guess_number.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess_number.1

http:	doxygen-doc
	python3 -m http.server --directory $</html 8000

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

GENERATES = ABOUT-NLS autom4te.cache config.guess config.h.in config.log config.status configure install-sh Makefile Makefile.in stamp-h1 aclocal.m4 compile config.h config.h.in~ config.rpath config.sub configure~ depcomp m4 missing Doxyfile doxygen-doc
GENERATES_SRC = src/.deps src/guess_number src/guess_number.o src/Makefile src/Makefile.in
GENERATES_PO = po/boldquot.sed po/en@quot.header po/Makefile po/Makefile.in.in po/Makevars.template po/POTFILES po/remove-potcdate.sin po/Rules-quot po/stamp-it po/en@boldquot.header po/insert-header.sin po/Makefile.in po/Makefile.in.in~ po/quot.sed po/ru.gmo

clean:
	rm -rf $(GENERATES)
	rm -rf $(GENERATES_SRC)
	rm -rf $(GENERATES_PO)
