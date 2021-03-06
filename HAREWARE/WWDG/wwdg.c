#include<wwdg.h>
#include<stm32f10x_rcc.h>
#include<stm32f10x.h>
#include<stm32f10x_wwdg.h>
#include<led.h>

//保存WWDG计数器的设置值，默认为最大
u8 WWDG_CNT =0x7f;
//tr : T[6:0]计数器值 操作CR寄存器
//wr : W[6:0]窗口值   操作CFR寄存器
//fprer:分频系数(WDGTB) ，仅最低2位有效
//Fwwdg = PCLK1/(4096*2^fprer)
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//WWDG时钟使能
	
	  WWDG_CNT = tr & WWDG_CNT;  //初始化WWDG_CNT   寄存器
	
		WWDG_SetPrescaler(fprer);     //设置分频数
	
	  WWDG_SetWindowValue(wr);   //设置窗口值
	
	  WWDG_Enable(WWDG_CNT);            //设置寄存器初始值并使能看门狗 设置 counter
	
	  
 ///没想到：
	WWDG_ClearFlag();           //清除提前唤醒中断标志
	
	WWDG_NVIC_Init();           //初始化窗口看门狗 NVIC
	WWDG_EnableIT();           //开启看门狗中断
}

//重设置WWDG计数器 �
void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);   //和寄存器代码一直

}


//窗口看门狗中断服务程序
void WWDG_NVIC_Init()
{
   NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; //WWDG中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占2 子优先级3组2
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3； //抢占2 子优先级3组2
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =3; //抢占2 子优先级3组2
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);     //初始化 NVIC

}



 void WWDG_IRQnHandler(void)
 {
	 //Update WWDG counter
	 WWDG_SetCounter(WWDG_CNT);  //当禁掉此句后，
	 
	 //Clear EWI flag 
	 	WWDG_ClearFlag(); 
	 //Toggle GPIO_Led pin7
	 LED1=!LED1;
	 
 
 }
