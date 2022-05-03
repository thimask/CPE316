#ifndef LCD_H
#define LCD_H

#include "main.h"

#define PC0_10_OUT 0xFF155555
#define WAKE_UP 0x30
#define FUNCTION_SET 0x38
#define NO_SHIFT_DISPLAY 0x10
#define DISPLAY_ON 0x0C
#define ENTRY_MODE_SET 0x06
#define CLEAR_CMD 0x01
#define CURSOR_ROW1_COL0_CMD 0xC0

void LCD_command(uint8_t command);
void LCD_write_char(uint8_t letter);
void LCD_write_string(char *str);
void LCD_create_char(uint8_t location, uint8_t *charmap);
void LCD_init();


#endif
