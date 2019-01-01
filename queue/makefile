# makefile for stack.c
# 04-20-2018

CC=gcc
CFLAGS=-Wall -g -c

all: st-tests stack.o efuncts.o

st-tests: st-tests.o stack.o ../efuncts.o
	$(CC) st-tests.o stack.o efuncts.o -o st-tests
	
st-tests.o: st-tests.c stack.h
	$(CC) $(CFLAGS) st-tests.c

stack.o: stack.c stack.h ../efuncts.h
	 $(CC) $(CFLAGS) stack.c
	
efuncts.o: ../efuncts.c ../efuncts.h
	$(CC) $(CFLAGS) ../efuncts.c

clean:
	rm *.o st-tests

