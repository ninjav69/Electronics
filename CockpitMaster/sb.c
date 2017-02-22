#include "sb.h"
#include "config.h"
#include "htc.h"
#include "fifo.h"

void sb_interrupt(void) {
	struct packet_t packet;

	__delay_ms(20);	// wait for switchbounce to settle
 	packet.src_id = SB_1_ID;
 	packet.dst_id = TX_ID;
 	packet.data = PORTB >> 4;
	in_push(packet);
}

