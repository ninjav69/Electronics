#include "init.h"	// included by C-Wiz
#include <htc.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000
#endif //_XTAL_FREQ

void main(void) {
    char output = 1;
    char i;

    init();	// Function call inserted by C-Wiz
    while (1){
        for (i = 0; i < 7; i++)
        {
            PORTB = output;
            output <<= 1;
            __delay_ms(200);
        }
        for (i = 0; i < 7; i++)
        {
            PORTB = output;
            output >>= 1;
            __delay_ms(200);
        }
    }
}

