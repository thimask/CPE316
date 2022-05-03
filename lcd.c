#include "lcd.h"

uint8_t locked_char[] = {
    0x0E,
    0x11,
    0x11,
    0x11,
    0x1F,
    0x1F,
    0x1F,
    0x1F};

uint8_t unlocked_char[] = {
    0x0E,
    0x10,
    0x10,
    0x10,
    0x1F,
    0x1F,
    0x1F,
    0x1F};

void LCD_init() {
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOCEN);
    GPIOC->MODER = PC0_10_OUT;
    LCD_command(WAKE_UP);
    HAL_Delay(100);
    LCD_command(WAKE_UP);
    HAL_Delay(10);
    LCD_command(WAKE_UP);
    HAL_Delay(10);
    LCD_command(FUNCTION_SET);
    LCD_command(NO_SHIFT_DISPLAY);
    LCD_command(DISPLAY_ON);
    LCD_command(ENTRY_MODE_SET);
    LCD_create_char('\0', locked_char);
    LCD_create_char('\1', unlocked_char);
}

void LCD_command(uint8_t command) {
    GPIOC->ODR = command;
    HAL_Delay(1);
    GPIOC->ODR |= 1 << 10;
    HAL_Delay(1);
    GPIOC->ODR &= ~(1 << 10);
}

void LCD_write_char(uint8_t letter) {
    GPIOC->ODR = letter | 1 << 9;
    HAL_Delay(1);
    GPIOC->ODR |= 1 << 10;
    HAL_Delay(1);
    GPIOC->ODR &= ~(1 << 10);
}

void LCD_write_string(char *str) {
    if (str) {
        while (*str) {
            LCD_write_char(*str++);
        }
    }
}

void LCD_create_char(uint8_t location, uint8_t *charmap) {
    location &= 0x7; // There are only 8 cgram locations
    LCD_command(0x40 | location << 3);
    for (int i = 0; i < 8; i++) {
        LCD_write_char(charmap[i]);
    }
}
