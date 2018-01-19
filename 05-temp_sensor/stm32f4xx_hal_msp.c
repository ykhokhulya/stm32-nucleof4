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

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_conf.h>

#include "lcd/Lcd.h"
#include "temp/Temp.h"

void HAL_MspInit()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init = {};
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    gpio_init.Pin = GPIO_PIN_5;
    gpio_init.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &gpio_init);
}

void HAL_MspDeInit()
{
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5);

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    __HAL_RCC_GPIOC_CLK_DISABLE();
    __HAL_RCC_GPIOH_CLK_DISABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();

        GPIO_InitTypeDef gpio_init = {};
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Pull = GPIO_PULLUP;
        gpio_init.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        gpio_init.Speed = GPIO_SPEED_FAST;
        gpio_init.Alternate = GPIO_AF7_USART2;

        HAL_GPIO_Init(GPIOA, &gpio_init);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

        __HAL_RCC_USART2_CLK_DISABLE();
    }
}

void LCD_MspInit(LCD_HandleTypeDef* lcd)
{
    if (lcd->instance == LCD0)
    {
        GPIO_InitTypeDef gpio_init = {};
        gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
        gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init.Pull = GPIO_PULLDOWN;

        gpio_init.Pin = GPIO_PIN_0;
        HAL_GPIO_Init(GPIOB, &gpio_init);

        gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        HAL_GPIO_Init(GPIOH, &gpio_init);

        gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
        HAL_GPIO_Init(GPIOC, &gpio_init);

        lcd->io.en.port = GPIOB;
        lcd->io.rs.port = GPIOH;
        lcd->io.d4.port = GPIOC;
        lcd->io.d5.port = GPIOC;
        lcd->io.d6.port = GPIOC;
        lcd->io.d7.port = GPIOC;

        lcd->io.en.pin = GPIO_PIN_0;
        lcd->io.rs.pin = GPIO_PIN_1;
        lcd->io.d4.pin = GPIO_PIN_0;
        lcd->io.d5.pin = GPIO_PIN_1;
        lcd->io.d6.pin = GPIO_PIN_2;
        lcd->io.d7.pin = GPIO_PIN_3;
    }
}

void LCD_MspDeInit(LCD_HandleTypeDef* lcd)
{
    if (lcd->instance == LCD0)
    {
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_0 | GPIO_PIN_1);
        HAL_GPIO_DeInit(
            GPIOC, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    }
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    if (hrtc->Instance == RTC)
    {
        RCC_OscInitTypeDef osc_init = {};
        osc_init.OscillatorType = RCC_OSCILLATORTYPE_LSE;
        osc_init.PLL.PLLState = RCC_PLL_NONE;
        osc_init.LSEState = RCC_LSE_ON;

        if (HAL_RCC_OscConfig(&osc_init) != HAL_OK)
        {
            while (1) __NOP();
        }

        RCC_PeriphCLKInitTypeDef clk_init = {};
        clk_init.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        clk_init.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;

        if (HAL_RCCEx_PeriphCLKConfig(&clk_init) != HAL_OK)
        {
            while (1) __NOP();
        }

        HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);

        __HAL_RCC_RTC_ENABLE();
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
    if (hrtc->Instance == RTC)
    {
        __HAL_RCC_RTC_DISABLE();
        __HAL_RCC_PWR_CLK_DISABLE();
    }
}

void TEMP_MspInit(TEMP_HandleTypeDef* temp)
{
    if (temp->instance == TEMP0)
    {
        GPIO_InitTypeDef gpio_init = {};
        gpio_init.Mode = GPIO_MODE_OUTPUT_OD;
        gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init.Pin = GPIO_PIN_4;
        gpio_init.Pull = GPIO_NOPULL;

        HAL_GPIO_Init(GPIOA, &gpio_init);

        temp->io.data.port = GPIOA;
        temp->io.data.pin = GPIO_PIN_4;
    }
}

void TEMP_MspDeInit(TEMP_HandleTypeDef* temp)
{
    if (temp->instance == TEMP0)
    {
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);
    }
}
