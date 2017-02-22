/*
 * This module is used for one-way 2-wire comms between
 * chips. The idea is to daisy-chain PIC micros for the
 * c172p cockpit that we're building. There are 2 sides
 * to this coin - a sending side and a receiving side. This
 * implements the sending side. 8 bits are clocked out on
 * the designated clock and data line. Clock ide is low and
 * a bit is transmitted by a rising edge. The micro on the
 * receiving end has RB0 set as interrupt on rising edge, which
 * can respond to the clock signals from the sender. Data is
 * transmitted MSB first - almost like the PS2 keyboard.
 */
#ifndef PS2COMMS_H_
#define PS2COMMS_H_

#include <htc.h>

#define PS2_CLOCK_PIN RB2
#define PS2_DATA_PIN RB3

void ps2_init();

/*
 * Writes a byte on the designated wire
 */
void ps2_write_byte(unsigned char data);

#endif /*PS2COMMS_H_*/
