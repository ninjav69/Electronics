#include "init.h"	// included by C-Wiz
#include <htc.h>
#include "fifo.h"
#include "uart.h"
#include "config.h"
#include "adc.h"

void
main(void)
{
	init();	// Function call inserted by C-Wiz

	INTE = 1;	// enable external interrupt on RB0
	
	while (1){
		if (!(ADGO || ADIF)) {
			adc_advance();
			adc_read();
		}
		// Service the fifo - sending pending
		// entries to RS232
		if (pending()) {
			struct entry_t entry = pop();
			putc(entry.key);
			putc(entry.value);
			__delay_ms(10);
			RD6 = 0;
		}
	}
}
