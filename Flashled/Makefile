CC=picc
SRC=init.c main.c
CHIP=16F84
BUILDIR=build

all: 
	$(CC) $(SRC) --chip=$(CHIP) --outdir=$(BUILDIR) $(OBJS) -Omain

install:
	picp /dev/ttyS0 16f84 -bp -wp $(BUILDIR)/main.hex

clean:
	rm build/*
	rm funclist

