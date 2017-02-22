/*
 * We use this program to debug AT Keyboard data packets. Bit
 * in each position in the 11-bit packet is output on the
 * available PORTA and PORTB pins. This is to help us see if
 * our interrupt routine works okay.
 */
#include "init.h"	// included by C-Wiz
#include <htc.h>


volatile extern char bitcount;
volatile extern bit kbhit;
volatile extern int data;

void
main(void)
{
	int i;
	
	init();	// Function call inserted by C-Wiz
	
	PORTA = 0;
	PORTB = 0;
	
	while (1){
		/* Interrupt handler does everything */
		if (kbhit) {
			PORTA = bitcount;
			PORTB = (data >> 2);
			bitcount = 0;
			data = 0;
			kbhit = 0;
		}
	}
}
