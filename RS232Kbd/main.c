#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile extern char bitcount;
volatile extern bit kbhit;
volatile extern char data;

void putch(unsigned char byte) {
	while (!TXIF) {
		continue;
	}
	TXREG = byte; 
}

void
main(void)
{
	unsigned char byte = 0;
	init();	// Function call inserted by C-Wiz
	while (1){
		int i;
		
		init();	// Function call inserted by C-Wiz
		
		while (1){
			/* Interrupt handler does everything */
			if (kbhit) {
				RB3 = 1;
				putch(data);
				bitcount = 0;
				data = 0;
				kbhit = 0;
				RB3 = 0;
			}
		}
	}
}
