#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "uart.h"
#include "adc.h"
#include "config.h"

/*
 * Indicates activity in the main loop.
 */
#define INDICATOR RA4

/*
 * Switch block constants
 */

#define SB1 9	// first channel after analog inputs
#define	SB1_PORT PORTB


/*
 * Stores the old channel values for detecting
 * changes in the readings.
 */
unsigned short last_val[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };


/*
 * Writes a packet to the serial port designating the
 * channel number that changed and the new value.
 */
void report_channel(unsigned char channel, unsigned short val) {
	putc(0xff);
	__delay_ms(10);
	putc(channel);
	__delay_ms(10);
	putc((unsigned char)(val >> 8));
	__delay_ms(10);
	putc((unsigned char)(val & 0xff));
	__delay_ms(10);
	putc(0xfe);
	__delay_ms(10);
}

/*
 * Writes a packet to the serial port designating the
 * switch block that changed and the new value.
 */

void report_switchblock(unsigned char channel, unsigned char val) {
	putc(0xff);
	__delay_ms(10);
	putc(channel);
	__delay_ms(10);
	putc((unsigned char)0);	// unused - still present for the sake of packet alignment
	__delay_ms(10);
	putc(val);
	__delay_ms(10);
	putc(0xfe);
	__delay_ms(10);
}

void delay() {
	char i;
	__delay_ms(20);
}

void
main(void)
{
	int i;
	unsigned short val;
	unsigned char ch;
	unsigned char sb1_status;	// Switch block 1 (PORTB)
	
	init();	// Function call inserted by C-Wiz
	
	// Turn off comparitor module
	
	CMCON = 0b00000111;
	
	// Fetch initial switch block and submit
	sb1_status = SB1_PORT;
	report_switchblock(SB1, sb1_status);
	
	while (1){
		// Indicate activity.
		INDICATOR = 1;

		/*
		 * Scan all channels for changes.
		 */
		for (ch = 0; ch < 6; ch++) {
			val = read_channel(ch);
			// Test for changes using a 'deadzone' to eliminate error.
			if (val < (last_val[ch] - 2) || val > (last_val[ch] + 2)) {
				last_val[ch] = val;
				report_channel(ch, val);
			}
		}
		
		/*
		 * Check if a switch position changed. If it did, send
		 * the entire switch block over RS232
		 */
		
		//if (sb1_status != SB1_PORT) {
			sb1_status = SB1_PORT;
			report_switchblock(SB1, sb1_status);
		//}
		
		// Wait a while.
		delay();
		INDICATOR = 0;
		delay();
	}
}
