// Interrupt service routines
#include <htc.h>

volatile char bitcount = 0;
volatile bit kbhit = 0;
volatile char data = 0;

/*
 * This routine works for a fact, but the bits
 * that we capture from the keyboard data line are
 * reversed.
 *
 */
void interrupt my_isr(void){
	// External interrupt from keyboard clock
	if (INTF) {

		// Start bit and parity is ignored. Only data
		// bits are captured and stop bit indicates end of packet
		if (bitcount > 0 && bitcount < 9) {
			data = ((data >> 1)|(RA4 << 7));	// capture bit
		} else if (bitcount == 10) {
			kbhit = 1;	// signal main thread that a key was pressed
		}
		bitcount++;
		INTF = 0;
	}
}
