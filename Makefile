CC=gcc
# warn about failure to inline functions
# warn when using variable-length arrays
# enforce 2s complement signed arithmetic
CFLAGS=-Wall -Wextra -Wpedantic -Wvla -Winline -fwrapv
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
