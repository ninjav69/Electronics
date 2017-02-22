#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile unsigned char display = 0xff;

void
main(void)
{
	init();	// Function call inserted by C-Wiz
	TMR0 = 100;
	while (1){
		//TODO Auto-generated main function
	}
}
