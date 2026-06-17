#ifndef __GPIO_H__
#define __GPIO_H__

typedef enum
{
    GPIO_MODE_INPUT  = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_AF     = 2,
    GPIO_MODE_ANALOG = 3
} GPIO_Mode_t;


typedef enum{
    GPIO_OUTTYPE_PUSH_PULL = 0,
    GPIO_OUTTYPE_OPEND_RAIN = 1

}GPIO_OUTTYPE_t;

typedef enum{
    GPIO_LOW_SPEED = 0,
    GPIO_MEDIUM_SPEED = 1,
    GPIO_HIGH_SPEED = 2

}GPIO_OUTPUt_SPEED_t;

typedef struct 
{
    int Pin;
    GPIO_Mode_t Mode;
    GPIO_OUTTYPE_t OType;
    GPIO_OUTPUt_SPEED_t Speed;

}gpio_init_t;


typedef struct 
{
    volatile int MODER;
    volatile int OTYPER;
    volatile int OSPEEDR;
    volatile int PUPDR;
    volatile int IDR;
    volatile int ODR;
    volatile int BSRR;
    volatile int LCKR;
    volatile int AFR[2];
    volatile int BRR;
}gpio_regTypedef_t;


#define GPIOA_BASE     0x48000000UL
#define GPIOB_BASE     0x48000400UL
#define GPIOC_BASE     0x48000800UL
#define GPIOD_BASE     0x48000C00UL
#define GPIOF_BASE     0x48001400UL


#define GPIOA (gpio_regTypedef_t*)(GPIOA_BASE)
#define GPIOA (gpio_regTypedef_t*)(GPIOB_BASE)
#define GPIOA (gpio_regTypedef_t*)(GPIOC_BASE)
#define GPIOA (gpio_regTypedef_t*)(GPIOD_BASE)
#define GPIOA (gpio_regTypedef_t*)(GPIOF_BASE)


#define GPIO_PIN_0     (1U << 0)
#define GPIO_PIN_1     (1U << 1)
#define GPIO_PIN_2     (1U << 2)
#define GPIO_PIN_3     (1U << 3)
#define GPIO_PIN_4     (1U << 4)
#define GPIO_PIN_5     (1U << 5)
#define GPIO_PIN_6     (1U << 6)
#define GPIO_PIN_7     (1U << 7)
#define GPIO_PIN_8     (1U << 8)
#define GPIO_PIN_9     (1U << 9)
#define GPIO_PIN_10    (1U << 10)
#define GPIO_PIN_11    (1U << 11)
#define GPIO_PIN_12    (1U << 12)
#define GPIO_PIN_13    (1U << 13)
#define GPIO_PIN_14    (1U << 14)
#define GPIO_PIN_15    (1U << 15)



void gpio_init(gpio_regTypedef_t *GPIOX, gpio_regTypedef_t gpio_init_struct);
void gpio_WritePin(gpio_regTypedef_t *GPIOX, int pin, int state);
void gpio_toggle(gpio_regTypedef_t *GPIOX,int pin);
int gpio_ReadPin(gpio_regTypedef_t *GPIOX,int pin);

#endif