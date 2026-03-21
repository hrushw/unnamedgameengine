CC=gcc
CFLAGS=-Wall -Wextra -Wvla -Wpedantic

game: main.c
	$(CC) $(CFLAGS) -o game main.c

clean:
	rm -f game *.o
