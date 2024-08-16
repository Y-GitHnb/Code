/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */

/* 遥控器接收状态
 * [7]  : 收到了引导码标志
 * [6]  : 得到了一个按键的所有信息
 * [5]  : 保留
 * [4]  : 标记上升沿是否已经被捕获
 * [3:0]: 溢出计时器
 */
uint8_t IN_receive_flag = 0;
uint32_t IN_receive_data = 0; /* 红外接收到的数据 */
uint8_t IN_receive_count = 0; /* 按键按下的次数 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 72 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 65535;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */
}
/* TIM2 init function */
void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 1894;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);
}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_IC_InitTypeDef sConfigIC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 72 - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (tim_baseHandle->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspInit 0 */

		/* USER CODE END TIM1_MspInit 0 */
		/* TIM1 clock enable */
		__HAL_RCC_TIM1_CLK_ENABLE();
		/* USER CODE BEGIN TIM1_MspInit 1 */

		/* USER CODE END TIM1_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspInit 0 */

		/* USER CODE END TIM2_MspInit 0 */
		/* TIM2 clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();
		/* USER CODE BEGIN TIM2_MspInit 1 */

		/* USER CODE END TIM2_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspInit 0 */

		/* USER CODE END TIM3_MspInit 0 */
		/* TIM3 clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM3 GPIO Configuration
		PA6     ------> TIM3_CH1
		*/
		GPIO_InitStruct.Pin = IN_receive_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(IN_receive_GPIO_Port, &GPIO_InitStruct);

		/* TIM3 interrupt Init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
		/* USER CODE BEGIN TIM3_MspInit 1 */

		/* USER CODE END TIM3_MspInit 1 */
	}
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (timHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspPostInit 0 */

		/* USER CODE END TIM2_MspPostInit 0 */

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**TIM2 GPIO Configuration
		PA1     ------> TIM2_CH2
		*/
		GPIO_InitStruct.Pin = IN_send_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(IN_send_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN TIM2_MspPostInit 1 */

		/* USER CODE END TIM2_MspPostInit 1 */
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM1)
	{
		/* USER CODE BEGIN TIM1_MspDeInit 0 */

		/* USER CODE END TIM1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM1_CLK_DISABLE();
		/* USER CODE BEGIN TIM1_MspDeInit 1 */

		/* USER CODE END TIM1_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspDeInit 0 */

		/* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM2_CLK_DISABLE();
		/* USER CODE BEGIN TIM2_MspDeInit 1 */

		/* USER CODE END TIM2_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspDeInit 0 */

		/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();

		/**TIM3 GPIO Configuration
		PA6     ------> TIM3_CH1
		*/
		HAL_GPIO_DeInit(IN_receive_GPIO_Port, IN_receive_Pin);

		/* TIM3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
		/* USER CODE BEGIN TIM3_MspDeInit 1 */

		/* USER CODE END TIM3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

// ---------------------------------------------- TIME1 --------------------------------------------------

void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_ENABLE(&htim1);
	while (__HAL_TIM_GET_COUNTER(&htim1) < us)
	{
	}
	__HAL_TIM_DISABLE(&htim1);
}

void delay_us_2(uint16_t nus)
{
	uint16_t delay = 0xffff - nus - 5;

	HAL_TIM_Base_Start(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, delay);
	while (delay < 0xffff - 5)
	{
		delay = __HAL_TIM_GetCounter(&htim1);
	}
	HAL_TIM_Base_Stop(&htim1);
}

// ---------------------------------------------- TIME2 --------------------------------------------------

void IR_SendBit(uint8_t bit)
{
	if (bit)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 947);
		delay_us(560);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
		delay_us(1680);
	}
	else
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 947);
		delay_us(560);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
		delay_us(560);
	}
}

/// @brief IR_SendNEC(0X00, 0x1C);
/// @param user ID
/// @param key send dat
void IR_SendNEC(uint8_t user, uint8_t key)
{
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 947);
	delay_us(9000);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
	delay_us(4500);

	uint32_t data = ((~key & 0xFF) << 24) | ((key & 0xFF) << 16) | ((~user & 0xFF) << 8) | (user & 0xFF);

	for (uint8_t i = 0; i <= 32; i++) // send
	{
		IR_SendBit(data & 0x01);
		data >>= 1;
	}
}

// ---------------------------------------------- TIME3 --------------------------------------------------

// 定时器更新中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		if (IN_receive_flag & 0x80) /* 上次有数据被接收到了 */
		{
			IN_receive_flag &= ~0X10; /* 取消上升沿已经被捕获标记 */

			if ((IN_receive_flag & 0X0F) == 0X00)
			{
				IN_receive_flag |= 1 << 6; /* 标记已经完成一次按键的键值信息采集 */
			}

			if ((IN_receive_flag & 0X0F) < 14)
			{
				IN_receive_flag++;
			}
			else
			{
				IN_receive_flag &= ~(1 << 7); /* 清空引导标识 */
				IN_receive_flag &= 0XF0;	  /* 清空计数器 */
			}
		}
	}
}

