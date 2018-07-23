#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "isr.h"

extern UART_HandleTypeDef huart2;


// Note: Interrupts don't come enabled!!
void ISR_USART2_Init(void)
{

	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE); // enable interrupt on RX
	NVIC_EnableIRQ(USART2_IRQn); // enable the interrupts on USART2
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0); // set the USART2 interrupt priority (lower the number; the higher the priority)

}

volatile char str_dataRX[4];
static int bufferRX_idx = 0;


void USART2_IRQHandler(void)
{
	uint8_t dataRX = USART2->RDR;

	if(dataRX !='\n' && bufferRX_idx<4)
	{
		str_dataRX[bufferRX_idx] = dataRX;
		HAL_GPIO_TogglePin(GPIOA, LD2);
		printf(">>%c\r\n", str_dataRX[bufferRX_idx]);
		bufferRX_idx++;
	}
	else
	{
		bufferRX_idx = 0;
		//printf(">>%s\r\n", str_dataRX);

	}


}


