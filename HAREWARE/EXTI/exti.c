#include <stdio.h>
#include <led.h>
#include <key.h>
#include <delay.h>
#include <usart.h>
#include <beep.h>
#include <exti.h>
#include <stm32f10x.h>




//void EXTI_Init()
void EXTIX_Init()
{
	EXTI_InitTypeDef EXTI_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	KEY_Init(); //初始化IO口    为输入
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//RCC_APB2Periph_AFIO  ??   外设重映射功能使能AFIO 
	
	KEY_Init();    //初始化按键对应IO的模式
	//中断线映射
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5); //KEY0 对于PC5  中断线映射
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15); //KEY1 对应 PA15    中断线映射
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  //WK_UP
	//设置中短线模式
	EXTI_InitStrue.EXTI_Line=EXTI_Line5; //
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //选择中断模式
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PC5 对应KEY0 下降沿
  EXTI_Init(&EXTI_InitStrue);	
	
	EXTI_InitStrue.EXTI_Line=EXTI_Line15; //
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //选择中断模式
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PA.15 对应KEY0 下降沿
  EXTI_Init(&EXTI_InitStrue);	
	/*
	EXTI_InitStrue.EXTI_Line=EXTI_Line0; //为什么是线4，PE4？？
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //选择中断模式
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PE4 对应KEY0 下降沿
  EXTI_Init(&EXTI_InitStrue);	
	*/
//根据NVIC_Init中指定参数初试化外设NVIC寄存器
	NVIC_InitStrue.NVIC_IRQChannel=EXTI9_5_IRQn;   //使能按键所在的外部中断通道                 设置通道串口1位SART1_IRQn 在stm32f10x.h头文件中
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //使能通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //设置优先级 这里 0-3 ，随便设置为2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;        //子优先级没有随便设置为1
  NVIC_Init(&NVIC_InitStrue); 
	
  NVIC_InitStrue.NVIC_IRQChannel=EXTI15_10_IRQn;   //使能按键所在的外部中断通道                 设置通道串口1位SART1_IRQn 在stm32f10x.h头文件中
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //使能通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;    //设置优先级 这里 0-3 ，随便设置为2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //子优先级没有随便设置为1
  NVIC_Init(&NVIC_InitStrue); 
	/*
	 NVIC_InitStrue.NVIC_IRQChannel=EXTI0_IRQn;   //使能按键所在的外部中断通道                 设置通道串口1位SART1_IRQn 在stm32f10x.h头文件中
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //使能通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //设置优先级 这里 0-3 ，随便设置为2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //子优先级没有随便设置为1
  NVIC_Init(&NVIC_InitStrue); 
	*/
}
//编写中断处理函数
/*
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);  //防抖
	if(KEY0==0){         //KEY0==0 位操作
		LED0=!LED0; //取反操作
	}
	EXTI_ClearITPendingBit(EXTI_Line8); //清除中断标志位  让下次进入中断？？？
		
}
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);  //防抖
	 if(KEY1==0)
	{
	 LED1=!LED1;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line15);
		
}*/
/*
void EXTI0_IRQHandler(void) ////stm32min无蜂鸣器
{
	delay_ms(10);  //防抖
	 if(WK_UP==0)
	{
	 BEEP=!BEEP;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line15);
		
}*/