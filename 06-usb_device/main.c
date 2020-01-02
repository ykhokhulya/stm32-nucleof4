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
#include <stm32f3xx_hal.h>
#include <stm32f3xx_hal_pcd.h>
#include <stm32f3xx_hal_uart.h>
#include <usbd_core.h>
#include <usbd_customhid.h>
#include "usbd_desc.h"
#include "usbd_gamepad_if.h"

UART_HandleTypeDef g_uart_handle;
USBD_HandleTypeDef g_usbd_handle;

static void initSystemClock();
static void initUart();
static void initUsbd();

static void errorHandler();

int main()
{
    HAL_Init();

    initSystemClock();
    // initUart();
    initUsbd();

    //printf("System Clock Frequency = %lu Hz\n", SystemCoreClock);
    //printf("Device identifier = %lu\n", HAL_GetDEVID());

//    const size_t HID_BufferSize = 4;
//    uint8_t HID_Buffer[HID_BufferSize];

    while (1)
    {
        HAL_Delay(500);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
        HAL_Delay(16);
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);

        //        if (counter++ == USBD_HID_GetPollingInterval(&g_usbd_handle))
        {
            // GetPointerData(HID_Buffer);

            /* send data though IN endpoint*/
//            if ((HID_Buffer[1] != 0) || (HID_Buffer[2] != 0))
//            {
//                USBD_CUSTOM_HID_SendReport(
//                    &g_usbd_handle, HID_Buffer, HID_BufferSize);
//            }
            //          counter =0;
        }
    }
}

void initSystemClock()
{
    /**
     * The system Clock is configured as follow :
     *    System Clock source            = PLL (HSE)
     *    SYSCLK(Hz)                     = 180000000
     *    HCLK(Hz)                       = 180000000
     *    AHB Prescaler                  = 1
     *    APB1 Prescaler                 = 4
     *    APB2 Prescaler                 = 2
     *    HSE Frequency(Hz)              = 8000000
     *    PLL_M                          = 8
     *    PLL_N                          = 360
     *    PLL_P                          = 2
     *    PLL_Q                          = 7
     *    VDD(V)                         = 3.3
     *    Main regulator output voltage  = Scale1 mode
     *    Flash Latency(WS)              = 5
     * The USB clock configuration from PLLSAI:
     *    PLLSAIM                        = 8
     *    PLLSAIN                        = 384
     *    PLLSAIP                        = 8
     */

    RCC_OscInitTypeDef rcc_osc_init = {};
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rcc_osc_init.HSEState = RCC_HSE_ON;
    rcc_osc_init.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;
    rcc_osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    rcc_osc_init.PLL.PLLMUL = RCC_PLL_MUL9;

    RCC_PeriphCLKInitTypeDef phy_clk_init = {};
    HAL_RCCEx_GetPeriphCLKConfig(&phy_clk_init);
    phy_clk_init.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;

    RCC_ClkInitTypeDef rcc_clk_init = {};
    rcc_clk_init.ClockType =
        (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
         RCC_CLOCKTYPE_PCLK2);
    rcc_clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_OK != HAL_RCC_OscConfig(&rcc_osc_init) ||
        HAL_OK != HAL_RCCEx_PeriphCLKConfig(&phy_clk_init) ||
        HAL_OK != HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_2))
    {
        errorHandler();
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

    if (HAL_OK != HAL_UART_Init(&g_uart_handle))
    {
        errorHandler();
    }
}

void initUsbd()
{
    if (USBD_OK != USBD_Init(&g_usbd_handle, &USBD_Desc, 0) ||
        USBD_OK != USBD_RegisterClass(&g_usbd_handle, &USBD_CUSTOM_HID) ||
        USBD_OK != USBD_CUSTOM_HID_RegisterInterface(
                       &g_usbd_handle, &USBD_GamepadHID_fops) ||
        USBD_OK != USBD_Start(&g_usbd_handle))
    {
        errorHandler();
    }
}

int __io_putchar(int ch)
{
    // HAL_UART_Transmit(&g_uart_handle, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}

int __io_getchar()
{
    return -1;
    // uint8_t ch;
    // HAL_StatusTypeDef status =
    //    HAL_UART_Receive(&g_uart_handle, &ch, 1, HAL_MAX_DELAY);
    // return (status == HAL_OK) ? (int)ch : -1;
}

void errorHandler()
{
    while (1) __NOP();
}
