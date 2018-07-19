#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "uart.h"

extern GPIO_InitTypeDef uart2;
extern UART_HandleTypeDef huart2;

void RCC_USART_ENABLE(void)
{
	//__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
}

void GPIO_USART2_Init(void)
{
	// USART TX2 Configuration
	uart2.Pin = TX2; // USART2_TX (PA2)
	uart2.Mode = GPIO_MODE_AF_PP; // set output as push-pull
	uart2.Alternate = GPIO_AF7_USART2; // set port to Alternate Function #7
	uart2.Speed = GPIO_SPEED_FREQ_HIGH; //set high frequency clocking
	HAL_GPIO_Init(GPIOA,&uart2); // initialise GPIO TX2 (PA2) to be configured

	// USART RX2 Configuration
	uart2.Pin = RX2; // USART2_RX (PA3)
	uart2.Mode = GPIO_MODE_AF_PP; // set output as push-pull
	uart2.Alternate = GPIO_AF7_USART2; // set port to Alternate Function #7
	uart2.Speed = GPIO_SPEED_FREQ_HIGH; //set high frequency clocking
	HAL_GPIO_Init(GPIOA,&uart2); // initialise GPIO RX2 (PA3) to be configured
}

void USART2_Init(void)
{
	huart2.Instance = USART2; // set base to be USART2
	huart2.Init.BaudRate = 115200; // Baud Rate
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // no hardware control
	huart2.Init.Mode = UART_MODE_TX_RX; // TX and RX mode
	huart2.Init.Parity = UART_PARITY_NONE; // no parity
	huart2.Init.StopBits = UART_STOPBITS_1; // 1 stop bit
	huart2.Init.WordLength = UART_WORDLENGTH_8B; // 8-bit word length
	huart2.Init.OverSampling = UART_OVERSAMPLING_16; // Oversampling by 16U
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE; // disable one-bit sampling

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
}


