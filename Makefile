CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: solver search_util_test

solver: search_util.o solver.o
	$(CC) search_util.o solver.o -o solver

search_util_test: search_util.o search_util_test.o
	$(CC) search_util.o search_util_test.o -o search_util_test

search_util_test.o: search_util_test.c search_util.h
	$(CC) $(CFLAGS) -c search_util_test.c

search_util.o: search_util.c search_util.h
	$(CC) $(CFLAGS) -c search_util.c

solver.o: solver.c search_util.h
	$(CC) $(CFLAGS) -c solver.c

clean:
	rm -f search_util.o solver.o search_util_test.o solver search_util_test

format:
	clang-format -i -style=file *.[ch]
