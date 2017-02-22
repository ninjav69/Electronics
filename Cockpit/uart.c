#include "uart.h"
#include <pic.h>

void putc(unsigned char byte) {
	while (!TXIF) {
		continue;
	}
	TXREG = byte;
}

unsigned char getc(void) {
	while (!RCIF) {
		continue;
	}
	return RCREG;
}
