#include "Temp.h"

#include <stdarg.h>

HAL_StatusTypeDef TEMP_init(TEMP_HandleTypeDef* temp)
{
    assert_param(temp != 0);
    assert_param(temp->init.driver != 0);

    TEMP_MspInit(temp);

    if (temp->init.driver->init(&temp->io) != HAL_OK)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

void TEMP_deinit(TEMP_HandleTypeDef* temp)
{
    assert_param(temp != 0);

    TEMP_MspDeInit(temp);
}

int TEMP_read(TEMP_HandleTypeDef* temp, int8_t* t, int8_t* h)
{
    assert_param(temp != 0);
    assert_param(temp->init.driver != 0);
    assert_param(t != 0);
    assert_param(h != 0);

    return temp->init.driver->read(&temp->io, t, h);
}

__weak void TEMP_MspInit(TEMP_HandleTypeDef* temp)
{
    UNUSED(temp);
}

__weak void TEMP_MspDeInit(TEMP_HandleTypeDef* temp)
{
    UNUSED(temp);
}
