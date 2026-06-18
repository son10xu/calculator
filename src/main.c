#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "system_stm32_init.h"
#include "keypad.h"

int main(void)
{
    system_stm32_init();

    gpioa_clock_enable();
    gpiob_clock_enable();
    gpioc_clock_enable();
    gpiod_clock_enable();
    gpiof_clock_enable();
    systick_init();
    keypad_init();

    LCD_init();
    LCD_clear();
    LCD_setCursor(0, 0);

    char temp;
    char str[2];
    LCD_puts("hello");
    while (1)
{
    temp = keypad_scan();

    if (temp != 'c')
    {
        LCD_sendChar(temp);
    }
}
}