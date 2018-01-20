#include "HD44780.h"

#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>

enum
{
    HD44780_COLS = 16,
    HD44780_ROWS = 2,
};

LCD_DriverTypeDef HD44780_driver = {
    HD44780_init,
    HD44780_getCols,
    HD44780_getRows,
    HD44780_displayOn,
    HD44780_displayOff,
    HD44780_clear,
    HD44780_home,
    HD44780_cursor,
    HD44780_print,
};

HAL_StatusTypeDef HD44780_init(LCD_IOTypeDef* io)
{
    assert_param(io != 0);

    HD44780_IO_delay(16000);
    HD44780_IO_command(io, 0b00110000, 0); // 8-bit mode
    HD44780_IO_delay(50);
    HD44780_IO_command(io, 0b00101100, 1); // 4-bit mode, high nibble only
    HD44780_IO_delay(50);
    HD44780_IO_command(io, 0b00101100, 0); // 4-bit mode
    HD44780_IO_delay(50);
    HD44780_IO_command(io, 0b00001000, 0); // display off
    HD44780_IO_delay(50);
    HD44780_IO_command(io, 0b00000001, 0); // clear
    HD44780_IO_delay(1600);
    HD44780_IO_command(io, 0b00000110, 0); // cursor shift
    HD44780_IO_delay(50);
    HD44780_IO_command(io, 0b00001100, 0); // display on
    HD44780_IO_delay(50);

    return HAL_OK;
}

int16_t HD44780_getCols(LCD_IOTypeDef* io)
{
    UNUSED(io);
    return HD44780_COLS;
}

int16_t HD44780_getRows(LCD_IOTypeDef* io)
{
    UNUSED(io);
    return HD44780_ROWS;
}

void HD44780_displayOn(LCD_IOTypeDef* io)
{
    HD44780_IO_command(io, 0b00001100, 0);
    HD44780_IO_delay(50);
}

void HD44780_displayOff(LCD_IOTypeDef* io)
{
    HD44780_IO_command(io, 0b00001000, 0);
    HD44780_IO_delay(50);
}

void HD44780_clear(LCD_IOTypeDef* io)
{
    HD44780_IO_command(io, 0b00000001, 0);
    HD44780_IO_delay(1600);
}

void HD44780_home(LCD_IOTypeDef* io)
{
    HD44780_IO_command(io, 0b00000011, 0);
    HD44780_IO_delay(1600);
}

void HD44780_cursor(LCD_IOTypeDef* io, int16_t rows, int16_t cols)
{
    assert_param(cols >= 0 && cols < HD44780_COLS);
    assert_param(rows >= 0 && rows < HD44780_ROWS);

    uint8_t addr;
    switch (rows)
    {
    case 0:
        addr = 0x80;
        break;
    case 1:
        addr = 0xC0;
        break;
    }
    HD44780_IO_command(io, addr + cols, 0);
    HD44780_IO_delay(50);
}

void HD44780_print(LCD_IOTypeDef* io, char ch)
{
    HD44780_IO_data(io, ch);
    HD44780_IO_delay(50);
}

void HD44780_IO_command(LCD_IOTypeDef* io, uint8_t cmd, int only_high_nibble)
{
    assert_param(io != 0);

    HAL_GPIO_WritePin(io->rs.port, io->rs.pin, GPIO_PIN_RESET);
    HD44780_IO_delay(20);
    HD44780_IO_writeNibble(io, cmd >> 4);
    if (!only_high_nibble)
    {
        HD44780_IO_delay(20);
        HD44780_IO_writeNibble(io, cmd);
    }
}

void HD44780_IO_data(LCD_IOTypeDef* io, uint8_t data)
{
    assert_param(io != 0);

    HAL_GPIO_WritePin(io->rs.port, io->rs.pin, GPIO_PIN_SET);
    HD44780_IO_delay(20);
    HD44780_IO_writeNibble(io, data >> 4);
    HD44780_IO_delay(20);
    HD44780_IO_writeNibble(io, data);
}

void HD44780_IO_writeNibble(LCD_IOTypeDef* io, uint8_t data)
{
    HAL_GPIO_WritePin(io->d4.port, io->d4.pin, HAL_IS_BIT_SET(data, 1 << 0));
    HAL_GPIO_WritePin(io->d5.port, io->d5.pin, HAL_IS_BIT_SET(data, 1 << 1));
    HAL_GPIO_WritePin(io->d6.port, io->d6.pin, HAL_IS_BIT_SET(data, 1 << 2));
    HAL_GPIO_WritePin(io->d7.port, io->d7.pin, HAL_IS_BIT_SET(data, 1 << 3));

    HAL_GPIO_WritePin(io->en.port, io->en.pin, GPIO_PIN_SET);
    HD44780_IO_delay(40);
    HAL_GPIO_WritePin(io->en.port, io->en.pin, GPIO_PIN_RESET);
    HD44780_IO_delay(5);

    HAL_GPIO_WritePin(io->d4.port, io->d4.pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(io->d5.port, io->d5.pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(io->d6.port, io->d6.pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(io->d7.port, io->d7.pin, GPIO_PIN_RESET);
}

void HD44780_IO_delay(uint32_t delay_us)
{
    delay_us = SystemCoreClock / 8000000 * delay_us;
    while (delay_us--)
        ;
}
