# makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: py-tests python.o list.o

py-tests: py-tests.c py-tests.o emalloc.o python.o list.o
	$(CC) py-tests.o emalloc.o python.o list.o -o $@
	
py-tests.o: py-tests.c python.h list.h
	$(CC) $(CFLAGS) py-tests.c
	
python.o: python.c python.h emalloc.h
	$(CC) $(CFLAGS) python.c

list.o: list.c list.h emalloc.h
	 $(CC) $(CFLAGS) list.c
	
emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm *.o py-tests

