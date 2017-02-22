// Interrupt service routines
#include <htc.h>
#include "fifo.h"
#include "config.h"

void interrupt my_isr(void){

	/***** PortB Code *****/
	if((RBIE)&&(RBIF)){
		__delay_ms(20);
		struct entry_t entry;
 		entry.key = 18;
		entry.value = PORTB >> 4;
		push(entry);
		RBIF=0;	// clear event flag
	}
}
