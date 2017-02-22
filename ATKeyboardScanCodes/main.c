#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile char scan_code = 0;
volatile bit key_pressed = 0;

extern char count;

void
main(void)
{
	init();	// Function call inserted by C-Wiz

	/* Enable external interupt on falling edge */
	INTEDG = 0;
	INTE = 1;
	
	/* Enable timer */
	T0IE = 0;

	while (1){
		if (key_pressed) {
			PORTB = (count << 2);
			key_pressed = 0;
			count = 0;
		}
	}
}
