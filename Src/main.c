/* Includes */
#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "printfRedir.h"
#include "sysClock.h"
#include "gpio.h"
/* Declarations */

/* Typedef and Handle Declarations*/
GPIO_InitTypeDef GPIO;

GPIO_InitTypeDef uart2;
UART_HandleTypeDef huart2;

/* User function prototype calls */

// Startup configuration
void _write(int file, char *data, int len);
void sysClock(void);
void _Error_Handler(char *file, int line);
// LD2 Configuration
void RCC_GPIO_ENABLE(void);
void GPIO_LD2_Init(void);
// USART2 Configuration
void RCC_USART_ENABLE(void);
void GPIO_USART2_Init(void);
void USART2_Init(void);


/* Main function*/

int main(void)
{
	HAL_Init();
	sysClock();
	RCC_GPIO_ENABLE();
	RCC_USART_ENABLE();

	GPIO_USART2_Init();
	USART2_Init();

	GPIO_LD2_Init();



	while(1)
	{
		printf(CURSOR_HOME CLEAR_TERMINAL);
		printf("Testing Minicom \r\n");
		HAL_Delay(1000);
		printf("Works \r\n");
		HAL_Delay(1000);


	}


	return 0;
}

