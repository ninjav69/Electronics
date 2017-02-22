// Interrupt service routines
#include <htc.h>

extern volatile unsigned char display;

void interrupt my_isr(void){

	/***** Timer 0 Code *****/
	if((T0IE)&&(T0IF)){

		PORTB = display;	// copy character to display pins
		display = ~display;	// invert the bitmask for next display
		
		TMR0 = 100;	// offset for 10ms interval
		T0IF=0;	// clear event flag
	}
}
