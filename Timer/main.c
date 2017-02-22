#include "init.h"	// included by C-Wiz
#include <htc.h>

volatile char task_counter1 = 200;
volatile char task_counter2 = 100;
volatile char task_counter3 = 50;
volatile char output = 1;
volatile int task_blocker = 0;

void
main(void)
{
	init();	// Function call inserted by C-Wiz
	while (1){
		PORTB = output;
	}
}
