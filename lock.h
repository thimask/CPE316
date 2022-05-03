#ifndef LOCK_H
#define LOCK_H

#include "keypad.h"
#include "lcd.h"
#include <string.h>

#define PIN_LEN 4
typedef enum State STATE;

enum State {
    LOCKED,
    UNLOCKED,
    CHANGE_KEY
};

STATE locked_state(char *pin);
STATE unlocked_state();
STATE change_key(char *pin);

#endif
