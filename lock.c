#include "lock.h"

void locked_state_lcd_print() {
	LCD_command(CLEAR_CMD);
	LCD_write_string("LOCKED");
	LCD_write_char('\0');
	LCD_command(CURSOR_ROW1_COL0_CMD);
	LCD_write_string("Enter Pin:");
}

void unlocked_state_lcd_print() {
	LCD_command(CLEAR_CMD);
	LCD_write_string("UNLOCKED");
	LCD_write_char('\1');
	LCD_command(CURSOR_ROW1_COL0_CMD);
	LCD_write_string("PRESS KEY TO LOCK");
}

void change_key_state_lcd_print() {
	LCD_command(CLEAR_CMD);
	LCD_write_string("Change Pin");
	LCD_command(CURSOR_ROW1_COL0_CMD);
	LCD_write_string("New Pin:");
}


STATE locked_state(char *pin) {
    STATE returnState = LOCKED;
    static char curPin[PIN_LEN];
    static unsigned curPinIdx = 0;
    int32_t read_char;

    // take keypad input
    if ((read_char = keypad_detect_press()) != -1) {
    	if (read_char == '*') { // CLEAR
    	    locked_state_lcd_print();
    	    curPinIdx = 0;
    	} else {
    	    LCD_write_char(read_char);
        	curPin[curPinIdx++] = read_char;
        	HAL_Delay(500);
    	}
    }

    // when idx == sizeof(pin)
    if (curPinIdx == PIN_LEN) {
        // evaluate pin
    	LCD_write_char('#');
        if (!memcmp(curPin, pin, PIN_LEN)) {
            // correct pin
        	unlocked_state_lcd_print();
            returnState = UNLOCKED;
        } else { // wrong pin
        	locked_state_lcd_print();
        }
       	curPinIdx = 0;
        // we can use strncmp
    }

    GPIOA->ODR |= GPIO_PIN_5; // turn on LED

    return returnState;
}

STATE unlocked_state() {
    STATE returnState = UNLOCKED;
    GPIOA->ODR &= ~GPIO_PIN_5; // turn off LED
    //  option to har
    int32_t read_char;

        // take keypad input
    if ((read_char = keypad_detect_press()) != -1) {
    	if (read_char == 'D') {
    		change_key_state_lcd_print();
    		returnState = CHANGE_KEY;
    	} else {
    		locked_state_lcd_print();
    		returnState = LOCKED;
    	}
        HAL_Delay(500);
    }

    return returnState;
}

STATE change_key(char *pin) {
	STATE returnState = CHANGE_KEY;
	static unsigned curPinIdx = 0;
	static char curPin[PIN_LEN];
	int32_t read_char;

	if ((read_char = keypad_detect_press()) != -1) {
		if (read_char == '*') { // CLEAR
			change_key_state_lcd_print();
			curPinIdx = 0;
		} else {
			LCD_write_char(read_char);
			curPin[curPinIdx++] = read_char;
			HAL_Delay(500);
		}
	}

	if (curPinIdx == PIN_LEN) {
		memcpy(pin, curPin, PIN_LEN);
		curPinIdx = 0;
		unlocked_state_lcd_print();
		returnState = UNLOCKED;
	}


	return returnState;
}
