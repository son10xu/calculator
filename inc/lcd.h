#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "gpio.h"

extern uint8_t col;
extern uint8_t row;

#ifdef __cplusplus
extern "C"
{
#endif
void LCD_clear();
void LCD_setCursor(char row, char col);
void LCD_puts(char *data);
void LCD_scroll(char isScroll);
void LCD_init();
void LCD_sendChar(uint8_t data);
#ifdef __cplusplus

}
#endif

#endif