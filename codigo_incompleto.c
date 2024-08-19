/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "time.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7789/st7789.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO9 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO10 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO11 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO12 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int matrizInicial[8][8];
int matrizInvisivel[8][8];
int bombas = 8, unidade = 8, dezena = 0, clicou=0, x=0, y=0, i=0, j=0, posicaoX=0, posicaoY=0, resto=65, vizinha=0, sorteioBombas=0, subX=0, subY;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

void Menu(void);
void bombasRestantes(void);
void IniciarJogo (void);
void QuantidadeBombas(void);
void Controles(void);
void Jogo(void);
void atualizarCursor(void);
void unidaDezena (void);
void bombaVizinha(void);
void semBombas(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7789_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	 Menu();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Menu(void) {
	int escolha =0;
	    	ST7789_Fill_Color(RED);
	    	ST7789_WriteString(50, 20, "MINAS'CAMP", Font_16x26 , WHITE, RED);
	    	ST7789_WriteString(40, 80, "PA9 - JOGAR", Font_11x18, WHITE, RED);
	    	ST7789_WriteString(40, 120, "PA10 - BOMBAS", Font_11x18, WHITE, RED);
	    	ST7789_WriteString(40, 160, "PA11 - CONTROLES", Font_11x18, WHITE, RED);
	    	HAL_Delay(2000);

	    	while(escolha==0)
	    	    	{
	    	    	if (BOTAO9 == 0) {
	    	    		escolha=1;
	    	    	}

	    	    	else if (BOTAO10 == 0) {
	    	    	    escolha=2;
	    	    	  }

	    	    	else if (BOTAO11 == 0) {
	    	    	     escolha=3;
	    	    	    	  }
	    	    	}
	    	    	switch (escolha) {
	    	    		case 1:
	    	    		IniciarJogo();
	    	    	    Jogo();
	    	    		break;

	    	    		case 2:
	    	    		QuantidadeBombas();
	    	    		break;

	    	    		case 3:
	    	    		Controles();
	    	    	    break;

	    	    	}

}

void IniciarJogo(void) {

	 ST7789_Fill_Color(BLACK);

			  x=50;
			  y=0;
			  ST7789_WriteString(x, y, "Bombas: ", Font_16x26, RED, BLACK);
			  y=32;
			  bombasRestantes();
			  for(int i=0;i<8;i++) {

				  x=0;

			  for(int j=0;j<8;j++) {

				  matrizInicial[i][j] = 0;

				  if (i==0 && j==0) {
					  ST7789_WriteChar(x, y, 'X', Font_16x26, RED, BLACK);
					  x+=32;
				  } else {

				  ST7789_WriteChar(x, y, 'X',  Font_16x26, WHITE, BLACK);
				  x+=16;
				  ST7789_WriteChar(x, y, ' ', Font_16x26, WHITE, BLACK);
				  x+=16;

				  }

			  	  }

			  y+=26;

		  }

			  x=0, y=32;
		  }

void bombasRestantes(void) {

	ST7789_WriteChar(196, 0, unidade + '0', Font_16x26, RED, BLACK);
	ST7789_WriteChar(180, 0, dezena + '0', Font_16x26, RED, BLACK);

}
void Controles (void) {
	int escolha=0;

		ST7789_Fill_Color(MAGENTA);
			ST7789_WriteString(50, 10, "Controles:", Font_16x26, WHITE, MAGENTA);
			ST7789_WriteString(20, 60, "PA9 - ESQUERDA ",Font_11x18, WHITE, MAGENTA);
			ST7789_WriteString(20, 90, "PA11 - DIREITA ", Font_11x18, WHITE, MAGENTA);
			ST7789_WriteString(20, 120, "PA12 - MARCAR BOMBA ", Font_11x18, WHITE, MAGENTA);
			ST7789_WriteString(20, 150, "PA10 - CONFIRMAR ", Font_11x18, WHITE, MAGENTA);
			ST7789_WriteString(20, 200, "PA10 - MENU ", Font_11x18, WHITE, MAGENTA);

			while(escolha == 0){

			if (BOTAO10 == 0) {
				escolha = 1;
			}

	}
}

void QuantidadeBombas(void){

		ST7789_Fill_Color(BLUE);
		ST7789_WriteString(30, 20, "Bombas: ", Font_16x26, WHITE, BLUE);
		ST7789_WriteChar(166, 20, unidade + '0', Font_16x26, GREEN, BLUE);
		ST7789_WriteChar(150, 20, dezena + '0', Font_16x26, GREEN, BLUE);
		ST7789_WriteString(40, 80, "PA9 - DIMINUIR ",Font_11x18, WHITE, BLUE);
		ST7789_WriteString(40, 120, "PA11 - AUMENTAR ", Font_11x18, WHITE, BLUE);
		ST7789_WriteString(40, 200, "PA10 - MENU " , Font_11x18, GREEN, BLUE);

		do {

			if (BOTAO9 == 0) {
				unidade--;
				clicou++;
				}

			else if (BOTAO11 == 0) {
				unidade++;
				clicou++;
			}

			unidaDezena();
			if (dezena >= 6) {
					if (unidade > 0) {
						dezena = 0;
						unidade = 3;
					}
				}
				else if (dezena <= 0) {
					if (unidade < 3) {
						dezena = 6;
						unidade = 0;
					}
				}

			if(clicou==1) {

				if(dezena*10+unidade<=8){

					ST7789_WriteChar(166, 20, unidade + '0', Font_16x26, GREEN, BLUE);
					ST7789_WriteChar(150, 20, dezena + '0', Font_16x26, GREEN, BLUE);

				} else if (dezena*10+unidade<=11) {

					ST7789_WriteChar(166, 20, unidade + '0', Font_16x26, YELLOW, BLUE);
					ST7789_WriteChar(150, 20, dezena + '0', Font_16x26, YELLOW, BLUE);

				}else if (dezena*10+unidade<=14) {

					ST7789_WriteChar(166, 20, unidade + '0', Font_16x26, RED, BLUE);
					ST7789_WriteChar(150, 20, dezena + '0', Font_16x26, RED, BLUE);

				} else {

					ST7789_WriteChar(166, 20, unidade + '0', Font_16x26, BLACK, BLUE);
					ST7789_WriteChar(150, 20, dezena + '0', Font_16x26, BLACK, BLUE);

				}
				clicou=0;

			}

			HAL_Delay(200);

			} while (BOTAO10 == 1);

		bombas = dezena*10+unidade;
		resto-=bombas;

}

void unidaDezena (void) {

	if(unidade > 9){
		dezena++;
		unidade = 0;
	} else if (unidade < 0) {

		dezena--;
		unidade = 9;

	}

	bombas = dezena*10+unidade;

}

void Jogo(void) {

	while (1){

		atualizarCursor();

		if (resto == 0) {

			ST7789_Fill_Color(BLUE);
			ST7789_WriteString(40,70,"VICTORY!!", Font_16x26 , YELLOW, BLUE);
			HAL_Delay(1000);
			ST7789_WriteString(40,200,"PA10 - Menu", Font_11x18 , WHITE, BLUE);
			while (BOTAO10 == 1) {
				ST7789_WriteString(75,125,"YOU WIN!", Font_11x18 , YELLOW, BLUE);
			}
			Menu();

		}

		 }
	}

void bombaVizinha(void) {

	vizinha = 0;

	for(int i=0; i<8; i++) {

		for(int j=0; j<8; j++) {

			if(i == posicaoX && j == posicaoY) {

				if(matrizInvisivel[i-1][j-1] == 1 && i-1>=0 && j-1>=0){

					vizinha++;

				} if(matrizInvisivel[i-1][j] == 1 && i-1>=0){

					vizinha++;

				} if(matrizInvisivel[i-1][j+1] == 1 && i-1>=0 && j+1<8){

					vizinha++;

				} if(matrizInvisivel[i][j-1] == 1 && j-1>=0){

					vizinha++;

				} if(matrizInvisivel[i][j+1] == 1 && j+1<8){

					vizinha++;

				} if(matrizInvisivel[i+1][j-1] == 1 && i<8 && j-1>=0){

					vizinha++;

				} if(matrizInvisivel[i+1][j] == 1 && i<8){

					vizinha++;

				} if(matrizInvisivel[i+1][j+1] == 1 && i<8 && j+1<8){

					vizinha++;

				}

				x=posicaoX*32;
				y=posicaoY*26+32;
				ST7789_WriteChar(x, y, vizinha + '0', Font_16x26, BLUE, BLACK);

			}

		}
	}

}

void semBombas(void) {

	subX = posicaoX;
	subY = posicaoY;

	if(subX-1>=0 && subY-1>=0 && matrizInicial[subX-1][subY-1] == 0){

		matrizInicial[subX-1][subY-1] = 3;
		posicaoX = subX-1;
		posicaoY = subY-1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subX-1>=0 && matrizInicial[subX-1][subY] == 0){

		matrizInicial[subX-1][subY] = 3;
		posicaoX = subX-1;
		posicaoY = subY;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subX-1>=0 && subY+1<8 && matrizInicial[subX-1][subY+1] == 0){

		matrizInicial[subX-1][subY+1] = 3;
		posicaoX = subX-1;
		posicaoY = subY+1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subY-1>=0 && matrizInicial[subX][subY-1] == 0){

		matrizInicial[subX][subY-1] = 3;
		posicaoX = subX;
		posicaoY = subY-1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subY+1<8 && matrizInicial[subX][subY+1] == 0){

		matrizInicial[subX][subY+1] = 3;
		posicaoX = subX;
		posicaoY = subY+1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subX+1<8 && subY-1>=0 && matrizInicial[subX+1][subY-1] == 0){

		matrizInicial[subX+1][subY-1] = 3;
		posicaoX = subX+1;
		posicaoY = subY-1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subX+1<8 && matrizInicial[subX+1][subY] == 0){

		matrizInicial[subX+1][subY] = 3;
		posicaoX = subX+1;
		posicaoY = subY;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	} if(subX+1<8 && subY+1<8 && matrizInicial[subX+1][subY+1] == 0){

		matrizInicial[subX+1][subY+1] = 3;
		posicaoX = subX+1;
		posicaoY = subY+1;
		bombaVizinha();
		while (vizinha == 0) {

			semBombas();

		}

	}

	while(matrizInicial[subX][subY] == 3) {

		subY++;

		if(subY>7) {

			subY = 0;
			subX++;

			if(subX>7) {

				subX = 0;

			}

		}

	}
	posicaoX = subX;
	posicaoY = subY;

}

void atualizarCursor(void) {

		if(sorteioBombas == 1) {

			for (i=0; i<8; i++) {
						for (int j=0; j<8; j++) {

							matrizInvisivel[i][j] = 0;

						}
					}

					srand(time(NULL));

					int bombasColocadas = 0;

					while (bombasColocadas < bombas) {
						int x = rand () % 8;
						int y = rand () % 8;

						if (matrizInvisivel[x][y] == 0) {
							matrizInvisivel[x][y] = 1;
							bombasColocadas++;
						}
					}

					bombaVizinha();
					while (vizinha == 0 && sorteioBombas>=1) {

						semBombas();

					}
					sorteioBombas++;

		}

		if(BOTAO12==0){

			if(matrizInicial[posicaoX][posicaoY] != 2 && bombas >= 1) {

				matrizInicial[posicaoX][posicaoY] = 2;
				unidade--;

			} else {

				ST7789_WriteChar(x, y, 'B', Font_16x26, RED, BLACK);

				if (matrizInvisivel[posicaoX][posicaoY] == 0) {

					matrizInicial[posicaoX][posicaoY] = 0;

				} else {

					matrizInicial[posicaoX][posicaoY] = 1;

				}

				unidade++;

			}

			unidaDezena();
			bombasRestantes();
			ST7789_WriteChar(x, y, 'B', Font_16x26, RED, BLACK);

		}

	if(BOTAO10==0){

		sorteioBombas++;

		if(matrizInvisivel[posicaoX][posicaoY] == 1){
		sorteioBombas = 1;
		ST7789_Fill_Color(LBBLUE);
		ST7789_WriteString(40,70,"GAME OVER!", Font_16x26 , RED, LBBLUE);
		HAL_Delay(1000);
		ST7789_WriteString(40,200,"PA10 - Menu", Font_11x18 , WHITE, LBBLUE);
		while (BOTAO10 == 1) {
			ST7789_WriteString(75,125,"YOU LOSE!", Font_11x18 , RED, LBBLUE);
		}
		Menu();

		} else {

			bombaVizinha();
			matrizInicial[posicaoX][posicaoY] = 3;
			while (vizinha == 0 && sorteioBombas>1) {

				semBombas();

			}
			resto--;

		}


			}

		if(BOTAO9 == 0) {

			if(matrizInicial[posicaoX][posicaoY] == 2) {

					ST7789_WriteChar(x, y, 'B', Font_16x26, RED, BLACK);

				} else if (matrizInicial[posicaoX][posicaoY] == 0 || matrizInicial[posicaoX][posicaoY] == 1) {

						ST7789_WriteChar(x, y, 'X', Font_16x26, WHITE, BLACK);

					}

				do {

					posicaoX--;

					if (posicaoX == -1) {

						posicaoY--;
						posicaoX = 7;

						if(posicaoY == -1) {

							posicaoY = 7;

						}

					}

					x-=32;

		if(x<0) {

			x=224;
			y-=26;

			if(y<32) {

				y=216;

			}

		}

				} while (matrizInicial[posicaoX][posicaoY] == 3);

		ST7789_WriteChar(x, y, 'X', Font_16x26, RED, BLACK);

		}else if (BOTAO11 == 0) {

			if(matrizInicial[posicaoX][posicaoY] == 2) {

					ST7789_WriteChar(x, y, 'B', Font_16x26, RED, BLACK);

				} else if (matrizInicial[posicaoX][posicaoY] == 0 || matrizInicial[posicaoX][posicaoY] == 1) {

			ST7789_WriteChar(x, y, 'X', Font_16x26, WHITE, BLACK);

		}

		do  {

							posicaoX++;

							if (posicaoX == 8) {

								posicaoY++;
								posicaoX = 0;

								if(posicaoY == 8) {

									posicaoY = 0;

								}

							}

							x+=32;

		if(x>224) {

			x=0;
			y+=26;

			if(y>214) {

				y=32;

			}

		}

		} while (matrizInicial[posicaoX][posicaoY] == 3);

		ST7789_WriteChar(x, y, 'X', Font_16x26, RED, BLACK);

	}

	HAL_Delay(200);




}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
