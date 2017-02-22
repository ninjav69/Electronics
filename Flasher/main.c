#include "init.h"	// included by C-Wiz
#include <htc.h>

void
main(void)
{
	int i;
	
	init();	// Function call inserted by C-Wiz
	while (1){
		RB0 = 1;
		for (i = 0; i < 4000; i++);
		RB0 = 0;
		for (i = 0; i < 4000; i++);
	}
}
