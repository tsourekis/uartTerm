/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

// SEE DOCUMENT "UM1786" FOR HAL DRIVERS

// USER DEFINES - START
#define TX2 GPIO_PIN_2 //PA2
#define RX2 GPIO_PIN_3 //PA3
// USER DEFINES - END

// declare global handle for USART
UART_HandleTypeDef uart2Set;


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



int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* Initiliaze UART settings */
	uartInit();

	while (1)
	{
		char buffer0[] = "\r testing to see if the terminal works \r\n"; // \r\n";
		char buffer1[] = "if it works \r\n";
		char buffer2[] = "lines disappear after 1s \r\n";
		char buffer3[] = "terminal is cleared \r\n";

		// Terminal commands - START

		char clearTerminal[] = "\033[2J"; // clear terminal screen
		//char upXTerminal = "\033[XA"; // Move up X lines
		//char downXTerminal = "\033[XB"; // Move down X lines
		//char rightXTerminal = "\033[XC"; // Move right X lines
		//char leftXTerminal=  "\033[XD"; // Move left X lines

		// Terminal commands - END

		// see how to use printf instead of HAL_UART_TRANSMIT
		// redirect stdout ?? somethin to do with _write ....??

		//HAL_UART_Receive(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
		HAL_UART_Transmit(&uart2Set, buffer0, strlen(buffer0), HAL_MAX_DELAY);
		HAL_Delay(1000); // in ms
		HAL_UART_Transmit(&uart2Set, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		HAL_Delay(1000); // in ms
		HAL_UART_Transmit(&uart2Set, buffer2, strlen(buffer2), HAL_MAX_DELAY);
		HAL_Delay(1000); // in ms
		HAL_Delay(1000); // in ms
		HAL_UART_Transmit(&uart2Set, buffer2, strlen(buffer3), HAL_MAX_DELAY);
		HAL_Delay(1000); // in ms
		HAL_UART_Transmit(&uart2Set, clearTerminal, strlen(clearTerminal), HAL_MAX_DELAY);




	}

}

// USER DEFINED FUNCTIONS- START

/*
 *
// old init for reference

void gpioInit(void)
{
	// declare local typedef
	GPIO_InitTypeDef gpio;
	// alternatively use 	GPIO_InitTypeDef GPIO_InitStruct;
	 *
	 */
	/* Alternate definition below
	// setup pin PA5 (LED2) as a digital output in push-pull
	gpio.Pin = GPIO_PIN_5; // configure GPIO pin 5
	gpio.Mode = GPIO_MODE_OUTPUT_PP; // output is push-pull
	gpio.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &gpio); //
	*/
/*
	// setup pin PA5 (LED2) as a digital output in push-pull
	gpio.Pin = LED2; // configure GPIO pin 5
	gpio.Mode = GPIO_MODE_OUTPUT_PP; // output is push-pull
	gpio.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &gpio); // initiliase GPIO PA5 (LED2)

	// setup pin PC13 to accept input with button attached to it
	gpio.Pin = button1; // configure GPIO pin 13
	gpio.Mode = GPIO_MODE_INPUT; // set as floating input
	gpio.Pull = GPIO_PULLDOWN; // pulldown activated on PC13
	HAL_GPIO_Init(GPIOC, &gpio); // initialise GPIO PC13 (button1)

}
*/



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
