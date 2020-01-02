/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2017 Yuriy Khokhulya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

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

    // enable GPIOA & GPIOC periph clock
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);

    // configure GPIOA5 in GP output mode (PP, low speed)
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE5_0);

    // configure GPIOC13 in GP input mode (low speed, pull-up)
    SET_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPD13);

    while (1)
    {
        if (!READ_BIT(GPIOC->IDR, GPIO_IDR_ID13))
        {
            delay(500);
        }

        delay(500);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
        delay(500);
        SET_BIT(GPIOA->BSRR, GPIO_BRR_BR5);
    }
}
