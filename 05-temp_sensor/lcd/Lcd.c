#include "Lcd.h"

#include <stdarg.h>

HAL_StatusTypeDef LCD_init(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    LCD_MspInit(lcd);

    if (lcd->init.driver->init(&lcd->io) != HAL_OK)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

void LCD_deinit(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);

    LCD_MspDeInit(lcd);
}

int16_t LCD_getCols(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    return lcd->init.driver->getCols(&lcd->io);
}

int16_t LCD_getRows(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    return lcd->init.driver->getRows(&lcd->io);
}

void LCD_displayOn(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    lcd->init.driver->displayOn(&lcd->io);
}

void LCD_displayOff(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    lcd->init.driver->displayOff(&lcd->io);
}

void LCD_clear(LCD_HandleTypeDef* lcd)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    lcd->init.driver->clear(&lcd->io);
}

void LCD_cursor(LCD_HandleTypeDef* lcd, int16_t cols, int16_t rows)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    lcd->init.driver->cursor(&lcd->io, cols, rows);
}

void LCD_print(LCD_HandleTypeDef* lcd, char ch)
{
    assert_param(lcd != 0);
    assert_param(lcd->init.driver != 0);

    lcd->init.driver->print(&lcd->io, ch);
}

void LCD_prints(LCD_HandleTypeDef* lcd, const char* str)
{
    assert_param(str != 0);

    while (*str != 0) LCD_print(lcd, *str++);
}

void LCD_printf(LCD_HandleTypeDef* lcd, const char* format, ...)
{
    assert_param(format != 0);

    static char char_buffer[256];

    va_list args;
    va_start(args, format);
    vsprintf(char_buffer, format, args);
    va_end(args);

    LCD_prints(lcd, char_buffer);
}

__weak void LCD_MspInit(LCD_HandleTypeDef* lcd)
{
    UNUSED(lcd);
}

__weak void LCD_MspDeInit(LCD_HandleTypeDef* lcd)
{
    UNUSED(lcd);
}
