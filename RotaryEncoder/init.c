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
	 *  Usart TX interrupt disabled.
	 *  Usart RX interrupt disabled.
	 */
	PIE1	= 0b00000000;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISC	= 0b11000000;
	/*
	 *  Portbit7:4 interrupt-on-change enabled
	 *  Peripheral interrupts not enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b00001000;
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b11110000;
	
	/***** Usart Code ****
	 *  High speed baud rate generator enabled
	 *  Usart in Asynchronous mode
	 *  Usart transmission enabled
	 *  TX in eight bit format
	 */
	TXSTA	= 0b00100100;
	/*
	 *  Usart reception disabled
	 *  RX in eight bit format
	 *  Usart module enabled
	 */
	RCSTA	= 0b10000000;
	/*
	 *  Baud rate is 9600
	 */
	SPBRG	= 0b10000001;
	
	ei();	// Global interrupts enabled
	
}
