WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_CONVERT -DTEST_READLIST -DTEST_DELETELIST -DTEST_ADDNODE -DTEST_DELETENODE

SRCS = main.c list.c convert.c
OBJS = $(SRCS:%.c=%.o)

Arithmetic: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o Arithmetic

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testall: test1 test2 test3 test4 test5

test1: Arithmetic
	./Arithmetic inputs/test1 > output1
	diff output1 expected/expected1

test2: Arithmetic
	./Arithmetic inputs/test2 > output2
	diff output2 expected/expected2

test3: Arithmetic
	./Arithmetic inputs/test3 > output3
	diff output3 expected/expected3

test4: Arithmetic
	./Arithmetic inputs/test4 > output4
	diff output4 expected/expected4

test5: Arithmetic
	./Arithmetic inputs/test5 > output5
	diff output5 expected/expected5

clean: # remove all machine generated files
	rm -f Arithmetic *.o output?
