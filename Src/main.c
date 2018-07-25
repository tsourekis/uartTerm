/* Includes */
#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "printfRedir.h"
#include "sysClock.h"
#include "gpio.h"
#include "isr.h"
#include "terminal.h"
/* Data Type Declarations */
/* Typedef and Handle Declarations*/
GPIO_InitTypeDef GPIO;

GPIO_InitTypeDef uart2;
UART_HandleTypeDef huart2;

/* User Function Prototype Calls */

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
void ISR_USART_EN(void);
void USART2_IRQHandler(void);
void USART2_putc(void);
// Terminal Configuration
void terminalStartupScreen(void);
void terminalMenuList(void);
void terminalCommands(void);
/* Main function*/


extern uint8_t dataRX;
extern char str_dataRX;
extern uint8_t dataFlag;

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

	terminalStartupScreen();
	terminalMenuList();



	while(1)
	{

		USART2_putc();
		//terminalCommands();

	}


	return 0;
}

