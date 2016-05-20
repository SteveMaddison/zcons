CC=cc
BIN_DIR=/usr/bin
LDFLAGS=`sdl-config --cflags --libs`
INCLUDES=-I./include

INSTALL=/usr/bin/install -c

emu: main.o memory.o video.o vpu.o
	$(CC) $(LDFLAGS) -o $@ $^

.c.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f emu *.o core core.*
