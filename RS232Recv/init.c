#include <htc.h>

/* Program device configuration word
 * Oscillator = XT
 * Watchdog Timer = Off
 * Power Up Timer = Disabled
 * Brown Out Detect = Disabled
 * Master Clear Enable = Enabled
 * Low Voltage Program = Disabled
 * Data EE Read Protect = Disabled
 * Code Protect = Off
 */
__CONFIG(XT & WDTDIS & PWRTDIS & BORDIS & MCLREN & LVPDIS & UNPROTECT & UNPROTECT);

// Peripheral initialization function
void init(void){
	/***** Common Code ****
	 *  Portbit7:4 interrupt-on-change disabled
	 *  Peripheral interrupts enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b01000000;
	/*
	 *  Weak pullup on PORT disabled
	 */
	OPTION	= 0b10000000;
	/*
	 *  Usart TX interrupt disabled.
	 *  Usart RX interrupt enabled.
	 */
	PIE1	= 0b00100000;
	
	/***** PortA Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISA	= 0b10000000;
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b00000110;
	
	/***** Usart Code ****
	 *  High speed baud rate generator enabled
	 *  Usart in Asynchronous mode
	 *  Usart transmission disabled
	 *  TX in eight bit format
	 */
	TXSTA	= 0b00000100;
	/*
	 *  Usart reception enabled
	 *  RX in eight bit format
	 *  Usart module enabled
	 */
	RCSTA	= 0b10010000;
	/*
	 *  Baud rate is 9600
	 */
	SPBRG	= 0b00011001;
	
	ei();	// Global interrupts enabled
	
}
