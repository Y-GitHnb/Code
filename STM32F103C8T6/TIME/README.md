# 开发板：
	STM32F103C8T6


# 程序功能：
	基于 STM32 单片机万能红外遥控器


# 原理说明：
	- 每个定时器有四个通道，每一个通道都有一个捕获比较寄存器
	- 将寄存器值和计数器值比较，通过比较结果输出高低电平，便可以实现脉冲宽度调制模式（PWM信号）
	- TIMx_ARR 寄存器确定 PWM 频率
	- TIMx_CCRx 寄存器确定占空比

	* ?PWM 的一个周期：定时器从 0 开始向上计数
		- 0-t1 段，定时器计数器 TIMx_CNT 值小于 CCRx 值，输出低电平；
		- t1-t2 段，定时器计数器 TIMx_CNT 值大于 CCRx值，输出高电平；
		- 当 TIMx_CNT 值达到 ARR 时，定时器溢出，重新向上计数。

	* CCR：PWM 输出模式下除了 CNT（计数器当前值）、ARR（自动重装载值）外，还多了一个 CCRx（捕获/比较寄存器值），当 CNT 小于 CCRx 时，TIMx_CHx 通道输出低电平、当 CNT 等于或大于 CCRx 时，TIMx_CHx 通道输出高电平。


# 备注说明
	* STM32cubeMX 生成定时器：
		- 定时器频率 = Tclk / PSC + 1
		- 定时器溢出时间计算方法：Tout = ((ARR+1) * (PSC+1)) / Tclk us

	- Tclk：一般来源 APB1 Timer clocks (MHz)
	- PSC：分频系数，预分频器的值决定了定时器时钟频率的分频
	- ARR：计数值（定时器数 ARR 个数发生中断），ARR 的值决定了定时器计数器的最大值
	- CCR：CCR 的值决定了 PWM 的占空比，注意这个值不能超过 ARR
