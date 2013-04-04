CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430g2553

BINARIES=simple binout pushcount lowpowled

all: $(BINARIES)

clean:
	rm $(BINARIES)
