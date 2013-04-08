CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430g2553

BINARIES=simple binout pushcount lowpowled bad_recursion

all: $(BINARIES)

clean:
	rm $(BINARIES)
