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

#include "stm32f3xx_hal.h"

void HAL_MspInit()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init = {};
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    gpio_init.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                    GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(GPIOE, &gpio_init);
}

void HAL_MspDeInit()
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOE_CLK_DISABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART2)
    {
        GPIO_InitTypeDef gpio_init = {};
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Pull = GPIO_PULLUP;
        gpio_init.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init.Alternate = GPIO_AF7_USART2;

        HAL_GPIO_Init(GPIOA, &gpio_init);

        __HAL_RCC_USART2_CLK_ENABLE();
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
    }
}

void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
{
    if (hpcd->Instance == USB)
    {
        GPIO_InitTypeDef gpio_init;

        gpio_init.Pin = GPIO_PIN_11 | GPIO_PIN_12;
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Pull = GPIO_NOPULL;
        gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init.Alternate = GPIO_AF14_USB;
        HAL_GPIO_Init(GPIOA, &gpio_init);

        __HAL_RCC_USB_CLK_ENABLE();
        __HAL_RCC_SYSCFG_CLK_ENABLE();

        HAL_NVIC_SetPriority(USB_LP_CAN_RX0_IRQn, 0x0F, 0);
        HAL_NVIC_EnableIRQ(USB_LP_CAN_RX0_IRQn);
    }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef* hpcd)
{
    if (hpcd->Instance == USB)
    {
        __HAL_RCC_USB_CLK_DISABLE();
        __HAL_RCC_SYSCFG_CLK_DISABLE();
    }
}
