CC=cc
BIN_DIR=/usr/bin
LDFLAGS=`sdl-config --cflags --libs` -lSDL_gfx
CFLAGS=`sdl-config --cflags` -I./include

INSTALL=/usr/bin/install -c

emu: main.o input.o memory.o video.o vpu.o
	$(CC) $(LDFLAGS) -o $@ $^

.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f emu *.o core core.*
