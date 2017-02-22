// Interrupt service routines
#include <htc.h>
#include "adc.h"
#include "ps2comms.h"
#include "fifo.h"
#include "config.h"

void interrupt my_isr(void){

	/***** A2D Converter Code *****/
	if((ADIE)&&(ADIF)){
		adc_interrupt();
		ADIF=0;	// clear event flag
	}

	/***** Timer 1 Code *****/
	if((TMR1IE)&&(TMR1IF)){
		PORTD = ~PORTD;
		TMR1IF=0;	// clear event flag
	}

	/***** PortB Code *****/
	if (INTF) {
		ps2_interrupt();
		INTF = 0;
	}
	
	if((RBIE)&&(RBIF)){
		__delay_ms(20);
		struct entry_t entry;
 		entry.key = 17;
 		entry.value = PORTB >> 4;
		push(entry);
		RBIF=0;	// clear event flag
	}
}
