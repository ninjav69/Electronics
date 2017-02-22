#ifndef UART_H_
#define UART_H_

void uart_putc(unsigned char byte);
unsigned char uart_getc(void);

void uart_interrupt(void);

#endif /*UART_H_*/
