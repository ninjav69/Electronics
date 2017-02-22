#ifndef LCD_H_
#define LCD_H_


/*
 * Initialize the LCD display. We use 8-bit mode, 2 lines
 * using 5x8 font. We use a blinking cursor.
 */

void lcd_init(void);

/*
 * Clears the entire display.
 */

void lcd_clear(void);

/*
 * Write a byte to the lcd.
 */

void lcd_write(unsigned char c);


/*
 * Put a character on the lcd.
 */

void lcd_putc(char c);

/*
 * Put a string on the lcd.
 */

void lcd_puts(const char *str);

#endif /*LCD_H_*/
