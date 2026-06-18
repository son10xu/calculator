#include "lcd.h"

#define GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_5
#define D5_Pin GPIO_PIN_6
#define D6_Pin GPIO_PIN_7
#define D7_Pin GPIO_PIN_0
#define RS_Pin GPIO_PIN_3
#define EN_Pin GPIO_PIN_4
static void LCD_sendNibble(uint8_t data);
static void LCD_sendByte(uint8_t data);
static void LCD_sendCmd(uint8_t cmd);
static void LCD_sendNibble(uint8_t data)
{
    gpio_WritePin(GPIOA, D4_Pin, data & 0x01);
    gpio_WritePin(GPIOA, D5_Pin, data & 0x02);
    gpio_WritePin(GPIOA, D6_Pin, data & 0x04);
    gpio_WritePin(GPIOB, D7_Pin, data & 0x08);
    gpio_WritePin(GPIOA, EN_Pin, 1);

    gpio_WritePin(GPIOA, EN_Pin, 0);

}
static void LCD_sendByte()
{

}
void LCD_init()
{
}

void LCD_setCursor(char row, char col)
{
}

void LCD_clear();
void LCD_setCursor(char row, char col);
void LCD_puts(char *data);
void LCD_scroll(char isScroll);
void LCD_init();
void LCD_sendChar(uint8_t data);
