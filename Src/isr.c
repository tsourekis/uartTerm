#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "isr.h"


void ISR_USART_EN(void)
{
	//USART2 ->CR1 |= USART_CR1_RXNEIE; // Receiver Interrupt Enable bit
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0); // set the USART2 interrupt priority
	NVIC_EnableIRQ(USART2_IRQn); // enable the interrupts on USART2
	//printf("Type yes(y) or no(n) \n");
}
//void USART2_IRQHandler(void)
//{
	//uint8_t dataRX = USART2->RDR; // define a variable to store the received data for USART2
	//printf(">>");
	//printf("%c", dataRX); // prints the received characters
//}


