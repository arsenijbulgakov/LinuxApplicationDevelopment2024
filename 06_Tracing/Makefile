all: move remove.so

move: move.c
	cc -g -Wall move.c -o move

remove.so: remove.c
	cc -shared -o remove.so remove.c


test_remove: remove.so move
	echo "some text for test" > PROTECT_test_infile
	LD_PRELOAD=`pwd`/remove.so ./move PROTECT_test_infile test_outfile
	cmp PROTECT_test_infile test_outfile


test_strace: move
	echo "some text for test" > test_infile
	./move test_infile test_outfile

	echo "some text for test" > test_infile
	echo "+++ exited with 2 +++" > test_err_true
	strace -e openat -P test_infile -e fault=openat ./move test_infile test_outfile 2>&1 | grep 'exited with' > test_err
	cmp test_err_true test_err

	echo "some text for test" > test_infile
	echo "+++ exited with 3 +++" > test_err_true
	strace -e close -P test_infile -e fault=close ./move test_infile test_outfile 2>&1 | grep 'exited with' > test_err
	cmp test_err_true test_err

	echo "some text for test" > test_infile
	echo "+++ exited with 4 +++" > test_err_true
	strace -e read -P test_infile -e fault=read ./move test_infile test_outfile 2>&1 | grep 'exited with' > test_err
	cmp test_err_true test_err

	echo "some text for test" > test_infile
	echo "+++ exited with 5 +++" > test_err_true
	strace -e write -P test_outfile -e fault=write ./move test_infile test_outfile 2>&1 | grep 'exited with' > test_err
	cmp test_err_true test_err

	echo "some text for test" > test_infile
	echo "+++ exited with 6 +++" > test_err_true
	strace -e unlinkat -P test_infile -e fault=unlinkat ./move test_infile test_outfile 2>&1 | grep 'exited with' > test_err
	cmp test_err_true test_err


clean:
	rm -rf move remove.so test_* PROTECT_test_infile