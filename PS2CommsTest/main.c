#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "config.h"
#include "fifo.h"
#include "ps2comms.h"

void
main(void)
{
	init();	// Function call inserted by C-Wiz
	ps2_init();
	
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);
	__delay_ms(30);

	while (1){
		// Service the fifo - sending pending
		// entries to ps2 port
		if (pending()) {
			struct entry_t entry = pop();
			ps2_write_byte(entry.key);
			ps2_write_byte(entry.value);
			__delay_ms(10);
		}
	}
}
