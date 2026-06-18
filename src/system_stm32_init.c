#include "system_stm32_init.h"
#include "clock.h"

/* SysTick CTRL bits */
#define SYSTICK_CTRL_ENABLE     (1U << 0)
#define SYSTICK_CTRL_TICKINT    (1U << 1)
#define SYSTICK_CTRL_CLKSOURCE  (1U << 2)
static volatile uint32_t g_ms_ticks = 0;

/* ================= SYSTEM INIT ================= */
void system_stm32_init(void){
    system_clock_enable();
    systick_init();
}

/* ================= SYSTICK / DELAY ================= */

void systick_init(void)
{
    g_ms_ticks = 0;

    SysTick->CSR = 0;

    /*
       SysTick chạy bằng SYSCLK = 48MHz.
       Muốn ngắt mỗi 1ms:
       LOAD = 48MHz / 1000 - 1 = 48000 - 1
    */
    SysTick->RVR = (SYSCLK_FREQ_HZ / 1000U) - 1U;
    SysTick->CVR = 0;

    SysTick->CSR = SYSTICK_CTRL_CLKSOURCE |
                    SYSTICK_CTRL_TICKINT |
                    SYSTICK_CTRL_ENABLE;
}

void SysTick_Handler(void)
{
    g_ms_ticks++;
}

uint32_t millis(void)
{
    return g_ms_ticks;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = millis();
    while ((millis() - start) < ms) {
    }
}