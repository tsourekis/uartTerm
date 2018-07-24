#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "isr.h"
#include "terminal.h"

void terminalStartupScreen(void)
{
	printf(CURSOR_HOME CLEAR_TERMINAL);
	printf("Welcome to the uartTerm terminal\r\n");
	printf("--------------------------------\r\n");
	printf("Version:                     0x1\r\n");
	printf(NEWLINE);
}

extern char str_dataRX;
extern uint8_t dataRX;

void terminalMenuList(void)
{
	printf(NEWLINE);
	printf("Type 'h' or 'help' to see the available commands and press ENTER\r\n");
	printf("----------------------------------------------------------------\r\n");
//	if( (str_dataRX == 'h' || str_dataRX == 'help') && dataRX == ENTER)
//	{
//		printf("help menu\r\n");
//	}
}

