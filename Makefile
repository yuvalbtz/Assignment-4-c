CC = gcc
CFLAGS = -Wall -std=c99

all: digitcompress

digitcompress: encodemain.o compress.o
	$(CC) $(CFLAGS) $^ -o $@

encodemain.o: encodemain.c compress.h
	$(CC) $(CFLAGS) -c $<

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o digitcompress
