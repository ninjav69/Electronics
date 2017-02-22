#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "config.h"
#include "adc.h"
#include "fifo.h"
#include "rof.h"
#include "uart.h"

static void uart_send_packet(struct packet_t packet) {
	uart_putc(packet.src_id);
	uart_putc(packet.dst_id);
	uart_putc(packet.data);
	__delay_ms(10);
}

static void rof_send_packet(struct packet_t packet) {
	rof_write_byte(packet.src_id);
	rof_write_byte(packet.dst_id);
	rof_write_byte(packet.data);
	__delay_ms(10);
}

void
main(void) {
	init();	// Function call inserted by C-Wiz
	rof_init();
	
	while (1){
		if (!(ADGO || ADIF)) {
			adc_advance();
			adc_read();
		}

		// Service the fifo - sending pending
		// entries to encoded destination
		if (in_pending()) {
			struct packet_t entry = in_pop();
			if (entry.dst_id == TX_ID) {
				uart_send_packet(entry);
			} else {
				rof_send_packet(entry);
			}
		}
	}
}
