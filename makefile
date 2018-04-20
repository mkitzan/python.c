# Makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: py-tests

py-tests: py-tests.o python.o
	$(CC) py-tests.o python.o -o $@
    
py-tests.o: py-tests.c python.o
	$(CC) $(CFLAGS) py-tests.c

python.o: python.c python.h
	$(CC) $(CFLAGS) python.c

clean:
	rm *.o python-c

