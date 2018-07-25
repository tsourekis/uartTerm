#include "main.h"
#include "stm32f3xx_hal.h"
#include "defines.h"
#include "stdio.h"
#include "string.h"
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
extern char str_dataRX;
extern int bufferRX_idx;

void terminalMenuList(void)
{
	printf(NEWLINE);
	printf("Type 'h' or 'help' to see the available commands and press ENTER\r\n");
	printf("----------------------------------------------------------------\r\n");
}


