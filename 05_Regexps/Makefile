all: esub

esub: esub.c
	cc -g -Wall esub.c -o esub

check: esub
	./esub "ab" "BA" "eabc" > test_esub_1
	./esub "a(b)c" "\1_\1" "DabcE" > test_esub_2
	./esub "(a)b(c)d(e)" "<\3\2\1>" "_abcdef_" > test_esub_3
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > test_esub_4

	echo eabc | sed -E 's/ab/BA/' > test_sed_1
	echo DabcE | sed -E 's/a(b)c/\1_\1/' > test_sed_2
	echo _abcdef_ | sed -E 's/(a)b(c)d(e)/<\3\2\1>/' > test_sed_3
	echo '2024 17 October Thursday' | sed -E 's/([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/' > test_sed_4


	cmp test_esub_1 test_sed_1
	cmp test_esub_2 test_sed_2
	cmp test_esub_3 test_sed_3
	cmp test_esub_4 test_sed_4

clean:
	rm -rf esub test_*