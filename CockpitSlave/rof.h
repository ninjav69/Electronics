#ifndef ROF_H_
#define ROF_H_

#include <htc.h>
#include "fifo.h"

void rof_init();
void rof_interrupt(void);
void rof_write_byte(unsigned char data);

#endif /*ROF_H_*/
