// Interrupt service routines
#include <htc.h>

volatile char bitcount = 0;
volatile bit kbhit = 0;
volatile int data = 0;

void interrupt my_isr(void){

	// No interrupts generated
	if (INTF) {

		data |= RA4;	// capture data line state
		
		bitcount++;
		if (bitcount == 11) {
			kbhit = 1;	// signal main thread that a key was pressed
		} else {
			data <<= 1; // make way for new bit (until we read it all)
		}
		
		INTF = 0;
	}
}
