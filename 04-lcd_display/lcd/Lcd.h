#pragma once

#include <stdint.h>
#include <stm32f4xx_hal.h>

#include "drivers/Lcd_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    LCD0,
    LCD1,
    LCD2,
    LCD3,
};

typedef struct
{
    LCD_DriverTypeDef* driver;
} LCD_InitTypeDef;

typedef struct
{
    uint8_t instance;
    LCD_InitTypeDef init;
    LCD_IOTypeDef io;
} LCD_HandleTypeDef;

HAL_StatusTypeDef LCD_init(LCD_HandleTypeDef* lcd);
int16_t LCD_getCols(LCD_HandleTypeDef* lcd);
int16_t LCD_getRows(LCD_HandleTypeDef* lcd);
void LCD_displayOn(LCD_HandleTypeDef* lcd);
void LCD_displayOff(LCD_HandleTypeDef* lcd);
void LCD_clear(LCD_HandleTypeDef* lcd);
void LCD_cursor(LCD_HandleTypeDef* lcd, int16_t cols, int16_t rows);
void LCD_print(LCD_HandleTypeDef* lcd, char ch);
void LCD_prints(LCD_HandleTypeDef* lcd, const char* str);
void LCD_printf(LCD_HandleTypeDef* lcd, const char* format, ...);

void LCD_MspInit(LCD_HandleTypeDef* lcd);
void LCD_MspDeInit(LCD_HandleTypeDef* lcd);

#ifdef __cplusplus
}
#endif
