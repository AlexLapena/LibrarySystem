CC = gcc

all: liblistio.a

# Creates Library
liblistio.a: src/listio.c
	$(CC) src/listio.c -o src/listio.o -c
	ar cr liblistio.a src/listio.o

# Runs test program
run: main.c
	$(CC) main.c -llistio -L. -o run

clean:
	rm -rf *.o run *.bin liblistio.a
