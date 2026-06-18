#include "keypad.h"
#include "clock.h"

char keypad[4][5] = {
	{ '1', '5', '9', 'x', ')' },
	{ '2', '6', '0', ':', 'C' },
	{ '3', '7', '+', '=', 'B' },
	{ '4', '8', '-', '(', '.' }
};

static gpio_regTypedef_t *colPort[5] = { GPIOB, GPIOB, GPIOB, GPIOB, GPIOB };
static uint16_t colPin[5] = {
	GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4, GPIO_PIN_3
};

static gpio_regTypedef_t *rowPort[4] = { GPIOA, GPIOA, GPIOA, GPIOA };
static uint16_t rowPin[4] = {
	GPIO_PIN_15, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2
};

#define ROW_PINS (GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2)
#define COL_PINS (GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3)

gpio_init_t rowConfig = {
    .Pin = ROW_PINS,
    .Mode = GPIO_MODE_OUTPUT,
    .OType = GPIO_OUTTYPE_OPEN_DRAIN,
    .Speed = GPIO_HIGH_SPEED,
    .Pull = GPIO_NO_PULL
};
gpio_init_t colConfig = {
    .Pin = COL_PINS,
    .Mode = GPIO_MODE_INPUT,
    .OType = GPIO_OUTTYPE_PUSH_PULL,
    .Speed = GPIO_HIGH_SPEED,
    .Pull = GPIO_PULL_UP
};

void keypad_init(void)
{
	gpio_init(GPIOA, &rowConfig);
	gpio_init(GPIOB, &colConfig);

	keypad_setRow();
}

void keypad_setRow(void)
{
	for(int i = 0; i < 4; i++)
	{
		gpio_WritePin(rowPort[i], rowPin[i], 1);
	}
}
char keypad_scan(void)
{
    for(int i = 0; i < 4; i++)
    {
        keypad_setRow();  // tất cả row = 1

        // chọn row hiện tại bằng cách kéo xuống 0
        gpio_WritePin(rowPort[i], rowPin[i], 0);

        for(int j = 0; j < 5; j++)
        {
            if(gpio_ReadPin(colPort[j], colPin[j]) == 0)
            {
                delay_ms(20);

                if(gpio_ReadPin(colPort[j], colPin[j]) == 0)
                {
                    while(gpio_ReadPin(colPort[j], colPin[j]) == 0)
                    {
                        delay_ms(10);
                    }

                    return keypad[i][j];
                }
            }
        }
    }

    return 'c';
}