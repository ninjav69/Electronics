#include "uart.h"
#include <pic.h>
#include "fifo.h"

static struct packet_t packet;
static volatile unsigned char index = 0;

void uart_putc(unsigned char byte) {
	while (!TXIF) {
		continue;
	}
	TXREG = byte;
}

unsigned char uart_getc(void) {
	while (!RCIF) {
		continue;
	}
	return RCREG;
}

void uart_interrupt(void) {
	unsigned char data = RCREG;
	if (index == 0) {
		packet.src_id = data;
	} else if (index == 1) { 
		packet.dst_id = data;
	} else if (index == 2) {
		packet.data = data;
		in_push(packet);
	}
	index++;
	if (index > 2) {
		index = 0;
	}
}
