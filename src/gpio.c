#include "gpio.h"


void gpio_init(gpio_regTypedef_t *GPIOX, gpio_init_t *cfg);
void gpio_WritePin(gpio_regTypedef_t *GPIOX, uint16_t pin, uint8_t state);
void gpio_toggle(gpio_regTypedef_t *GPIOX, uint16_t pin);
uint8_t gpio_ReadPin(gpio_regTypedef_t *GPIOX, uint16_t pin);
void gpio_init(gpio_regTypedef_t *GPIOX, gpio_init_t *cfg)
{
    for (uint8_t pin = 0; pin < 16; pin++)
    {
        if (cfg->Pin & (1U << pin))
        {
            GPIOX->MODER &= ~(0x3U << (pin * 2U));
            GPIOX->MODER |=  ((uint32_t)cfg->Mode << (pin * 2U));

            GPIOX->OTYPER &= ~(1U << pin);
            GPIOX->OTYPER |=  ((uint32_t)cfg->OType << pin);

            GPIOX->OSPEEDR &= ~(0x3U << (pin * 2U));
            GPIOX->OSPEEDR |=  ((uint32_t)cfg->Speed << (pin * 2U));

            GPIOX->PUPDR &= ~(0x3U << (pin * 2U));
            GPIOX->PUPDR |=  ((uint32_t)cfg->Pull << (pin * 2U));
        }
    }
}
void gpio_WritePin(gpio_regTypedef_t *GPIOX, uint16_t pin, uint8_t state)
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
void gpio_toggle(gpio_regTypedef_t *GPIOX, uint16_t pin)
{
    GPIOX->ODR ^= pin;
}
uint8_t gpio_ReadPin(gpio_regTypedef_t *GPIOX, uint16_t pin)
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
