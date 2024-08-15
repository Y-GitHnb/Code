/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    dma.c
 * @brief   This file provides code for the configuration
 *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/**
 * Enable DMA controller clock
 * Configure DMA for memory to memory transfers
 *   hdma_memtomem_dma1_channel1
 */
void MX_DMA_Init(void)
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* Configure DMA request hdma_memtomem_dma1_channel1 on DMA1_Channel1 */
	hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
	hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
	hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
	hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
	hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_LOW;
	if (HAL_DMA_Init(&hdma_memtomem_dma1_channel1) != HAL_OK)
	{
		Error_Handler();
	}

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	/* DMA1_Channel2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
	/* DMA1_Channel3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 1, 2);
	HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
}

/* USER CODE BEGIN 2 */

/*
*********************************************************************************************************
* 函 数 名: DMA_Usart_Send
* 功能说明: 串口发送功能函数
* 形  参: buf，len
* 返 回 值: 无
*********************************************************************************************************
*/
void DMA_Usart_Send(uint8_t *buf, uint8_t len) // 串口发送封装
{
	if (HAL_UART_Transmit_DMA(&huart3, buf, len) != HAL_OK) // 判断是否发送正常，如果出现异常则进入异常中断函数
	{
		Error_Handler();
	}
}

/*
*********************************************************************************************************
* 函 数 名: DMA_Usart1_Read
* 功能说明: 串口接收功能函数
* 形  参: Data,len
* 返 回 值: 无
*********************************************************************************************************
*/
void DMA_Usart1_Read(uint8_t *Data, uint8_t len) // 串口接收封装
{
	HAL_UART_Receive_DMA(&huart3, Data, len); // 重新打开DMA接收
}

/* USER CODE END 2 */
