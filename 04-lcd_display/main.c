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

#include <stdlib.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_pwr.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_uart.h>

#include "lcd/Lcd.h"
#include "lcd/drivers/HD44780/HD44780.h"

UART_HandleTypeDef g_uart_handle;
LCD_HandleTypeDef g_lcd_handle;

static void initSystemClock();
static void initUart();
static void initLcd();

static void handleError();

int main()
{
    HAL_Init();

    initSystemClock();
    initUart();
    initLcd();

    printf("System Clock Frequency = %lu Hz\n", SystemCoreClock);
    printf("Device identifier = %lu\n", HAL_GetDEVID());

    LCD_cursor(&g_lcd_handle, 1, 0);
    LCD_prints(&g_lcd_handle, "Hello!");

    while (1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
        HAL_Delay(800);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
        HAL_Delay(200);
    }
}

void initSystemClock()
{
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitTypeDef rcc_osc_init = {};
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    rcc_osc_init.HSIState = RCC_HSI_ON;
    rcc_osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;
    rcc_osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    rcc_osc_init.PLL.PLLM = 16;
    rcc_osc_init.PLL.PLLN = 200;
    rcc_osc_init.PLL.PLLP = RCC_PLLP_DIV2;
    rcc_osc_init.PLL.PLLQ = 7;
    rcc_osc_init.PLL.PLLR = 2;

    if (HAL_RCC_OscConfig(&rcc_osc_init) != HAL_OK)
    {
        handleError();
    }

    RCC_ClkInitTypeDef rcc_clk_init = {};
    rcc_clk_init.ClockType =
        (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
         RCC_CLOCKTYPE_PCLK2);
    rcc_clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5) != HAL_OK)
    {
        handleError();
    }
}

void initUart()
{
    g_uart_handle.Instance = USART2;
    g_uart_handle.Init.BaudRate = 115200;
    g_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    g_uart_handle.Init.StopBits = UART_STOPBITS_1;
    g_uart_handle.Init.Parity = UART_PARITY_NONE;
    g_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    g_uart_handle.Init.Mode = UART_MODE_TX_RX;
    g_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&g_uart_handle) != HAL_OK)
    {
        handleError();
    }
}

void initLcd()
{
    g_lcd_handle.instance = LCD0;
    g_lcd_handle.init.driver = &HD44780_driver;

    if (LCD_init(&g_lcd_handle) != HAL_OK)
    {
        handleError();
    }
}

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&g_uart_handle, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}

int __io_getchar()
{
    uint8_t ch;
    HAL_StatusTypeDef status =
        HAL_UART_Receive(&g_uart_handle, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return (status == HAL_OK) ? (int)ch : -1;
}

void handleError()
{
    while (1) __NOP();
}
