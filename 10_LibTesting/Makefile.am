SUBDIRS = src tests

GENERATES = aclocal.m4 compile config.h.in config.status install-sh missing test-driver autom4te.cache config.guess config.h.in~ config.sub configure~ libtool Makefile.in  autoscan.log config.h config.log configure depcomp ltmain.sh stamp-h1 Makefile .deps .libs
GENERATES_SRC = src/Makefile src/Makefile.in src/libbuf.a src/libbuf.la src/libbuf.lo src/libbuf.o src/.deps src/.libs
GENERATES_TESTS = tests/Makefile tests/Makefile.in tests/test-suite.log tests/tests tests/tests.c tests/tests.log tests/tests.o tests/tests.trs tests/.deps tests/.libs

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov

.PHONY: clean

clean:
	rm -rf $(GENERATES)
	rm -rf $(GENERATES_SRC)
	rm -rf $(GENERATES_TESTS)
