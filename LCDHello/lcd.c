#include "lcd.h"
#include "config.h"

#include <pic.h>

#define LCD_RS RC0
#define LCD_RW RC1
#define LCD_EN RC2

#define LCD_DATA PORTD

#define LCD_STROBE() ((LCD_EN = 1), (LCD_EN = 0))

void lcd_init(void) {
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	
	// Wait for power-up
	__delay_ms(15);
	// Set 8-bit mode / 2 Line display
	lcd_write(0x3C);
	__delay_ms(2);
	// Set display on / cursor on / blink
	lcd_write(0x07);
	// Clear screen
	lcd_clear();
	// Set entry mode
	lcd_write(0x02);
}

void lcd_clear(void) {
	LCD_RS = 0;
	lcd_write(0x01);
	__delay_ms(2);
}

void lcd_write(unsigned char c) {	
	__delay_us(40);
	LCD_DATA = c;
	LCD_STROBE();
}

void lcd_putc(char c) {
	LCD_RS = 1;
	lcd_write(c);
}

void lcd_puts(const char *s) {
	LCD_RS = 1;
	while (*s) {
		lcd_write(*s++);
	}
}

