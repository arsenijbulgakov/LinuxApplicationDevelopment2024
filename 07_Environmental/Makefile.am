GENERATES = aclocal.m4 aclocal.m4 compile config.h.in config.log configure install-sh missing autom4te.cache config.h config.h.in~ config.status configure~ depcomp Makefile Makefile.in rhasher stamp-h1 src/rhasher.o test*

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

TESTS=test.sh

test.sh:
	echo 'echo "some text for test" > test_file' >> $@

	echo 'sha1sum test_file |  cut -d " " -f 1 > test_true_ans' >> $@
	echo 'echo "SHA1 test_file" | ./rhasher | sed -n '2p' > test_ans' >> $@
	echo 'cmp test_true_ans test_ans' >> $@

	echo 'md5sum test_file |  cut -d " " -f 1 > test_true_ans' >> $@
	echo 'echo "MD5 test_file" | ./rhasher | sed -n '2p' > test_ans' >> $@
	echo 'cmp test_true_ans test_ans' >> $@
    
	chmod +x $@

clean:
	rm -rf $(GENERATES)
