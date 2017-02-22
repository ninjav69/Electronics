#include "fifo.h"

#define FIFO_SIZE 16
#define FIFO_MASK (FIFO_SIZE-1);

struct entry_t fifo[FIFO_SIZE];
unsigned char iidx = 0;
unsigned char oidx = 0;
unsigned char tidx = 0;

void push(struct entry_t entry) {
	fifo[iidx] = entry;
	tidx = (iidx + 1) & FIFO_MASK;
	if (tidx != oidx) {
		iidx = tidx;
	}
}

struct entry_t pop(void) {
	struct entry_t rv;
	rv = fifo[oidx];
	++oidx;
	oidx &= FIFO_MASK;
	return rv;
}

unsigned char pending(void)
{
	if (iidx > oidx) {
		return (iidx - oidx);
	} else {
		return (oidx - iidx);
	}
}
