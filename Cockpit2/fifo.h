/*
 * We use this as a shares space where different tasks
 * and interrupts share their data. All taks schedule
 * their data to be sent to the RS232 port in this fifo
 * which is serviced by the main program loop.
 */
#ifndef FIFO_H_
#define FIFO_H_

struct entry_t {
	unsigned char key;
	unsigned char value;
};

void push(struct entry_t entry);
struct entry_t pop(void);
unsigned char pending(void);

#endif /*FIFO_H_*/
