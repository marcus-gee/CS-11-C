#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: 1dCA_arrays 1dCA_pointers
	
1dCA_arrays: 1dCA_arrays.o memcheck.o 
	$(CC) 1dCA_arrays.o -o 1dCA_arrays memcheck.o
	
1dCA_arrays.o: 1dCA_arrays.c memcheck.c
	$(CC) $(CFLAGS) -c 1dCA_arrays.c memcheck.c

1dCA_pointers: 1dCA_pointers.o memcheck.o 
	$(CC) 1dCA_pointers.o -o 1dCA_pointers memcheck.o
	
1dCA_pointers.o: 1dCA_pointers.c memcheck.c
	$(CC) $(CFLAGS) -c 1dCA_pointers.c memcheck.c
		
memcheck.o: memcheck.c
	$(CC) $(CFLAGS) -c memcheck.c
	
check:
	c_style_check 1dCA_arrays.c 1dCA_pointers.c

clean:
	rm -f 1dCA_pointers.o 1dCA_arrays.o 1dCA_arrays 1dCA_pointers memcheck.o


