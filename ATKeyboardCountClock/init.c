#include <htc.h>

/* Program device configuration word
 * Oscillator = XT
 * Watchdog Timer = Off
 * Power Up Timer = On
 * Code Protect = Off
 */
__CONFIG(XT & WDTDIS & 0x3FF7 & UNPROTECT);

// Peripheral initialization function
void init(void){
	/***** Common Code ****
	 *  Portbit7:4 interrupt-on-change disabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b00000000;
	/*
	 *  Weak pullup on PORT disabled
	 */
	OPTION	= 0b10000000;
	
	/***** PortA Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISA	= 0b00010000;
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b00000001;
	
	/*
	 * Enable external interrupts.
	 */
	INTEDG = 1;	// falling edge triggers interrupts
	INTE = 1;
	
	ei();	// Global interrupts enabled
	
}
