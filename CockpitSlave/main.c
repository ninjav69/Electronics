#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "config.h"
#include "fifo.h"
#include "rof.h"

static void rof_send_packet(struct packet_t packet) {
	rof_write_byte(packet.src_id);
	rof_write_byte(packet.dst_id);
	rof_write_byte(packet.data);
	__delay_ms(10);
}

void
main(void)
{
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);
	
	init();			// Function call inserted by C-Wiz
	rof_init();
	while (1){
		// Service the fifo - sending pending
		// entries to encoded destination
		if (in_pending()) {
			struct packet_t entry = in_pop();
			if (entry.dst_id == LED_1_ID) {
				PORTD = entry.data;
			} else {
				rof_send_packet(entry);
			}
		}
	}
}
