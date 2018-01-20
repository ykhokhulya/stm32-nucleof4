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
RTC_HandleTypeDef g_rtc_handle;

static void initSystemClock();
static void initRtc();
static void initUart();
static void initLcd();

static void handleError();

int main()
{
    HAL_Init();

    initSystemClock();
    initUart();
    initLcd();
    initRtc();

    printf("System Clock Frequency = %lu Hz\n", SystemCoreClock);
    printf("Device identifier = %lu\n", HAL_GetDEVID());

    LCD_cursor(&g_lcd_handle, 1, 0);
    LCD_prints(&g_lcd_handle, "Hello!");

    while (1)
    {
        __NOP();
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

void initRtc()
{
    g_rtc_handle.Instance = RTC;
    g_rtc_handle.Init.HourFormat = RTC_HOURFORMAT_24;
    g_rtc_handle.Init.AsynchPrediv = 127;
    g_rtc_handle.Init.SynchPrediv = 255;
    g_rtc_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
    g_rtc_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    g_rtc_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    if (HAL_RTC_Init(&g_rtc_handle) != HAL_OK)
    {
        handleError();
    }

    RTC_DateTypeDef rtc_date = {};
    rtc_date.Year = 0x18;
    rtc_date.Month = RTC_MONTH_JANUARY;
    rtc_date.Date = 0x19;
    rtc_date.WeekDay = RTC_WEEKDAY_FRIDAY;

    if (HAL_RTC_SetDate(&g_rtc_handle, &rtc_date, RTC_FORMAT_BCD) != HAL_OK)
    {
        handleError();
    }

    RTC_TimeTypeDef rtc_time = {};
    rtc_time.Hours = 0x23;
    rtc_time.Minutes = 0x33;
    rtc_time.Seconds = 0x00;
    rtc_time.TimeFormat = RTC_HOURFORMAT12_PM;
    rtc_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    rtc_time.StoreOperation = RTC_STOREOPERATION_RESET;

    if (HAL_RTC_SetTime(&g_rtc_handle, &rtc_time, RTC_FORMAT_BCD) != HAL_OK)
    {
        handleError();
    }

    RTC_AlarmTypeDef alarm = {};
    alarm.AlarmTime.Hours = 0x00;
    alarm.AlarmTime.Minutes = 0x00;
    alarm.AlarmTime.Seconds = 0x00;
    alarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_PM;
    alarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    alarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    alarm.AlarmMask = RTC_ALARMMASK_ALL;
    alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
    alarm.AlarmDateWeekDay = RTC_WEEKDAY_FRIDAY;
    alarm.Alarm = RTC_ALARM_A;
    if (HAL_RTC_SetAlarm_IT(&g_rtc_handle, &alarm, RTC_FORMAT_BCD) != HAL_OK)
    {
        handleError();
    }
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef* hrtc)
{
    if (hrtc->Instance == RTC)
    {
        RTC_AlarmTypeDef alarm = {};
        if (HAL_RTC_GetAlarm(hrtc, &alarm, RTC_ALARM_A, FORMAT_BIN) != HAL_OK)
        {
            handleError();
        }

        RTC_TimeTypeDef time;
        HAL_RTC_GetTime(&g_rtc_handle, &time, RTC_FORMAT_BIN);

        RTC_DateTypeDef date;
        HAL_RTC_GetDate(&g_rtc_handle, &date, RTC_FORMAT_BIN);

        LCD_cursor(&g_lcd_handle, 0, 0);
        LCD_printf(
            &g_lcd_handle, "%02d-%02d-%2d", date.Month, date.Date, date.Year);
        LCD_cursor(&g_lcd_handle, 1, 0);
        LCD_printf(
            &g_lcd_handle,
            "%02d:%02d:%02d",
            time.Hours,
            time.Minutes,
            time.Seconds);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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
