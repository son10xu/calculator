#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "gpio.h"
#include "clock.h"
extern uint8_t col;
extern uint8_t row;

#ifdef __cplusplus
extern "C"
{
#endif


#define D4_Pin GPIO_PIN_5
#define D5_Pin GPIO_PIN_6
#define D6_Pin GPIO_PIN_7
#define D7_Pin GPIO_PIN_0
#define RS_Pin GPIO_PIN_3
#define EN_Pin GPIO_PIN_4

    gpio_init_t lcd = {
        .Pin = (D4_Pin | D5_Pin | D6_Pin | D7_Pin),
        .Mode = GPIO_MODE_OUTPUT,
        .OType = GPIO_OUTTYPE_PUSH_PULL,
        .Speed = GPIO_HIGH_SPEED
    };

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