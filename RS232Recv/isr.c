// Interrupt service routines
#include <htc.h>

extern volatile char data;	// data from port
extern volatile bit recv;	// data recieved flag

void interrupt my_isr(void){

	/***** Usart Code *****/
	if((RCIE)&&(RCIF)){
		data = RCREG;
		recv = 1;
		RCIF=0;	// clear event flag
	}
	
}
