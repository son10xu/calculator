#include "gpio.h"



void gpio_init(gpio_regTypedef_t *GPIOX, gpio_init_t *cfg)
{
    
    for(int pin = 0; pin < 16;pin++)
    {
        if(cfg->Pin &(1<<pin))
        {
                        /* Cấu hình mode: MODER dùng 2 bit cho mỗi pin */
            GPIOX->MODER &= ~(3U << (pin * 2));
            GPIOX->MODER |=  ((uint32_t)cfg->Mode << (pin * 2));

            /* Cấu hình output type: OTYPER dùng 1 bit cho mỗi pin */
            GPIOX->OTYPER &= ~(1U << pin);
            GPIOX->OTYPER |=  ((uint32_t)cfg->OType << pin);

            /* Cấu hình speed: OSPEEDR dùng 2 bit cho mỗi pin */
            GPIOX->OSPEEDR &= ~(3U << (pin * 2));
            GPIOX->OSPEEDR |=  ((uint32_t)cfg->Speed << (pin * 2));
        }
    }
}
void gpio_WritePin(gpio_regTypedef_t *GPIOX, int pin, int state)
{
    if(state == 1)
    {
        GPIOX->BSRR = pin;   // set pin lên 1
    }
    else
    {
        GPIOX->BRR = pin;    // reset pin về 0
    }
}
void gpio_toggle(gpio_regTypedef_t *GPIOX, int pin)
{
    GPIOX->ODR ^= pin;
}
int gpio_ReadPin(gpio_regTypedef_t *GPIOX, int pin)
{
    if(GPIOX->IDR & pin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
