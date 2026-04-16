CC=gcc
# warn about failure to inline functions
# warn when using variable-length arrays
# warn about all cases of overflow
WFLAGS=-Wall -Wextra -Wpedantic -Wvla -Winline -Wstrict-overflow=5 -Wshift-overflow=2
# enforce 2s complement signed arithmetic
CFLAGS=-fwrapv -O3
LFLAGS=-lm -lX11 -lXext

test01: main.c test01.c
	$(CC) $(CFLAGS) $(WFLAGS) $(LFLAGS) -o test01 test01.c

clean:
	rm -f test01 *.o *.ppm *.png

run: test01
	./test01
	which magick &>/dev/null \
		&& magick img.ppm img.png \
		|| convert img.ppm img.png
