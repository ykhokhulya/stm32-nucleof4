#pragma once

#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} LCD_IOPinTypedDef;

typedef struct
{
    LCD_IOPinTypedDef en;
    LCD_IOPinTypedDef rs;
    LCD_IOPinTypedDef d4;
    LCD_IOPinTypedDef d5;
    LCD_IOPinTypedDef d6;
    LCD_IOPinTypedDef d7;
} LCD_IOTypeDef;

typedef struct
{
    HAL_StatusTypeDef (*init)(LCD_IOTypeDef*);
    int16_t (*getCols)(LCD_IOTypeDef*);
    int16_t (*getRows)(LCD_IOTypeDef*);
    void (*displayOn)(LCD_IOTypeDef*);
    void (*displayOff)(LCD_IOTypeDef*);
    void (*clear)(LCD_IOTypeDef*);
    void (*home)(LCD_IOTypeDef*);
    void (*cursor)(LCD_IOTypeDef*, int16_t, int16_t);
    void (*print)(LCD_IOTypeDef*, char);
} LCD_DriverTypeDef;

#ifdef __cplusplus
}
#endif
