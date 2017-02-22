#include "init.h"	// included by C-Wiz
#include <htc.h>

#define TX_PIN POR

void putch(unsigned char byte) {
	while (!TXIF) {
		continue;
	}
	TXREG = byte;
}

void
main(void)
{
	int i;
	init();	// Function call inserted by C-Wiz
	while (1){
		// Write a string
		putch('H');
		putch('e');
		putch('l');
		putch('l');
		putch('o');
		putch('\n');
		RB3 = !RB3;
		for (i = 0; i < 4000; i++);
	}
}
