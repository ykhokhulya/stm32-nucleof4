#include <stm32f4xx.h>

__IO uint32_t g_tick;

void SysTick_Handler()
{
    g_tick++;
}

void delay(uint32_t ticks)
{
    uint32_t start = g_tick;
    if (start == 0xffffffff) start++;
    while (g_tick - start < ticks) __NOP();
}

int main()
{
    SystemInit();
    SysTick_Config(SystemCoreClock / 1000U);

    // enable GPIOA periph clock
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);

    // configure GPIOA5 in GP output mode (PP, low speed)
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE5_0);

    while (1)
    {
        delay(500);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
        delay(500);
        SET_BIT(GPIOA->BSRR, GPIO_BRR_BR5);
    }
}
