# makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: dc-tests dict.o efuncts.o

dc-tests: dc-tests.o dict.o ../efuncts.o
	$(CC) dc-tests.o dict.o ../efuncts.o -o dc-tests
	
dc-tests.o: dc-tests.c dict.h
	$(CC) $(CFLAGS) dc-tests.c

dict.o: dict.c dict.h ../efuncts.h
	 $(CC) $(CFLAGS) dict.c
	
efuncts.o: ../efuncts.c ../efuncts.h
	$(CC) $(CFLAGS) ../efuncts.c

clean:
	rm *.o dc-tests

