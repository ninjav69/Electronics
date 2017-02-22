#include "init.h"	// included by C-Wiz
#include <htc.h>

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
	char ch;
	
	init();	// Function call inserted by C-Wiz
	while (1){
		putch((PORTA & 0x0f) | (PORTB & 0xf0));
		RB0 = 1;
		for(i = 0; i < 4000; i++);
		RB0 = 0;
		for(i = 0; i < 4000; i++);
	}
}
