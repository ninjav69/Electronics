#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile char data;	// data from port
volatile bit recv;	// data recieved flag

void
main(void)
{
	init();	// Function call inserted by C-Wiz
	while (1){
		if (recv) {
			RB3 = 1;
			PORTA = data;
			data = 0;
			recv = 0;
			RB3 = 1;
		}
	}
}
