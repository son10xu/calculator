#include "gpio.h"



void gpio_init(gpio_regTypedef_t *GPIOX, gpio_regTypedef_t *cfg)
{
    
    for(int pin = 0; pin < 16;pin++)
    {

    }
}
void gpio_WritePin(gpio_regTypedef_t *GPIOX, int pin, int state);
void gpio_toggle(gpio_regTypedef_t *GPIOX,int pin);
int gpio_ReadPin(gpio_regTypedef_t *GPIOX,int pin);

