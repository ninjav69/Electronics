#include <htc.h>

/* Program device configuration word
 * Oscillator = XT
 * Watchdog Timer = Off
 * Power Up Timer = Enabled
 * Brown Out Detect = Disabled
 * Master Clear Enable = Disabled
 * Low Voltage Program = Disabled
 * Data EE Read Protect = Disabled
 * Code Protect = Off
 */
__CONFIG(XT & WDTDIS & PWRTEN & BORDIS & MCLRDIS & LVPDIS & UNPROTECT & UNPROTECT);

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
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b00000000;
	
	ei();	// Global interrupts enabled
	
}
