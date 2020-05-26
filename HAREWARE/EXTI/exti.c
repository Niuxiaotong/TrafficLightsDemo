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
	
	KEY_Init(); //��ʼ��IO��    Ϊ����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//RCC_APB2Periph_AFIO  ??   ������ӳ�书��ʹ��AFIO 
	
	KEY_Init();    //��ʼ��������ӦIO��ģʽ
	//�ж���ӳ��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5); //KEY0 ����PC5  �ж���ӳ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15); //KEY1 ��Ӧ PA15    �ж���ӳ��
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  //WK_UP
	//�����ж���ģʽ
	EXTI_InitStrue.EXTI_Line=EXTI_Line5; //
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //ѡ���ж�ģʽ
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PC5 ��ӦKEY0 �½���
  EXTI_Init(&EXTI_InitStrue);	
	
	EXTI_InitStrue.EXTI_Line=EXTI_Line15; //
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //ѡ���ж�ģʽ
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PA.15 ��ӦKEY0 �½���
  EXTI_Init(&EXTI_InitStrue);	
	/*
	EXTI_InitStrue.EXTI_Line=EXTI_Line0; //Ϊʲô����4��PE4����
	EXTI_InitStrue.EXTI_LineCmd= ENABLE;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;  //ѡ���ж�ģʽ
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling; //PE4 ��ӦKEY0 �½���
  EXTI_Init(&EXTI_InitStrue);	
	*/
//����NVIC_Init��ָ���������Ի�����NVIC�Ĵ���
	NVIC_InitStrue.NVIC_IRQChannel=EXTI9_5_IRQn;   //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��                 ����ͨ������1λ�USART1_IRQn ��stm32f10x.hͷ�ļ���
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //ʹ��ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //�������ȼ� ���� 0-3 ���������Ϊ2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;        //�����ȼ�û���������Ϊ1
  NVIC_Init(&NVIC_InitStrue); 
	
  NVIC_InitStrue.NVIC_IRQChannel=EXTI15_10_IRQn;   //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��                 ����ͨ������1λ�USART1_IRQn ��stm32f10x.hͷ�ļ���
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //ʹ��ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;    //�������ȼ� ���� 0-3 ���������Ϊ2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //�����ȼ�û���������Ϊ1
  NVIC_Init(&NVIC_InitStrue); 
	/*
	 NVIC_InitStrue.NVIC_IRQChannel=EXTI0_IRQn;   //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��                 ����ͨ������1λ�USART1_IRQn ��stm32f10x.hͷ�ļ���
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //ʹ��ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //�������ȼ� ���� 0-3 ���������Ϊ2    
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //�����ȼ�û���������Ϊ1
  NVIC_Init(&NVIC_InitStrue); 
	*/
}
//��д�жϴ�����
/*
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);  //����
	if(KEY0==0){         //KEY0==0 λ����
		LED0=!LED0; //ȡ������
	}
	EXTI_ClearITPendingBit(EXTI_Line8); //����жϱ�־λ  ���´ν����жϣ�����
		
}
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);  //����
	 if(KEY1==0)
	{
	 LED1=!LED1;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line15);
		
}*/
/*
void EXTI0_IRQHandler(void) ////stm32min�޷�����
{
	delay_ms(10);  //����
	 if(WK_UP==0)
	{
	 BEEP=!BEEP;
	}
	
	EXTI_ClearITPendingBit(EXTI_Line15);
		
}*/