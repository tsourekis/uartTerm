#ifndef DEFINES_H_
#define DEFINES_H_

/* Defines */

// ANSI Color Schemes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
// Serial Terminal Instructions
#define NEWLINE "\r\n"
#define ENTER 13
#define CLEAR_TERMINAL "\033[2J"
#define CURSOR_HOME "\033[H"
#define RX_DATA_LEN 64
//USART2 Pins
#define TX2 GPIO_PIN_2 //PA2
#define RX2 GPIO_PIN_3 //PA3
//LD2 Pin
#define LD2 GPIO_PIN_5


#endif /* DEFINES_H_ */
