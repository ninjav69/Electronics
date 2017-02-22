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
	 *  Timer 1 interrupt enabled.
	 *  Usart TX interrupt disabled.
	 *  Usart RX interrupt disabled.
	 *  A2D interrupt enabled
	 */
	PIE1	= 0b01000001;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISE	= 0b00000111;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISA	= 0b00101111;
	/*
	 *  Port directions: 1=input, 0=output
	 */
	TRISC	= 0b11000000;
	/*
	 *  Portbit7:4 interrupt-on-change enabled
	 *  Peripheral interrupts enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b01001000;
	
	/***** A2D Converter Code ****
	 *  A2D module powered up
	 *  Channel selected is AN0
	 *  conversion clock is set at Fosc/32
	 */
	ADCON0	= 0b10000001;
	/*
	 *  Analog/Digital ports using configuration 0
	 *  Format is left justified
	 */
	ADCON1	= 0b00000000;
	
	/***** PortB Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISB	= 0b11110011;
	
	/***** PortD Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISD	= 0b00000000;
	
	/***** Timer 1 Code ****
	 *  Timer is active and running
	 *  Timer derived from system clock
	 *  External clock input is not synchronized
	 *  T1 oscillator circuit (for external input) is inactive
	 *  Timer prescaler is 1:8
	 */
	T1CON	= 0b00110101;
	
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
