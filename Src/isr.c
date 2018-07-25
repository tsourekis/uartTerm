#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stm32f3xx_it.h"
#include "isr.h"

extern UART_HandleTypeDef huart2;


// Note: Interrupts don't come enabled!!
void ISR_USART2_Init(void)
{

	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE); // enable interrupt on RX
	NVIC_EnableIRQ(USART2_IRQn); // enable the interrupts on USART2
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0); // set the USART2 interrupt priority (lower the number; the higher the priority)

}

uint8_t dataRX;
uint8_t dataFlag;

void USART2_IRQHandler() // we are going to put very little in the ISR and use the RX data in another function.
{

	dataFlag = TRUE;
	dataRX = USART2->RDR;

}


