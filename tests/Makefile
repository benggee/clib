CC=gcc
CFLAGS=

.PHONY: all clean

all: thread_pool_test linked_list_test ioprint_test

thread_pool_test: thread_pool_test.c ../thread_pool.c ../thread_pool.h ../hh.h
	$(CC) -lpthread -o thread_pool_test thread_pool_test.c ../thread_pool.c ../thread_pool.h ../hh.h

linked_list_test: linked_list_test.c ../list.h ../list.c ../dlist.h ../dlist.c ../hh.h
	$(CC) -o linked_list_test linked_list_test.c ../list.h ../list.c ../dlist.h ../dlist.c

ioprint_test: ioprint_test.c ../ioprint.h
	$(CC) -o ioprint_test ioprint_test.c ../ioprint.h

clean:
	rm -rf thread_pool_test linked_list_test ioprint_test
