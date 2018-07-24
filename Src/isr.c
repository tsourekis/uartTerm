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

void USART2_IRQHandler()
{
	char str_dataRX[RX_DATA_LEN];
	int bufferRX_idx = 0;
	uint8_t dataRX = USART2->RDR;

	// Circular Buffer - sort of?? - START
	if(dataRX !='\n' && (bufferRX_idx<RX_DATA_LEN) )
	{
		str_dataRX[bufferRX_idx] = dataRX;
		printf("%c", str_dataRX[bufferRX_idx]);
		fflush(stdout);
		bufferRX_idx++;
	}
	else if( bufferRX_idx > (RX_DATA_LEN -1) )
	{
		bufferRX_idx = 0;
	}
	// Circular Buffer - sort of?? - END

	// Escape sequence - ENTER KEY PRESSED
	if( dataRX == ENTER )
	{
		bufferRX_idx = 0;
		printf(NEWLINE);
	}

}


