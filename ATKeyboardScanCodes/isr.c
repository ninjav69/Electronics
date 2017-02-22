// Interrupt service routines
#include <htc.h>

volatile extern char scan_code;
volatile extern bit key_pressed;

int timer = 0;
char count = 0;

void interrupt my_isr(void){

	/***** Timer 0 Code *****/
	if((T0IE)&&(T0IF)){
		timer++;
		if (timer > 70) {
			//scan_code = 0;
			timer = 0;
			//PORTB = 0;
		}
		T0IF = 0;	// clear event flag
	}
	
	/* Extern interrupt code */
	if (INTF) {
		//TMR0 = 0;
		//T0IE = 0;	// Disable timer interrupts
		
		count++;

		if (count == 1) {
			// Start bit, reset scan code
			scan_code = 0;
			PORTB = 0;
		} 
		else if (count == 2) {
			scan_code |= RA4;
		} 
		else if (count == 3) {
			scan_code |= (RA4<<1);
			RB1 = RA4;
		} 
		else if (count == 4) {
			scan_code |= (RA4<<2);
			RB2 = RA4;
		} 
		else if (count == 5) {
			scan_code |= (RA4<<3);
			RB3 = RA4;
		} 
		else if (count == 6) {
			scan_code |= (RA4<<4);
			RB4 = RA4;
		} 
		else if (count == 7) {
			scan_code |= (RA4<<5);
			RB5 = RA4;
		} 
		else if (count == 8) {
			scan_code |= (RA4<<6);
			RB6 = RA4;
		} 
		else if (count == 9) {
			scan_code |= (RA4<<7);
			RB7 = RA4;
		} 
		else if (count == 10) {
			// ignore parity
		} else if (count == 11) {
			// Stop bit, reset counter
			count = 0;
			//key_pressed = 1;
		} 
		
		INTF = 0;
		//T0IE = 1;	// Enable timer interrupts
	}
}
