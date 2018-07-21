#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "isr.h"

extern UART_HandleTypeDef huart2;


// Note: Interrupts don't come enabled!!
void ISR_USART_EN(void)
{
	//USART2 ->CR1 |= USART_CR1_RXNEIE; // Receiver Interrupt Enable bit
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0); // set the USART2 interrupt priority
	NVIC_EnableIRQ(USART2_IRQn); // enable the interrupts on USART2
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE); // RX buffer not empty FLAG
	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_TXE); // TX complete FLAG
}
void USART2_IRQHandler(void)
{
	uint8_t dataRX = USART2->RDR; // define a variable to store the received data for USART2
	//HAL_UART_Receive(&huart2, dataRX, sizeof(dataRX), HAL_MAX_DELAY);

	printf("test\r\n");
	printf(">>%c", dataRX); // prints the received characters
	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_TXE); // TX complete FLAG

	HAL_GPIO_TogglePin(GPIOA,LD2);

}


