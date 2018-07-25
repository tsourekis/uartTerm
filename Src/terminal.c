#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "isr.h"
#include "uart.h"
#include "terminal.h"

void terminalStartupScreen(void)
{
	printf(CURSOR_HOME CLEAR_TERMINAL);
	printf("Welcome to the uartTerm terminal\r\n");
	printf("--------------------------------\r\n");
	printf("Version:                     0x1\r\n");
	printf(NEWLINE);
}

extern uint8_t dataRX;
extern uint8_t dataFlag;
char str_dataRX[RX_DATA_LEN];
int bufferRX_idx = 0;


void terminalMenuList(void)
{
	printf(NEWLINE);
	printf("Type 'h' or 'help' to see the available commands and press ENTER\r\n");
	printf("----------------------------------------------------------------\r\n");
//	for(int idx = 0; idx <= RX_DATA_LEN; idx++)
//	{
//
//		if( (str_dataRX == "h" ) )
//		{
//			printf("this help menu\r\n");
//		}
//
//	}
}

