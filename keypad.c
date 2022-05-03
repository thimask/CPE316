#include "keypad.h"

static const char letters[4][4] = {{'1', '2', '3', 'A'},
								   {'4', '5', '6', 'B'},
								   {'7', '8', '9', 'C'},
								   {'*', '0', '#', 'D'}};

void keypad_init() {
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN);
	// set columns to output and rows to output
	// rows PB0->3 and cols PB4->PB7
	GPIOB->MODER = COLS_OUTPUT_MODE; // set columns as output

	// enable pull down resistors for rows
	GPIOB->PUPDR = ROWS_PULLDOWN;
}

int32_t keypad_detect_press() {
	GPIOB->ODR = COLS_GPIO_MASK;
	unsigned char col;
	int32_t rows_in = GPIOB->IDR & ROWS_GPIO_MASK;
	unsigned char row;
	// set all columns to high

//	 check if any of the inputs are high
	if (rows_in == 0) {
		return -1;
	}
	row = count_till_one(rows_in);

	int col_mask = COL0_GPIO_MASK;
	for (col = 0; col < KEYPAD_GRID_DIM; col++) {
		GPIOB->ODR = col_mask;
		if (GPIOB->IDR & ROWS_GPIO_MASK) {
			break;
		}
		col_mask <<= 1;
	}

	return (int32_t)letters[row][col];
}

char count_till_one(int32_t num) {
	char count = 0;
	while (!(num & 0x1)) {
		count++;
		num >>= 1;
	}
	return count;
}


