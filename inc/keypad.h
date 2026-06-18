#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"
#include "system_stm32_init.h"
#include <stdint.h>

void keypad_init(void);
void keypad_setRow(void);
char keypad_scan(void);

#endif