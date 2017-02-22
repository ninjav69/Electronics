/*
 * We use this as a shares space where different tasks
 * and interrupts share their data. All taks schedule
 * their data to be sent to the RS232 port in this fifo
 * which is serviced by the main program loop.
 */
#ifndef FIFO_H_
#define FIFO_H_

struct packet_t {
	unsigned char src_id;
	unsigned char dst_id;
	unsigned char data;
};

void in_push(struct packet_t entry);
struct packet_t in_pop(void);
unsigned char in_pending(void);

void out_push(struct packet_t packet);
struct packet_t out_pop(void);
unsigned char out_pending(void);

#endif /*FIFO_H_*/
