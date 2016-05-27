CC=cc
BIN_DIR=/usr/bin
LDFLAGS=`sdl2-config --libs` -lSDL2_image
CFLAGS=`sdl2-config --cflags` -O0 -g -I./include

INSTALL=/usr/bin/install -c

tileconv: main.o
	$(CC) $(LDFLAGS) -o $@ $^

.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f tileconv *.o core core.*
