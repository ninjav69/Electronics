#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile char clock_counter = 0;

void
main(void)
{
	int i;
	init();	// Function call inserted by C-Wiz
	PORTB = 0;
	while (1){
		PORTB = (clock_counter >> 1);
	}
}
