#include<wwdg.h>
#include<stm32f10x_rcc.h>
#include<stm32f10x.h>
#include<stm32f10x_wwdg.h>
#include<led.h>

//±£´æWWDG¼ÆÊıÆ÷µÄÉèÖÃÖµ£¬Ä¬ÈÏÎª×î´ó
u8 WWDG_CNT =0x7f;
//tr : T[6:0]¼ÆÊıÆ÷Öµ ²Ù×÷CR¼Ä´æÆ÷
//wr : W[6:0]´°¿ÚÖµ   ²Ù×÷CFR¼Ä´æÆ÷
//fprer:·ÖÆµÏµÊı(WDGTB) £¬½ö×îµÍ2Î»ÓĞĞ§
//Fwwdg = PCLK1/(4096*2^fprer)
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//WWDGÊ±ÖÓÊ¹ÄÜ
	
	  WWDG_CNT = tr & WWDG_CNT;  //³õÊ¼»¯WWDG_CNT   ¼Ä´æÆ÷
	
		WWDG_SetPrescaler(fprer);     //ÉèÖÃ·ÖÆµÊı
	
	  WWDG_SetWindowValue(wr);   //ÉèÖÃ´°¿ÚÖµ
	
	  WWDG_Enable(WWDG_CNT);            //ÉèÖÃ¼Ä´æÆ÷³õÊ¼Öµ²¢Ê¹ÄÜ¿´ÃÅ¹· ÉèÖÃ counter
	
	  
 ///Ã»Ïëµ½£º
	WWDG_ClearFlag();           //Çå³ıÌáÇ°»½ĞÑÖĞ¶Ï±êÖ¾
	
	WWDG_NVIC_Init();           //³õÊ¼»¯´°¿Ú¿´ÃÅ¹· NVIC
	WWDG_EnableIT();           //¿ªÆô¿´ÃÅ¹·ÖĞ¶Ï
}

//ÖØÉèÖÃWWDG¼ÆÊıÆ÷ º
void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);   //ºÍ¼Ä´æÆ÷´úÂëÒ»Ö±

}


//´°¿Ú¿´ÃÅ¹·ÖĞ¶Ï·şÎñ³ÌĞò
void WWDG_NVIC_Init()
{
   NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; //WWDGÖĞ¶Ï
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //ÇÀÕ¼2 ×ÓÓÅÏÈ¼¶3×é2
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3£» //ÇÀÕ¼2 ×ÓÓÅÏÈ¼¶3×é2
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =3; //ÇÀÕ¼2 ×ÓÓÅÏÈ¼¶3×é2
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);     //³õÊ¼»¯ NVIC

}



 void WWDG_IRQnHandler(void)
 {
	 //Update WWDG counter
	 WWDG_SetCounter(WWDG_CNT);  //µ±½ûµô´Ë¾äºó£¬
	 
	 //Clear EWI flag 
	 	WWDG_ClearFlag(); 
	 //Toggle GPIO_Led pin7
	 LED1=!LED1;
	 
 
 }
