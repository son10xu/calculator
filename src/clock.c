#include "clock.h"


void system_clock_enable(void){
    RCC->CR &= ~(0xFU<<0);
    RCC->CR |= (0x1U<<0);
    while(!(RCC->CR & (1U<<1)));

    /*Configure Flash latency */
    FLASH->ACR |= (1U << 4);        // PRFTBE: Prefetch buffer enable

    FLASH->ACR &= ~(0x7U << 0);     // clear LATENCY
    FLASH->ACR |=  (0x2U << 0);     // 2 wait states for 48MHz

    /*
     * Configure prescalers
     *
     * HPRE  bits [7:4]   = 0000: AHB = SYSCLK / 1
     * PPRE1 bits [10:8]  = 100 : APB1 = HCLK / 2
     * PPRE2 bits [13:11] = 000 : APB2 = HCLK / 1
     */

    RCC->CFGR &= ~(0xFU << 4);      // HPRE clear
    RCC->CFGR |=  (0x0U << 4);      // AHB = SYSCLK / 1

    RCC->CFGR &= ~(0x7U << 8);      // PPRE1 clear
    RCC->CFGR |=  (0x4U << 8);      // APB1 = HCLK / 2

    RCC->CFGR &= ~(0x7U << 11);     // PPRE2 clear
    RCC->CFGR |=  (0x0U << 11);     // APB2 = HCLK / 1

    /*
     * Configure PLL
     *
     * PLLSRC bit 15 = 1: HSI selected as PLL input
     * PLLMUL bits [21:18] = 0100: PLL input clock x6
     */

    RCC->CFGR &= ~(1U << 15);       // clear PLLSRC
    RCC->CFGR |=  (1U << 15);       // PLL source = HSI

    RCC->CFGR &= ~(0xFU << 18);     // clear PLLMUL
    RCC->CFGR |=  (0x4U << 18);     // PLL x6
}

void gpioa_clock_enable(){
    RCC->AHBENR &= ~(0x1U<<17);
    RCC->AHBENR |= (0x1U<<17);
}

void gpiob_clock_enable(){
    RCC->AHBENR &= ~(0x1U<<18);
    RCC->AHBENR |= (0x1U<<18);
}

void gpioc_clock_enable(){
    RCC->AHBENR &= ~(0x1U<<19);
    RCC->AHBENR |= (0x1U<<19);
}

void gpiod_clock_enable(){
    RCC->AHBENR &= ~(0x1U<<20);
    RCC->AHBENR |= (0x1U<<20);
}

void gpiof_clock_enable(){
    RCC->AHBENR &= ~(0x1U<<22);
    RCC->AHBENR |= (0x1U<<22);
}