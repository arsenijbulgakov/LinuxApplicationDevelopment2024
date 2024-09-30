GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* output_prog*
CFLAGS = -Wall -fPIC

all: README prog prog-a prog-so

.SECONDARY: liboutput_static.a(fun.o const.o)

%.o: %.c
	cc $< $(CFLAGS) -c -o $@

liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog: const.o fun.o prog.o
	cc $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $< -L. -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $< -L. -loutput -o $@

README:	prog
	./$< 2> $@

fun.o prog.o:	outlib.h

test: prog prog-a prog-so
	./prog > output_prog_1 2>&1
	./prog-a > output_prog-a_1 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > output_prog-so_1 2>&1

	./prog first > output_prog_2 2>&1
	./prog-a first > output_prog-a_2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so first > output_prog-so_2 2>&1

	./prog first second third > output_prog_3 2>&1
	./prog-a first second third > output_prog-a_3 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so first second third > output_prog-so_3 2>&1


	cmp output_prog_1 output_prog-a_1
	cmp output_prog_1 output_prog-so_1
	cmp output_prog-a_1 output_prog-so_1

	cmp output_prog_2 output_prog-a_2
	cmp output_prog_2 output_prog-so_2
	cmp output_prog-a_2 output_prog-so_2

	cmp output_prog_3 output_prog-a_3
	cmp output_prog_3 output_prog-so_3
	cmp output_prog-a_3 output_prog-so_3

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)