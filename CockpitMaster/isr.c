// Interrupt service routines
#include <htc.h>
#include "fifo.h"
#include "adc.h"
#include "uart.h"
#include "rof.h"
#include "sb.h"

void interrupt my_isr(void){

	/***** A2D Converter Code *****/
	if((ADIE)&&(ADIF)){
		adc_interrupt();
		ADIF=0;	// clear event flag
	}

	/***** PortB Code *****/
	if((RBIE)&&(RBIF)){
		sb_interrupt();
		RBIF=0;	// clear event flag
	}

	/***** Usart Code *****/
	if((RCIE)&&(RCIF)){
		uart_interrupt();
		RCIF=0;	// clear event flag
	}

	/***** External Interrupt *****/
	if ((INTE)&&(INTF)) {
		rof_interrupt();
		INTF = 0;
	}
}
