#pragma once

#include <stm32f4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} TEMP_IOPinTypedDef;

typedef struct
{
    TEMP_IOPinTypedDef data;
} TEMP_IOTypeDef;

typedef struct
{
    HAL_StatusTypeDef (*init)(TEMP_IOTypeDef*);
    int (*read)(TEMP_IOTypeDef*, int8_t*, int8_t*);
} TEMP_DriverTypeDef;

#ifdef __cplusplus
}
#endif
