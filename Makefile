CC=gcc
CFLAGS=-Wall -Wextra -Wvla -Wpedantic -Winline
LFLAGS=-lX11 -lXext

game: main.c
	$(CC) $(CFLAGS) $(LFLAGS) -o game main.c

clean:
	rm -f game *.o

run: game
	./game
	which magick &>/dev/null \
		&& magick gaem.ppm gaem.png \
		|| convert gaem.ppm gaem.png
