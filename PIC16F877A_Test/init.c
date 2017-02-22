#include <htc.h>

/* Program device configuration word
 * Oscillator = HS
 * Watchdog Timer = Off
 * Power Up Timer = On
 * Brown Out Detect = Off
 * Low Voltage Program = Disabled
 * Flash Program Write = Write Protection Off
 * Background Debug = Disabled
 * Data EE Read Protect = Off
 * Code Protect = Off
 */
__CONFIG(HS & WDTDIS & PWRTEN & BORDIS & LVPDIS & WRTEN & DEBUGDIS & DUNPROT & UNPROTECT);

// Peripheral initialization function
void init(void){
	/***** Common Code ****
	 *  Weak pullup on PORT disabled
	 */
	OPTION	= 0b10000000;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISE	= 0b00000000;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISA	= 0b00000000;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISC	= 0b00000000;
	/*
	 *  Portbit7:4 interrupt-on-change disabled
	 *  Peripheral interrupts not enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b00000000;
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b00000000;
	
	/***** PortD Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISD	= 0b00000000;
	
	ei();	// Global interrupts enabled
	
}
