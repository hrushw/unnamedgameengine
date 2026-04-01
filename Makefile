CC=gcc
CFLAGS=-Wall -Wextra -Wvla -Wpedantic -Winline
LFLAGS=-lX11 -lXext

win: main.c
	$(CC) $(CFLAGS) $(LFLAGS) -o win main.c

clean:
	rm -f win *.o *.ppm *.png

run: win
	./win
	which magick &>/dev/null \
		&& magick img.ppm img.png \
		|| convert img.ppm img.png
