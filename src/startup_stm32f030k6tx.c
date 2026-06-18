#include <stdint.h>

/* Linker symbols */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);

/* Main function prototype */
extern int main(void);

/* Cortex-M0 Processor Exceptions */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* STM32F030 Specific Interrupts */
void WWDG_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)                 __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_5_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void ADC1_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM15_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM16_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void TIM17_IRQHandler(void)               __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)                __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)              __attribute__((weak, alias("Default_Handler")));

/* Vector Table */
__attribute__((section(".isr_vector"), used))
const uint32_t vector_table[] = {
    (uint32_t)&_estack,             /* 0x00 Initial Stack Pointer */
    (uint32_t)Reset_Handler,        /* 0x04 Reset Handler */
    (uint32_t)NMI_Handler,          /* 0x08 NMI Handler */
    (uint32_t)HardFault_Handler,    /* 0x0C Hard Fault Handler */
    0, 0, 0, 0, 0, 0, 0,            /* 0x10-0x28 Reserved */
    (uint32_t)SVC_Handler,          /* 0x2C SVC Handler */
    0, 0,                           /* 0x30-0x34 Reserved */
    (uint32_t)PendSV_Handler,       /* 0x38 PendSV Handler */
    (uint32_t)SysTick_Handler,      /* 0x3C SysTick Handler */
    
    /* External Interrupts */
    (uint32_t)WWDG_IRQHandler,                /* 0x40 WWDG */
    0,                                        /* 0x44 Reserved */
    (uint32_t)RTC_IRQHandler,                 /* 0x48 RTC */
    (uint32_t)FLASH_IRQHandler,               /* 0x4C FLASH */
    (uint32_t)RCC_IRQHandler,                 /* 0x50 RCC */
    (uint32_t)EXTI0_1_IRQHandler,             /* 0x54 EXTI0_1 */
    (uint32_t)EXTI2_3_IRQHandler,             /* 0x58 EXTI2_3 */
    (uint32_t)EXTI4_15_IRQHandler,            /* 0x5C EXTI4_15 */
    0,                                        /* 0x60 Reserved */
    (uint32_t)DMA1_Channel1_IRQHandler,       /* 0x64 DMA1 CH1 */
    (uint32_t)DMA1_Channel2_3_IRQHandler,     /* 0x68 DMA1 CH2_3 */
    (uint32_t)DMA1_Channel4_5_IRQHandler,     /* 0x6C DMA1 CH4_5 */
    (uint32_t)ADC1_IRQHandler,                /* 0x70 ADC1 */
    (uint32_t)TIM1_BRK_UP_TRG_COM_IRQHandler, /* 0x74 TIM1 BRK_UP_TRG_COM */
    (uint32_t)TIM1_CC_IRQHandler,             /* 0x78 TIM1 CC */
    0,                                        /* 0x7C Reserved */
    (uint32_t)TIM3_IRQHandler,                /* 0x80 TIM3 */
    0, 0,                                     /* 0x84-0x88 Reserved */
    (uint32_t)TIM14_IRQHandler,               /* 0x8C TIM14 */
    (uint32_t)TIM15_IRQHandler,               /* 0x90 TIM15 */
    (uint32_t)TIM16_IRQHandler,               /* 0x94 TIM16 */
    (uint32_t)TIM17_IRQHandler,               /* 0x98 TIM17 */
    (uint32_t)I2C1_IRQHandler,                /* 0x9C I2C1 */
    (uint32_t)I2C2_IRQHandler,                /* 0xA0 I2C2 */
    (uint32_t)SPI1_IRQHandler,                /* 0xA4 SPI1 */
    (uint32_t)SPI2_IRQHandler,                /* 0xA8 SPI2 */
    (uint32_t)USART1_IRQHandler,              /* 0xAC USART1 */
    (uint32_t)USART2_IRQHandler,              /* 0xB0 USART2 */
};

void Reset_Handler(void) {
    /* Copy data section from FLASH to RAM */
    uint32_t *pSrc = &_sidata;
    uint32_t *pDst = &_sdata;
    while (pDst < &_edata) {
        *pDst++ = *pSrc++;
    }

    /* Initialize BSS section to zero */
    pDst = &_sbss;
    while (pDst < &_ebss) {
        *pDst++ = 0;
    }

    /* Call main application */
    main();

    /* Trap if main returns */
    while (1);
}

void Default_Handler(void) {
    while (1);
}
