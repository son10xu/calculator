#include "clock.h"
#include "gpio.h"
#include "lcd.h"
#include "system_stm32_init.h"

int main(void)
{
    system_stm32_init();

    gpioa_clock_enable();
    gpiob_clock_enable();

    systick_init();

    LCD_init();
    LCD_clear();
    LCD_setCursor(0, 0);
    LCD_puts("Hello, World!");

    while (1)
    {
    }
}