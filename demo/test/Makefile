TARGETS=test.bin
SRCS=main.s 

all: ${TARGETS}

clean:
	rm -f ${TARGETS}

test.bin: $(SRCS)
	z80asm -o $@ $<
	@ls -l $@ | awk '{print "$@: " $$5 " bytes"}'

dump: $(TARGETS)
	hexdump -C $<
