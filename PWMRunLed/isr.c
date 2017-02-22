// Interrupt service routines
#include <htc.h>

#define TMR_OFFSET 100
#define PWM_END_POS 100


static char pwm_pos = 0;
extern volatile char pwm[8];

void interrupt my_isr(void){
	int i;
	
	/***** Timer 0 Code *****/
	if((T0IE)&&(T0IF)){

		// Check all PWM markers
		for (i = 0; i < 8; i++) 
		{
			if (pwm_pos > pwm[i]) {
				PORTB &= ~(1 << i);
			}
		}
		
		// Advance to the next PWM position
		pwm_pos++;
		if (pwm_pos > PWM_END_POS)
		{
			PORTB=0xff;
			pwm_pos = 0;
		}
		TMR0=TMR_OFFSET;	// scale the timer
		T0IF=0;	// clear event flag
	}
}
