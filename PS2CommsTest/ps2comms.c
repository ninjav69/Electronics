#include "ps2comms.h"
#include "config.h"

void ps2_init() {
	PS2_CLOCK_PIN = 0;
	PS2_DATA_PIN = 0;
}

void ps2_write_byte(unsigned char data) {
	unsigned char i;
	
	for(i = 0; i < 8; i++) {
		PS2_DATA_PIN = data & 0x01;
		data >>= 1;
		__delay_us(50);
		PS2_CLOCK_PIN = 1;
		__delay_us(50);
		PS2_CLOCK_PIN = 0;
		__delay_us(50);
	}
}
