#include "fifo.h"

#define FIFO_SIZE 16
#define FIFO_MASK (FIFO_SIZE-1);

struct packet_t in_fifo[FIFO_SIZE];
unsigned char in_iidx = 0;
unsigned char in_oidx = 0;
unsigned char in_tidx = 0;

struct packet_t out_fifo[FIFO_SIZE];
unsigned char out_iidx = 0;
unsigned char out_oidx = 0;
unsigned char out_tidx = 0;

void in_push(struct packet_t entry) {
	in_fifo[in_iidx] = entry;
	in_tidx = (in_iidx + 1) & FIFO_MASK;
	if (in_tidx != in_oidx) {
		in_iidx = in_tidx;
	}
}

struct packet_t in_pop(void) {
	struct packet_t rv;
	rv = in_fifo[in_oidx];
	++in_oidx;
	in_oidx &= FIFO_MASK;
	return rv;
}

unsigned char in_pending(void)
{
	if (in_iidx > in_oidx) {
		return (in_iidx - in_oidx);
	} else {
		return (in_oidx - in_iidx);
	}
}

void out_push(struct packet_t entry) {
	out_fifo[out_iidx] = entry;
	out_tidx = (out_iidx + 1) & FIFO_MASK;
	if (out_tidx != out_oidx) {
		out_iidx = out_tidx;
	}
}

struct packet_t out_pop(void) {
	struct packet_t rv;
	rv = out_fifo[out_oidx];
	++out_oidx;
	out_oidx &= FIFO_MASK;
	return rv;
}

unsigned char out_pending(void)
{
	if (out_iidx > out_oidx) {
		return (out_iidx - out_oidx);
	} else {
		return (out_oidx - out_iidx);
	}
}
