/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

// USER DEFINES - START
#define LED2 GPIO_PIN_5
#define button1 GPIO_PIN_13

//define bi-dir LED pins
#define LED_R GPIO_PIN_15
#define LED_G GPIO_PIN_14
// USER DEFINES - END


void ledSetupRG(void)
{
	GPIO_InitTypeDef led;

	// setup pin PD15 as a digital output in push-pull
	led.Pin = LED_R; // configure GPIO pin 15
	led.Mode = GPIO_MODE_OUTPUT_PP; // output is push-pull
	led.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &led); // initiliase GPIO PD15

	// setup pin PD14 as a digital output in push-pull
	led.Pin = LED_G; // configure GPIO pin 14
	led.Mode = GPIO_MODE_OUTPUT_PP; // output is push-pull
	led.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &led); // initiliase GPIO PD14
}

int ledColour(int a)
{
	if(a == 0)
	{
		HAL_GPIO_WritePin(GPIOA, LED_R, GPIO_PIN_SET); // set pin high

		HAL_GPIO_WritePin(GPIOA, LED_G, GPIO_PIN_RESET); // set pin low
	}
	else if(a == 1)
	{
		HAL_GPIO_WritePin(GPIOA, LED_R, GPIO_PIN_RESET); // set pin low

		HAL_GPIO_WritePin(GPIOA, LED_G, GPIO_PIN_SET); // set pin high
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

	gpioInit();


	while (1)
	{
		/* Alternate below, see gpioInit() as well
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(100);
		*/

		// If the button is pressed the LED goes on
		/* Explanation:
		 *
		 * If the button is pressed the pin goes low,
		 * if the button is depressed the pin goes high;
		 * see the schematic for more detail.
		 * The pin is set to have a pulldown. A weak one compared
		 * to the the pull-up on the board in hardware.
		 */

		if( !HAL_GPIO_ReadPin(GPIOC,button1) )
		{
			// if the button is pressed, button1 state is pulled low and its
			// state changes.  We are reading to see if it the state has been set
			HAL_GPIO_WritePin(GPIOA, LED2, GPIO_PIN_RESET); // turn LED2 OFF
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, LED2, GPIO_PIN_SET); // turn LED2 ON
		}
	}

}

// USER DEFINED FUNCTIONS- START

void gpioInit(void)
{
	// declare local typedef
	GPIO_InitTypeDef gpio;
	// alternatively use 	GPIO_InitTypeDef GPIO_InitStruct;

	/* Alternate definition below
	// setup pin PA5 (LED2) as a digital output in push-pull
	gpio.Pin = GPIO_PIN_5; // configure GPIO pin 5
	gpio.Mode = GPIO_MODE_OUTPUT_PP; // output is push-pull
	gpio.Speed = GPIO_SPEED_FREQ_MEDIUM; // set medium frequency clocking
	HAL_GPIO_Init(GPIOA, &gpio); //
	*/
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
