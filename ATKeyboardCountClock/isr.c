// Interrupt service routines
#include <htc.h>

volatile extern char clock_counter;

void interrupt my_isr(void){

	// No interrupts generated
	if (INTF) {
		clock_counter++;
		INTF = 0;
	}
	
}
