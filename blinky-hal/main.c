#include "stm32f4xx_hal.h"

int main()
{
    HAL_Init();

    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}
