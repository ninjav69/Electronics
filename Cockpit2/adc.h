#ifndef ADC_H_
#define ADC_H_

/*
 * Advance to the next channel.
 */

void adc_advance(void);

/*
 * This function initiates a read of the current channel,
 * and advances the channel for the next read. The value
 * is reported via interrupt.
 */

void adc_read(void);


/*
 * This function handles ADC interrupts. It reads
 * the value from the result register and schedules
 * a packet in the fifo which must be processed by
 * the main loop.
 */

void adc_interrupt(void);

#endif /*ADC_H_*/
