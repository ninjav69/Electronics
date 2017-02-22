// Interrupt service routines
#include <htc.h>
#include "config.h"
#include "uart.h"

unsigned char portb;
void interrupt my_isr(void){
	
	/***** PortB Code *****/
	if((RBIE)&&(RBIF)){
		__delay_ms(5);
		portb = PORTB >> 4;
		uart_putc(portb);
		RBIF=0;	// clear event flag
	}
	
}
