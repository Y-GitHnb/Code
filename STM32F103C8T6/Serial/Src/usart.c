/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

uint8_t UART1_data[REC_LENGTH] = {0};		// 接收中断缓冲
uint8_t UART1_Rx_Buf[UART1_Rx_COUNT] = {0}; // 接收数据缓冲
/*	bit15，      接收完成标志
 *  bit14，      接收到0x0d
 *  bit13~0，    接收到的有效字节数目
 */
volatile uint16_t UART1_Rx_cnt = 0; // 接收状态

uint8_t UART2_data = 0;
uint8_t UART2_Rx_Buf[UART2_Rx_COUNT] = {0}; // 接收数据缓冲
volatile uint16_t UART2_Rx_cnt = 0;			// 接收计数
volatile uint8_t UART2_Rx_flag = 0;			// 接收状态

uint8_t UART3_Rx_Buf[UART3_Rx_COUNT] = {0}; // 接收数据缓冲
volatile uint16_t UART3_Rx_cnt = 0;			// 接收计数
volatile uint8_t UART3_Rx_flag = 0;			// 接收状态

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */
}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE); // 使能 RXNE 中断
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE); // 使能 IDLE 中断（空闲中断）

	/* USER CODE END USART2_Init 2 */
}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

	/* USER CODE END USART3_Init 2 */
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
	else if (uartHandle->Instance == USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* USART2 clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART2 interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 3, 1);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}
	else if (uartHandle->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART3 DMA Init */
		/* USART3_RX Init */
		hdma_usart3_rx.Instance = DMA1_Channel3;
		hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart3_rx.Init.Mode = DMA_NORMAL;
		hdma_usart3_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
		if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(uartHandle, hdmarx, hdma_usart3_rx);

		/* USART3_TX Init */
		hdma_usart3_tx.Instance = DMA1_Channel2;
		hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart3_tx.Init.Mode = DMA_NORMAL;
		hdma_usart3_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
		if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(uartHandle, hdmatx, hdma_usart3_tx);

		/* USART3 interrupt Init */
		HAL_NVIC_SetPriority(USART3_IRQn, 3, 2);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

	if (uartHandle->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if (uartHandle->Instance == USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

		/* USART2 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}
	else if (uartHandle->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10 | GPIO_PIN_11);

		/* USART3 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);

		/* USART3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART3_IRQn);
		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

#if 1

struct __FILE
{
	int handle;
};
FILE __stdout;

void _sys_exit(int x)
{
	x = x;
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0x0001);
	return ch;
}
#endif

// 串口回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) /* 如果是串口1 */
	{
		if ((UART1_Rx_cnt & 0x8000) == 0) /* 接收未完成 */
		{
			if (UART1_Rx_cnt & 0x4000) /* 接收到了0x0d（即回车键） */
			{
				if (UART1_data[0] != 0x0a) /* 接收到的不是0x0a（即不是换行键） */
				{
					UART1_Rx_cnt = 0; /* 接收错误,重新开始 */
				}
				else
				{
					UART1_Rx_cnt |= 0x8000; /* 接收完成了 */
				}
			}
			else /* 还没收到0X0d（即回车键） */
			{
				if (UART1_data[0] == 0x0d)
				{
					UART1_Rx_cnt |= 0x4000;
				}
				else
				{
					UART1_Rx_Buf[UART1_Rx_cnt & 0X3FFF] = UART1_data[0];
					UART1_Rx_cnt++;

					if (UART1_Rx_cnt > (UART1_Rx_COUNT - 1))
					{
						UART1_Rx_cnt = 0; /* 接收数据错误,重新开始接收 */
					}
				}
			}
		}

		HAL_UART_Receive_IT(&huart1, (uint8_t *)UART1_data, REC_LENGTH); // 重新接收
	}

	if (huart->Instance == USART2)
	{
		if (UART2_Rx_cnt < UART2_Rx_COUNT - 1)
		{
			UART2_Rx_Buf[UART2_Rx_cnt] = UART2_data;
			UART2_Rx_cnt++;
		}
		else // 溢出数组
		{
			UART2_Rx_cnt = 0;
			UART2_Rx_Buf[UART2_Rx_cnt] = UART2_data;
			UART2_Rx_cnt++;
		}

		HAL_UART_Receive_IT(&huart2, &UART2_data, REC_LENGTH);
	}
}

/* USER CODE END 1 */
