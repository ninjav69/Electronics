// Interrupt service routines
#include <htc.h>
#include "sb.h"
#include "rof.h"

void interrupt my_isr(void){

	/***** PortB Code *****/
	if((RBIE)&&(RBIF)){
		sb_interrupt();
		RBIF=0;	// clear event flag
	}

	/***** External Interrupt *****/
	if ((INTE)&&(INTF)) {
		rof_interrupt();
		INTF = 0;
	}
}
