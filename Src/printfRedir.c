#include "main.h"
#include "stm32f3xx_hal.h"
#include "printfRedir.h"

extern UART_HandleTypeDef huart2;


void _write(int file, char *data, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY);
}
