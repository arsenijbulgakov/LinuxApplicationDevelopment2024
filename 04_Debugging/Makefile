GENERATES = out1 out2 range

all: range

range: range.c
	cc -O0 -g -Wall range.c -o range

test: range
	gdb -x gdb_script_1.gdb ./range --batch --quiet | grep '@@@' > out1
	gdb -x gdb_script_2.gdb ./range --batch --quiet | grep '@@@' > out2

	cmp out1 answers1
	cmp out2 answers2

clean:
	rm -rf $(GENERATES)