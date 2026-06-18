#include "lcd.h"
#include "system_stm32_init.h"

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
    gpio_WritePin(GPIOA, D4_Pin, (data & 0x01) ? 1 : 0);
    gpio_WritePin(GPIOA, D5_Pin, (data & 0x02) ? 1 : 0);
    gpio_WritePin(GPIOA, D6_Pin, (data & 0x04) ? 1 : 0);
    gpio_WritePin(GPIOB, D7_Pin, (data & 0x08) ? 1 : 0);

    gpio_WritePin(GPIOA, EN_Pin, 1);
    delay_ms(1);
    gpio_WritePin(GPIOA, EN_Pin, 0);
    delay_ms(1);
}
static void LCD_sendByte(uint8_t data)
{
    LCD_sendNibble(data>>4);
    LCD_sendNibble(data);
}
static void LCD_sendCmd(uint8_t cmd)
{
    gpio_WritePin(GPIOA, RS_Pin, 0); // RS = 0: gửi lệnh
    LCD_sendByte(cmd);
}


void LCD_init()
{
    gpio_init_t lcd_a = {
        .Pin = (D4_Pin | D5_Pin | D6_Pin | RS_Pin | EN_Pin),
        .Mode = GPIO_MODE_OUTPUT,
        .OType = GPIO_OUTTYPE_PUSH_PULL,
        .Speed = GPIO_HIGH_SPEED
    };
    gpio_init_t lcd_b = {
        .Pin = D7_Pin,
        .Mode = GPIO_MODE_OUTPUT,
        .OType = GPIO_OUTTYPE_PUSH_PULL,
        .Speed = GPIO_HIGH_SPEED
    };
    gpio_init(GPIOA, &lcd_a);
    gpio_init(GPIOB, &lcd_b);
    gpio_WritePin(GPIOA, RS_Pin, 0);

    delay_ms(1);
    LCD_sendNibble(0x03);
    delay_ms(1);
    LCD_sendNibble(0x03);
    delay_ms(1);
    LCD_sendNibble(0x03);
    delay_ms(1);
    LCD_sendNibble(0x02);

    LCD_sendCmd(0x28); // 4-bit, 2 dòng, font 5x8
    delay_ms(1);
    LCD_sendCmd(0x06); // tự tăng con trỏ
    LCD_sendCmd(0x0C); // bật LCD, tắt con trỏ
    LCD_sendCmd(0x01); // xóa màn hình
    delay_ms(1);

}

void LCD_setCursor(char row, char col)
{
    uint8_t address;

    if (row == 0)
    {
        address = 0x00 + col;
    }
    else
    {
        address = 0x40 + col;
    }

    LCD_sendCmd(0x80 | address);
}

void LCD_sendChar(uint8_t data)
{
    gpio_WritePin(GPIOA, RS_Pin, 1); // RS = 1: gửi dữ liệu
    LCD_sendByte(data);
}
void LCD_clear(void)
{
    LCD_sendCmd(0x01);
    delay_ms(5);
}
void LCD_puts(char *data)
{
    while (*data != '\0')
    {
        LCD_sendChar(*data);
        data++;
    }
}