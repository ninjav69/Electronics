/*
 * This is a simple exercise in multitasking. It is a running led
 * program with a bit of a twist : instead of just running the leds
 * from PORTB.0 - PORTB.7 and back again, we use PWM to dim a LED
 * once it was activated. We do this by keeping an array of PWM values
 * for each PORTB pin. We set up a 10ms timer interrupt that keeps a
 * local position counter between 0-100. This timing allows us to
 * create a PWM signal at +/-100Hz - which is a good value for
 * LED dimming purposes. The timer uses it's own position indicator
 * and the PWM table of the pins to determine when to set a pin
 * hi or low. When the counter is reset, it sets all pins low. For
 * every counter interrupt, the position indicator is incremented
 * and checked if it's greater than the PWM of each pin. If it becomes
 * greater than a PWM pin, that pin is set to hi. Once the counter reach
 * 100, it's reset back to zero and the pins are set low again. The
 * fade-out of the LEDS are accompished by decrementing the values
 * in the PWM table until they reach 0 duty cycle. This effectively
 * turns the LED completely off. The running sequence itself is
 * basically lazily performed in the main loop.
 */ 
#include "init.h"	// included by C-Wiz
#include <htc.h>

/*
 * We store the PWM values in an array - one array element
 * for each PORTB pin.
 */

volatile char pwm_init[8] = { 100, 100, 100, 100, 50, 50, 50, 50 };
volatile char pwm[8] = { 100, 100, 100, 100, 50, 50, 50, 50 };

void
main(void)
{
	int i;
	init();	// Function call inserted by C-Wiz
	PORTB = 0xff;
	while (1){
		for (i = 0; i < 100; i++);
		for(i = 0; i < 8; i++) {
			pwm[i]--;
			if (pwm[i] == 0)
			{
				pwm[i] = pwm_init[i];
			}
		}
	}
}
