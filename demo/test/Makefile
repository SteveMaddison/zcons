TARGETS=rom.img
SRCS=main.s
TILECONV=../../tools/tileconv/tileconv

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *.bin

test.bin: $(SRCS)
	z80asm -o $@ $<
	@ls -l $@ | awk '{print "$@: " $$5 " bytes"}'

tiles.bin: tiles.png
	${TILECONV} $< $@

rom.img: test.bin tiles.bin
	dd if=/dev/zero of=$@ bs=32k count=1
	dd if=tiles.bin of=$@ bs=16k seek=1 conv=notrunc
	dd if=test.bin of=$@ conv=notrunc

dump: $(TARGETS)
	hexdump -C $<
