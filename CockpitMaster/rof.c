#include "rof.h"
#include "config.h"

#define ROF_IN_CLOCK_PIN 	RB0
#define ROF_IN_DATA_PIN 	RB1
#define ROF_OUT_CLOCK_PIN 	RB2
#define ROF_OUT_DATA_PIN 	RB3

static volatile unsigned char bitcount = 0;
static volatile unsigned char data = 0;
static volatile unsigned char index = 0;	// Src,Dst or Data
static struct packet_t entry;

void rof_init() {
	ROF_OUT_CLOCK_PIN = 0;
	ROF_OUT_DATA_PIN = 0;
	INTE = 1;	// enable external interrupt on RB0
}

void rof_interrupt(void) {
	data = ((data >> 1)|(ROF_IN_DATA_PIN << 7));	// capture bit
	bitcount++;

	if (bitcount == 8) {
		if (index == 0) {
			entry.src_id = data;
		} else if (index == 1) { 
			entry.dst_id = data;
		} else if (index == 2) {
			entry.data = data;
			in_push(entry);
		}
		bitcount = 0;
		data = 0;
		index++;
		if (index > 2) {
			index = 0;
		}
	}
}

void rof_write_byte(unsigned char data) {
	unsigned char i;
	
	for(i = 0; i < 8; i++) {
		ROF_OUT_DATA_PIN = data & 0x01;
		data >>= 1;
		__delay_us(50);
		ROF_OUT_CLOCK_PIN = 1;
		__delay_us(50);
		ROF_OUT_CLOCK_PIN = 0;
		__delay_us(50);
	}
}

