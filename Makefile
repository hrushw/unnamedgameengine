CC=gcc
# warn about failure to inline functions
# warn when using variable-length arrays
# warn about all cases of overflow
# enforce 2s complement signed arithmetic
WFLAGS=-Wall -Wextra -Wpedantic -Wvla -Winline -Wstrict-overflow=5 -Wshift-overflow=2
CFLAGS=-fwrapv
LFLAGS=-lX11 -lXext

win: main.c
	$(CC) $(CFLAGS) $(WFLAGS) $(LFLAGS) -o win main.c

clean:
	rm -f win *.o *.ppm *.png

run: win
	./win
	which magick &>/dev/null \
		&& magick img.ppm img.png \
		|| convert img.ppm img.png
