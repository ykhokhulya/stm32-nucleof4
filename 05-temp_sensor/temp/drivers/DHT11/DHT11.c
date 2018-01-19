#include "DHT11.h"

#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>

TEMP_DriverTypeDef DHT11_driver = {
    DHT11_init,
    DHT11_read,
};

HAL_StatusTypeDef DHT11_init(TEMP_IOTypeDef* io)
{
    HAL_GPIO_WritePin(io->data.port, io->data.pin, GPIO_PIN_SET);
    return HAL_OK;
}

int DHT11_read(TEMP_IOTypeDef* io, int8_t* t, int8_t* h)
{
    assert_param(io != 0);

    __disable_irq();

    DHT11_IO_request(io);
    int status = DHT11_IO_read(io, t, h);

    __enable_irq();

    return status;
}

void DHT11_IO_request(TEMP_IOTypeDef* io)
{
    assert_param(io != 0);

    HAL_GPIO_WritePin(io->data.port, io->data.pin, GPIO_PIN_RESET);
    DHT11_IO_delay(20000);
    HAL_GPIO_WritePin(io->data.port, io->data.pin, GPIO_PIN_SET);
}

int DHT11_IO_read(TEMP_IOTypeDef* io, int8_t* t, int8_t* h)
{
    assert_param(io != 0);
    assert_param(t != 0);
    assert_param(h != 0);

    uint64_t data = 0;

    // wait for data
    DHT11_IO_delay(249);

    GPIO_PinState pin_state;
    for (int i = 39; i >= 0; --i)
    {
        DHT11_IO_delay(41);

        pin_state = HAL_GPIO_ReadPin(io->data.port, io->data.pin);
        DHT11_IO_delay(pin_state == GPIO_PIN_RESET ? 40 : 91);

        if (pin_state == GPIO_PIN_SET)
        {
            data |= (uint64_t)1 << i;
        }
    }

    int8_t rhum_m = (data >> 32) & 0xff;
    int8_t rhum_l = (data >> 24) & 0xff;
    int8_t temp_m = (data >> 16) & 0xff;
    int8_t temp_l = (data >> 8) & 0xff;
    int8_t crc = data & 0xff;

    if (rhum_m + rhum_l + temp_m + temp_l == crc)
    {
        *h = rhum_m;
        *t = temp_m;

        return 1;
    }
    return 0;
}

void DHT11_IO_delay(uint32_t delay_us)
{
    delay_us = SystemCoreClock / 8000000 * delay_us;
    while (delay_us--)
        ;
}
