# makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: ar-tests array.o efuncts.o

ar-tests: ar-tests.c ar-tests.o ../efuncts.o array.o
	$(CC) ar-tests.o ../efuncts.o array.o -o $@
	
ar-tests.o: ar-tests.c array.h
	$(CC) $(CFLAGS) ar-tests.c
	
array.o: array.c array.h ../efuncts.h
	$(CC) $(CFLAGS) array.c
	
efuncts.o: ../efuncts.c ../efuncts.h
	$(CC) $(CFLAGS) ../efuncts.c

clean:
	rm *.o ar-tests

