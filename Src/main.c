/* Includes */
#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "printfRedir.h"
#include "sysClock.h"
#include "gpio.h"
#include "isr.h"
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
// ISR Configurations and Functions
//void ISR_USART_EN(void);
//void USART2_IRQHandler(void);

/* Main function*/



int main(void)
{
	HAL_Init();
	sysClock();
	RCC_GPIO_ENABLE();
	RCC_USART_ENABLE();

	GPIO_LD2_Init();
	HAL_GPIO_WritePin(GPIOA, LD2, GPIO_PIN_SET);

	GPIO_USART2_Init();
	USART2_Init();

	ISR_USART2_Init();


	printf("Type something\r\n");

	//
	while(1)
	{
		//HAL_UART_Transmit_IT(&huart2, buff_TX,8); // changed TX to interrupt mode
	}


	return 0;
}

