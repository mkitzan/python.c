# makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: lt-tests list.o efuncts.o

lt-tests: lt-tests.o list.o ../efuncts.o
	$(CC) lt-tests.o list.o efuncts.o -o lt-tests
	
lt-tests.o: lt-tests.c list.h
	$(CC) $(CFLAGS) lt-tests.c

list.o: list.c list.h ../efuncts.h
	 $(CC) $(CFLAGS) list.c
	
efuncts.o: ../efuncts.c ../efuncts.h
	$(CC) $(CFLAGS) ../efuncts.c

clean:
	rm *.o lt-tests