// 定时器输入捕获中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		uint16_t dval; /* 下降沿时计数器的值 */

		if (HAL_GPIO_ReadPin(IN_receive_GPIO_Port, IN_receive_Pin)) /* 上升沿捕获 */
		{
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING); // CC4P=1 设置为下降沿捕获
			__HAL_TIM_SET_COUNTER(&htim3, 0);														/* 清空定时器值 */
			IN_receive_flag |= 0X10;																/* 标记上升沿已经被捕获 */
		}
		else /* 下降沿捕获 */
		{
			dval = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);							   /* 读取CCR4也可以清CC4IF标志位 */
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); /* 配置TIM4通道4上升沿捕获 */

			if (IN_receive_flag & 0X10) /* 完成一次高电平捕获 */
			{
				if (IN_receive_flag & 0X80) /* 接收到了引导码 */
				{

					if (dval > 300 && dval < 800) /* 560为标准值,560us */
					{
						IN_receive_data >>= 1;			  /* 右移一位 */
						IN_receive_data &= ~(0x80000000); /* 接收到0 */
					}
					else if (dval > 1400 && dval < 1800) /* 1680为标准值,1680us */
					{
						IN_receive_data >>= 1;		   /* 右移一位 */
						IN_receive_data |= 0x80000000; /* 接收到1 */
					}
					else if (dval > 2000 && dval < 3000) /* 得到按键键值增加的信息 2500为标准值2.5ms */
					{
						IN_receive_count++;		 /* 按键次数增加1次 */
						IN_receive_flag &= 0XF0; /* 清空计时器 */
					}
				}
				else if (dval > 4200 && dval < 4700) /* 4500为标准值4.5ms */
				{
					IN_receive_flag |= 1 << 7; /* 标记成功接收到了引导码 */
					IN_receive_count = 0;	   /* 清除按键次数计数器 */
				}
			}

			IN_receive_flag &= ~(1 << 4);
		}
	}
}

// 处理红外按键
uint8_t remote_scan(void)
{
	uint8_t t1, t2; // 接收码，接收反码
	uint8_t flag = 0;

	if (IN_receive_flag & 0x40) /* 得到一个按键的所有信息了 */
	{
		t1 = IN_receive_data;				/* 得到地址码 */
		t2 = (IN_receive_data >> 8) & 0xff; /* 得到地址反码 */

		if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID) /* 检验遥控识别码(ID)及地址 */
		{
			t1 = (IN_receive_data >> 16) & 0xff;
			t2 = (IN_receive_data >> 24) & 0xff;

			if (t1 == (uint8_t)~t2)
			{
				flag = t1; /* 键值正确 */
			}
		}

		if ((flag == 0) || ((IN_receive_flag & 0X80) == 0)) /* 按键数据错误/遥控已经没有按下了 */
		{
			IN_receive_flag &= ~(1 << 6); /* 清除接收到有效按键标识 */
			IN_receive_count = 0;		  /* 清除按键次数计数器 */
		}
	}

	return flag;
}

/* USER CODE END 1 */
