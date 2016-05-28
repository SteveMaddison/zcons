CC=cc
BIN_DIR=/usr/bin
LDFLAGS=`sdl2-config --libs` -lSDL2_gfx
CFLAGS=`sdl2-config --cflags` -O0 -g -I./include -I./include/z80emu

INSTALL=/usr/bin/install -c

emu: main.o input.o io.o memory.o video.o vpu.o z80emu.o
	$(CC) $(LDFLAGS) -o $@ $^

.c.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f emu *.o core core.*
