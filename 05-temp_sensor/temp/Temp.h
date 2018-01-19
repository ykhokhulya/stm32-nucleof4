#pragma once

#include <stdint.h>
#include <stm32f4xx_hal.h>

#include "drivers/Temp_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    TEMP0,
    TEMP1,
    TEMP2,
    TEMP3,
};

typedef struct
{
    TEMP_DriverTypeDef* driver;
} TEMP_InitTypeDef;

typedef struct
{
    uint8_t instance;
    TEMP_InitTypeDef init;
    TEMP_IOTypeDef io;
} TEMP_HandleTypeDef;

HAL_StatusTypeDef TEMP_init(TEMP_HandleTypeDef* temp);
int TEMP_read(TEMP_HandleTypeDef* temp, int8_t* t, int8_t* h);

void TEMP_MspInit(TEMP_HandleTypeDef* temp);
void TEMP_MspDeInit(TEMP_HandleTypeDef* temp);

#ifdef __cplusplus
}
#endif
