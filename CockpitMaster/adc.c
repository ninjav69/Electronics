#include <pic.h>
#include "adc.h"
#include "config.h"
#include "fifo.h"

#define CHANNEL_MASK (0x07 << 3)

static unsigned char values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

/*
 * Keeps track of the channel we're currently
 * servicing.
 */

static unsigned char adc_channel = 0;

void adc_advance(void) {
	adc_channel++;					// select next channel for next read
	adc_channel &= 0x07;
}

void adc_read(void) {
	ADCON0 &= ~CHANNEL_MASK;		// clear current channel select
	ADCON0 |= (adc_channel << 3);	// apply the new channel select
	ADIF = 0;
	ADIE = 1;
	PEIE = 1;
	GIE = 1;
	__delay_us(20);					// wait for hold capacitor to charge up
	ADGO = 1;						// initiate conversion on newly selected channel
}

void adc_interrupt(void) {
	struct packet_t entry;
	unsigned char new_value = ADRESH;
	unsigned char old_value = values[adc_channel];
	unsigned char lo_bound = new_value;
	unsigned char hi_bound = new_value;
	
	/*
	 * Calculate deadzone.
	 */

	if (lo_bound > 0) {
		lo_bound--;
	}
	if (hi_bound < 255) {
		hi_bound++;
	}
	
	/*
	 * Do checking to see if we have
	 * a change in value. If there's
	 * no change there's no need to
	 * enqueue an entry.
	 */
	
	if (old_value < lo_bound || old_value > hi_bound) {
		values[adc_channel] = new_value;
		entry.src_id = adc_channel + 1;	// +1 to map adc channels to device id's
		entry.dst_id = TX_ID;			// forward to PC
		entry.data = new_value;
		in_push(entry);
	}
}
