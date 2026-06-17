#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdint.h>

/*==============================
                RCC
================================*/
#define RCC_BASE_ADDRESS 0x40021000

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_RegDef_t;

#define RCC ((RCC_RegDef_t *)RCC_BASE_ADDRESS)


/*=================================
                Flash
===================================*/
#define FLASH_BASE_ADDR 0x40022000UL

typedef struct
{
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t AR;
    volatile uint32_t RESERVED;
    volatile uint32_t OBR;
    volatile uint32_t WRPR;
} FLASH_RegDef_t;

#define FLASH ((FLASH_RegDef_t *)FLASH_BASE_ADDR)

/*=================================
                Function
===================================*/

void system_clock_enable(void);
void gpioa_clock_enable();
void gpiob_clock_enable();
void gpioc_clock_enable();
void gpiod_clock_enable();
void gpiof_clock_enable();

#endif /*__CLOCK_H__*/