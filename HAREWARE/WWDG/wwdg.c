#include<wwdg.h>
#include<stm32f10x_rcc.h>
#include<stm32f10x.h>
#include<stm32f10x_wwdg.h>
#include<led.h>

//����WWDG������������ֵ��Ĭ��Ϊ���
u8 WWDG_CNT =0x7f;
//tr : T[6:0]������ֵ ����CR�Ĵ���
//wr : W[6:0]����ֵ   ����CFR�Ĵ���
//fprer:��Ƶϵ��(WDGTB) �������2λ��Ч
//Fwwdg = PCLK1/(4096*2^fprer)
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//WWDGʱ��ʹ��
	
	  WWDG_CNT = tr & WWDG_CNT;  //��ʼ��WWDG_CNT   �Ĵ���
	
		WWDG_SetPrescaler(fprer);     //���÷�Ƶ��
	
	  WWDG_SetWindowValue(wr);   //���ô���ֵ
	
	  WWDG_Enable(WWDG_CNT);            //���üĴ�����ʼֵ��ʹ�ܿ��Ź� ���� counter
	
	  
 ///û�뵽��
	WWDG_ClearFlag();           //�����ǰ�����жϱ�־
	
	WWDG_NVIC_Init();           //��ʼ�����ڿ��Ź� NVIC
	WWDG_EnableIT();           //�������Ź��ж�
}

//������WWDG������ �
void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);   //�ͼĴ�������һֱ

}


//���ڿ��Ź��жϷ������
void WWDG_NVIC_Init()
{
   NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; //WWDG�ж�
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ2 �����ȼ�3��2
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3�� //��ռ2 �����ȼ�3��2
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =3; //��ռ2 �����ȼ�3��2
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);     //��ʼ�� NVIC

}



 void WWDG_IRQnHandler(void)
 {
	 //Update WWDG counter
	 WWDG_SetCounter(WWDG_CNT);  //�������˾��
	 
	 //Clear EWI flag 
	 	WWDG_ClearFlag(); 
	 //Toggle GPIO_Led pin7
	 LED1=!LED1;
	 
 
 }
