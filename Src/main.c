#include "main.h"
#include "stm32f3xx_hal.h"
#include "stdio.h" // include for printf

#define TX2 GPIO_PIN_2 //PA2
#define RX2 GPIO_PIN_3 //PA3

const char clearTerminal[] = "\033[2J"; // clear terminal screen
const char cursorHome[] = "\033[H"; // set cursor back home

UART_HandleTypeDef uart2Set;

int main(void)
{
	HAL_Init();	//Reset of all peripherals, Initializes the Flash interface and the Systick
	SystemClock_Config(); //Configure the system clock
	MX_GPIO_Init(); // Initialize all configured peripherals

	uartInit(); // Initiliaze UART settings

	int dummyVar=0;

	// cursorhome            Move cursor to upper left corner       \033[H

	while (1)
	{
		if (dummyVar < 6)
		{
			printf("%s %s", cursorHome,clearTerminal);
			printf("This is to test the terminal \r\n");
			printf("Timer is %d \r\n", dummyVar++);
			HAL_Delay(1000);
		}
		else
		{
			dummyVar = 0;
			printf("Timer will reset now \r\n");
			printf("%s %s", cursorHome,clearTerminal);
			HAL_Delay(1000);
		}
	}

}

// USER DEFINED FUNCTIONS- START

void uartInit(void)
{
	// USART1_TX: PA9 USART1_RX: PA10 //

	//__USART2_CLK_ENABLE(); // enable USART2 RCC clock --> __HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	//__HAL_RCC_GPIOA_CLK_ENABLE(); // don't need to do this for this program since it is done in MX_PGIO_init();

	// declare local typedef for GPIO
	GPIO_InitTypeDef uartGPIO; // declare typedef for setting up GPIOs for UART

	// USART2 Pin Assignment //

	//TX2
	uartGPIO.Pin = TX2; // USART2_TX: PA2
	uartGPIO.Mode = GPIO_MODE_AF_PP; // set pin to Alternate Function in Push-Pull Mode
	uartGPIO.Alternate = GPIO_AF7_USART2; // assign alternate function to port
	uartGPIO.Speed = GPIO_SPEED_FREQ_HIGH; // high frequency clocking
	HAL_GPIO_Init(GPIOA, &uartGPIO); // initialise PA2 configuration
	//RX2
	uartGPIO.Pin = RX2; // USART2_TX: PA3
	uartGPIO.Mode = GPIO_MODE_AF_PP; // set pin to Alternate Function in Push-Pull Mode
	uartGPIO.Alternate = GPIO_AF7_USART2; // assign alternate function to port
	uartGPIO.Speed = GPIO_SPEED_FREQ_HIGH; // high frequency clocking
	HAL_GPIO_Init(GPIOA, &uartGPIO); // initialise PA3 configuration

	// Set the USART2 settings

	uart2Set.Instance = USART2;
	uart2Set.Init.BaudRate = 115200; // set the baud rate
	uart2Set.Init.HwFlowCtl = UART_HWCONTROL_NONE; // no hardware control
	uart2Set.Init.Mode = UART_MODE_RX | UART_MODE_TX; // TX or RX mode
	uart2Set.Init.Parity = UART_PARITY_NONE; // no parity
	uart2Set.Init.StopBits = UART_STOPBITS_1; // 1 stop bit
	uart2Set.Init.WordLength = UART_WORDLENGTH_8B;
	//note for possible bug:  UART_WordLength_8B address cannot be found??
	//uart2Set.Int.WordLength &= ~(1<<12)|(1<<28);// set the word length to 8 bits - UART_WordLength_8B;
	//HAL_UART_Init(&uart2Set); // initialise USART2 configuration

	if (HAL_UART_Init(&uart2Set) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}



/* Implementing printf in STM32 - START */


struct __FILE
{
	int dummyVariable;
};

FILE __stdout;
FILE __stdin;

int fputc(int c, FILE * stream)
{
//	uartWrite(c);
	return c;
}

void _write(int file, char *data, int len)
{
	HAL_UART_Transmit(&uart2Set, (uint8_t*)data, len, HAL_MAX_DELAY);
}

/* Implementing printf in STM32 - END */

// USER DEFINED FUNCTION - END




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
