#include <pic.h>
#include "adc.h"
#include "config.h"

#define CHANNEL_MASK (0x07 << 3)

unsigned short read_channel(unsigned char channel) {
	unsigned short rv;
	channel &= 0x07;			// truncate channel to 3 bits
	ADCON0 &= ~CHANNEL_MASK;	// clear current channel select
	ADCON0 |= (channel << 3);	// apply the new channel select
	__delay_us(20);				// wait for hold capacitor to charge up
	ADGO = 1;					// initiate conversion on newly selected channel
	while (ADGO) {
		continue;
	}
	rv = (ADRESH << 8) & 0xFF00;
	rv |= ADRESL & 0x00FF;
	return rv;
}
