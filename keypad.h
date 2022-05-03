#ifndef KEYPAD_H
#define KEYPAD_H

#include "main.h"

#define COL0_GPIO_MASK 0x10
#define KEYPAD_GRID_DIM 4
#define ROWS_GPIO_MASK 0x0F
#define COLS_GPIO_MASK 0xF0
#define COLS_OUTPUT_MODE 0x05500
#define ROWS_PULLDOWN 0x00AA

void keypad_init();
int32_t keypad_detect_press();
char count_till_one(int32_t num);


#endif
