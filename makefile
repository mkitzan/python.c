# makefile for python.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: py-tests python.o list.o

py-tests: py-tests.c py-tests.o efuncts.o python.o list.o dict.o
	$(CC) py-tests.o efuncts.o python.o list.o dict.o -o $@
	
py-tests.o: py-tests.c python.h list.h dict.h
	$(CC) $(CFLAGS) py-tests.c
	
python.o: python.c python.h efuncts.h
	$(CC) $(CFLAGS) python.c

list.o: list.c list.h efuncts.h
	$(CC) $(CFLAGS) list.c

dict.o: dict.c dict.h efuncts.h
	 $(CC) $(CFLAGS) dict.c
	
efuncts.o: efuncts.c efuncts.h
	$(CC) $(CFLAGS) efuncts.c

clean:
	rm *.o py-tests

