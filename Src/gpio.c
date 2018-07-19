#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "gpio.h"

extern GPIO_InitTypeDef GPIO;


void RCC_GPIO_ENABLE(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

}


void GPIO_LD2_Init(void)
{
	GPIO.Pin = LD2; // configure GPIO Pin 5
	GPIO.Mode = GPIO_MODE_OUTPUT_PP; // set output as push-pull
	GPIO.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &GPIO); // initiliase GPIO LD2 (PA5) to be configured
}

