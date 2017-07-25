#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init = {};
    gpio_init.Pin = GPIO_PIN_5;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_PULLDOWN;
    gpio_init.Speed = GPIO_SPEED_LOW;

    HAL_GPIO_Init(GPIOA, &gpio_init);
}

void HAL_MspDeInit(void)
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
}
