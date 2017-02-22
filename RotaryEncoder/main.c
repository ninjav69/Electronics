#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "config.h"
#include "uart.h"

void
main(void)
{
	init();	// Function call inserted by C-Wiz
	PORTB = 0x00;
	
	while (1){
		/* Interrupts handles everything */
	}
}
