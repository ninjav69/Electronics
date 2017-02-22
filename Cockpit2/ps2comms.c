#include "ps2comms.h"
#include "config.h"
#include "fifo.h"

#define PS2_INPUT_PIN RB1

static volatile unsigned char bitcount = 0;
static volatile unsigned char data = 0;
static volatile bit index = 0;	// is this a key or value
static struct entry_t entry;

void ps2_interrupt(void) {
	data = ((data >> 1)|(PS2_INPUT_PIN << 7));	// capture bit
	bitcount++;

	if (bitcount == 8) {
		if (index) {
			entry.value = data;
			push(entry);
		} else { 
			entry.key = data;
		}
		bitcount = 0;
		data = 0;
		index = ~index;
	}
}
