// Interrupt service routines
#include <htc.h>

volatile extern char task_counter1;
volatile extern char task_counter2;
volatile extern char task_counter3;
volatile extern char output;
volatile extern int task_blocker;

void interrupt my_isr(void){

	/***** Timer 0 Code *****/
	if((T0IE)&&(T0IF)){
		task_blocker++;
		if (task_blocker < 10)
		{
			T0IF=0;	// clear event flag
			return;
		}
		task_blocker = 0;
		
		task_counter1--;
		if (task_counter1 == 0)
		{
			output <<= 3;
			if (output == 0) 
			{
				output = 1;
			}
			task_counter1 = 200; 
		}
		
		task_counter2--;
		if (task_counter2 == 0)
		{
			output >>= 1;
			if (output == 0) 
			{
				output = 1;
			}
			task_counter2 = 100;
		}
		
		task_counter3--;
		if (task_counter3 == 0)
		{
			output ^= 0xff;	/* flip it upside down */
			if (output == 0) 
			{
				output = 1;
			}
			task_counter3 = 50;
		}

		T0IF=0;	// clear event flag
	}
}
