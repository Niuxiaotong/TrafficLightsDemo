-----------------\
20180928:
//SysTick?¡§¨º¡À?¡Â-?¨¦DD
#include <led.h>
#include <stm32f10x.h>
#include <sys.h>
//***************************************************************** 
//*                               SystemTick-Register                                   
//******************************************************************* 
//#define SYSTICK_TENMS    (*((volatile unsigned long *)0xE000E01C)) 
//#define SYSTICK_CURRENT  (*((volatile unsigned long *)0xE000E018)) 
//#define SYSTICK_RELOAD   (*((volatile unsigned long *)0xE000E014)) 
//#define SYSTICK_CSR       (*((volatile unsigned long *)0xE000E010)) 
//info:R-PA6,G-PA7,Y-PA5(DS0)
//Env:Stm32Ff103x?¡é???¨¹ ??¨ª¡§¦Ì???¨º??¡ê?¨¦
//Time:20180907-
//Info:?¨®¨º¨¹Lora ¨ºy?Y???¡é¡¤???¨¬¨¢¨¨?¨ºy?Y?¡é????LED?¡é¨ºy??1¨¹¦Ì1??¨º¡À
//LED1:PB5-PB7
//¨ºy??1¨¹¡êoPA5-PA7
//¨¨¨ª?t¨¦¨¨???¨°?¨¹¡êo ?¨®¨º¨¹¨ºy?Y¨®? Value ?????¨¦¦Ì?¦Ì? ¦Ì1??¨º¡À¨º¡À???¡é¨¢¨¢¦Ì?D??¡é?¡ê

//Function:???¨¹??¨ª¡§¦Ì???¨º??¡ê?¨¦
//Env:Stm32f103x, 74Hc595¡ê?Keil
//Author@New
//Tmie¡êo20180915
//INfo:
//IO?¡§¨°?:LED1-3:PB5-PB7
//74Hc595:PA5-PA7?¡éLOAD0 PAout(5)?¡éCLK PAout(6)?¡éSDK PAout(7)
//ps:74Hc595 LoAD?? ??¡Á??¡§¨°?¨®?SysTick->LOAD ???¡ä¡ê?1¨º???aLOAD0
//Load0:??¡ä??¡Â¡ê?CLK¡êo¨°???¨º¡À?¨® ¡ê? SDK¡êo¨ºy?Y??
//CLK = 0;¦Ì¨ª¦Ì???¡ê?¨ºy?Y?? SDK ¨º?¨¨?¨ºy?Y??¡ä??¡Â¡ê?CLK=1;¨¦?¨¦y????¨°?¨°?¨¨?¨ºy?Y??¡ä??¡Â¨ºy?Y?¨ª¨¨???¡ä??¡Â
//SysTick ????2???¡êohttps://blog.csdn.net/qq_40025335/article/details/79122244
//info:R-PA6,G-PA7,Y-PA5(DS0)
//Env:Stm32Ff103x¡¢ÖÇÄÜ ½»Í¨µÆÏÔÊ¾Ä£¿é
//Time:20180907-
//Info:½ÓÊÜLora Êý¾ÝÖ¡¡¢·Ö¸îÌáÈ¡Êý¾Ý¡¢¿ØÖÆLED¡¢ÊýÂë¹Üµ¹¼ÆÊ±
//LED1:PB5-PB7
//ÊýÂë¹Ü£ºPA5-PA7
//Èí¼þÉè¼Æ¿ò¼Ü£º ½ÓÊÜÊý¾ÝÓë Value ÔËËã¿ÉµÃµ½ µ¹¼ÆÊ±Ê±¼ä¡¢ÁÁµÆÐÅÏ¢¡£

//Function:ÖÇÄÜ½»Í¨µÆÏÔÊ¾Ä£¿é
//Env:Stm32f103x, 74Hc595£¬Keil
//Author@New
//Tmie£º20180919
//INfo:
//IO¶¨Òå:LED1-3:PB5-PB7£¬LED4-6£ºPB8-PB10
//74Hc595:PA6-PA8¡¢LOAD0 PAout(8)¡¢CLK PAout(6)¡¢SDK PAout(7)
//ps:74Hc595 LoADÎ» Ãû×Ö¶¨ÒåÓëSysTick->LOAD ÖØ¸´£¬¹Ê¸ÄÎªLOAD0
//Load0:Ëø´æÆ÷£¬CLK£ºÒÆÎ»Ê±ÖÓ £¬ SDK£ºÊý¾ÝÎ»
//CLK = 0;µÍµçÆ½£¬Êý¾ÝÎ» SDK ÊäÈëÊý¾Ý¼Ä´æÆ÷£¬CLK=1;ÉÏÉýÑØ½«ÒÑÒÆÈëÊý¾Ý¼Ä´æÆ÷Êý¾ÝËÍÈëËø´æÆ÷
//SysTick ÅäÖÃ²Î¼û£ºhttps://blog.csdn.net/qq_40025335/article/details/79122244
//20180928£º2¸ö½»Í¨µÆ LED1¡¢LED2¡¢±íÊ¾Ö±ÐÐ¡¢ÓÒ×ª¡¢×ó×ª¡
//½ÓÊÜLoraÊý¾Ý¡¢¶ÁÈ¡Êý¾ÝÖ¡ÄÚÈÝ¡¢eg: ÏàÎ»ÐÅÏ¢£º01;Í¨ÐÐÊ±¼ä£¨ÁÁÂÌµÆ£©£ºtime;
//¢LED1ÁÁÂÌµÆ ¿ªÊ¼µ¹¼ÆÊ± £ºÖ±ÐÐ¡¢ÓÒ×ª£»Í¬Ê± LED2ÁÁºìµÆ¡¢½ûÖ¹×ó×ª
//LED1£ºPA1¡¢PA5¡¢ £LLED2£    pc4\pc11º
  
//¡Á??¡ê
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//?¨®3¨´o¡¥¨ºy 2a¨º?
	void delay10ms(uint16_t temp)
{
	uint16_t  i,j,t;
	t=temp;
	while(t!=0)
    {
		for(i=200;i>0;i--)
       	for(j=248;j>0;j--);
		t--;
	}
}
*/
//8??¨ºy?Y ¡ä?DD¨º?¨¨?595
void SPI_595(unsigned char out_data)
{
	unsigned char i,temp;
 	for(i=0;i<8;i++)
  	{
		CLK=0;
     	temp=out_data&0x80;
     	if(temp==0x80)
        SDK=1;
        else SDK=0;    
     	out_data=out_data<<1;
     	CLK=1;
	}
}
//SysTick ?¡§¨º¡À?¡Â??¨º¡À
//???? systick ??¡ä??¡Â 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick ¦Ì¡À?¡ã??¡ä??¡Â¦Ì??¦Ì
	 //SysTick ¡Á??¡¥??¡Á¡ã3y?¦Ì??¡ä??¡Â
	 SysTick->LOAD = (72000000/8000000)*1000;//¡ä¨²¡À¨ª????msD¨¨¨°a¦Ì?9000??systick¨º¡À?¨®¨ºy ?
	 SysTick->CTRL |= 0x06; //SysTick ????o¨ª¡Á¡ä¨¬???¡ä??¡Â

 } 
//?D??¡ä|¨¤¨ªo¡¥¨ºy 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick ?¨®¨º¡Ào¡¥¨ºy
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // ¨®???¡Á¡Â¨®?¡ê?¡ê?¡ê?
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //¡À?¨¢?¨¦¨´?¡Â?¡ã3?¨º??¡¥
	 int j,k;
	 //?¨®¨º¨¹Lora¨ºy?Y??¡ê??a??3?Value?¦Ì?¡ã¦Ì1??¨º¡À¨º¡À??Loratime
	 //2a¨º??¦Ì
	 int Value = 0;//Value = LoraData[];//Value = 0,o¨¬¦Ì?¨¢¨¢¡ê?Value=1¡ê??¨¬¦Ì?¨¢¨¢
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // ?¨¤?-?¡¤
	 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 /*
	  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_11);*/
	 
	while(1)
	{
		//Lora?¨®¨º??¡ê?¨¦
		//1?¡é¨¢¨¢¦Ì¨¨D??¡éValue
		//2?¡é¦Ì1??¨º¡À¨º¡À3¡è
		
		
		//LED?¡ê?¨¦
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8¨º?3?¦Ì¨ª
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ¨º?3?¦Ì¨ª
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ¨º?3? ¦Ì¨ª
		/*//Test03?o¦Ì1??¨º¡À??¨º:?o??¨º?¨º¡À??'¨®0- 99
		*/
		//o¨¬¦Ì?¨¢¨¢¡ê?¦Ì1??¨º¡À?¡§???¨²99,?¨¬¦Ì?¨¢¨¢?¨®¨º¨¹¨ºy?Y?a¨º?¦Ì1??¨º¡À
		//Value = 0,o¨¬¦Ì?¨¢¨¢¡ê?Value=1¡ê??¨¬¦Ì?¨¢¨¢
		
		if(~Value)
			{
				//?¨¬¦Ì??e
				GPIO_SetBits(GPIOA,GPIO_Pin_1);//PB1 LED1
				//Red 
			GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PB5
		 //??¨º?¨°?¡ä?¨º¡À3???¡ä¨ª?¨®¡ê???¨º?¨¢?¡ä?--?y3¡ê??¨º?
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//¨ºy??1¨¹??¨º?99¡ê? o¨¬¦Ì?¨¢¨¢¡ê?¨º¡À?????¡ä1??¡§¡ê?
				//LedTime = LedTime*10000;
			Delay(50000); //5S  ?¡ê?ao¨¬¦Ì?¨¢¨¢¦Ì¨¨¨º¡À??	
			Value = ~Value;
			}
		else 
				{		
					//o¨¬¦Ì??e
					GPIO_SetBits(GPIOA,GPIO_Pin_5); //PB6 ¨º?3?¦Ì¨ª
					//Green
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB7 ¨º?3? ¦Ì¨ª	
					//¦Ì1??¨º¡À?¡ê?¨¦,j¡ê?3??¦ÌLoraTime¡ê??a¨¤??aj=92a¨º??¦Ì
					for(j=9;j>=0;j--)
					{
						for(k=9;k>=0;k--)
						{	
							LOAD0=1;
							LOAD0=0;	
							SPI_595(Tab[k]);//LED2-Right
							SPI_595(Tab[j]);//LED1-Left
							 Delay(10000); //1S  
				
						}				
					} 
					
				  Value = ~Value;					
				
				}
			/*
		for(j=9;j>=0;j--)
		{
			for(k=9;k>=0;k--)
			{	
				LOAD0=1;
				LOAD0=0;	
				SPI_595(Tab[k]);//LED2-Right
				SPI_595(Tab[j]);//LED1-Left
				//delay10ms(500);
				 Delay(10000); //1S  
			
			}				
		} */	
                                                                              
  } 
} 

--------------

//SysTick¶¨Ê±Æ÷-¿ÉÐÐ
#include <led.h>
#include <stm32f10x.h>
#include <sys.h>
//***************************************************************** 
//*                               SystemTick-Register                                   
//******************************************************************* 
#define SYSTICK_TENMS    (*((volatile unsigned long *)0xE000E01C)) 
#define SYSTICK_CURRENT  (*((volatile unsigned long *)0xE000E018)) 
#define SYSTICK_RELOAD   (*((volatile unsigned long *)0xE000E014)) 
#define SYSTICK_CSR       (*((volatile unsigned long *)0xE000E010)) 
  

//??systick???: 
void SysTick_Configuration(void) 
{ 
   SYSTICK_CURRENT=0; //?????? 
   SYSTICK_RELOAD=20000; //??????,????20M????1mS 
   SYSTICK_CSR|=0x06;// HCLK??Systick??,Systick????? 
 } 
//????: 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
SYSTICK_CURRENT=0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//??systick?????: 
  

unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SYSTICK_CSR|=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // ???????? 
SYSTICK_CSR|=0x06;// ??SysTick??? 
} 
  

int main() 
 { 
  SystemInit();    //??(??)??? 
 //GPIO_Init()(); //GPIO??? 
 LED_Init();
  SysTick_Configuration(); //??systick??? 
	while(1)
	{
		GPIOA->ODR|=1<<8;
		GPIOD->ODR|=1<<2;
		Delay(1000); //1S delay_ms(500);
		GPIOA->ODR&=~(1<<8);
		GPIOD->ODR&=~(1<<2);
	 Delay(1000); //1S  delay_ms(500);
                                                                              
  } 
} 
//Systick¶¨Ê±Æ÷-ÓÐÎÊÌâ
#include <stm32f10x.h>
#include <led.h>
//#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
#include <core_cm3.h>
//#include <beep.h> //stm32minÎÞ·äÃùÆ÷
//#include <exti.h>


/*void Delay(u32 nTime)
{
	u32 tmp = nTime;
	//u32 tmp = 
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//
}*/
///////@NXT:ÓÃÖÐ¶Ï·½Ê½ÊµÏÖÑÓÊ±
static __IO uint32_t TimingDelay;
void Delay(__IO uint32_t nTime)
{ 
   TimingDelay = nTime;
   while(TimingDelay != 0)
	 {
	   TimingDelay--;
	 }
}
void SysTick_Handler(void)
{
    if (TimingDelay == 0x00)
		{
		     LED1=1;
		}
     
}

int main()
{
	LED_Init();

	 if (SysTick_Config(SystemCoreClock / 8000000)) //systick???HCLK,??????1ms
     {
     while (1);
     }
	
    while(1)
     { 
	     LED1=0;
			 Delay(5);//2ms
			 //LED1=1;
			 
     }
}

//ÉÏÎ»»ú²âÊÔ£º
#include <stm32f10x.h>
#include "stdio.h"
#include <led.h>
#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
//#include <beep.h> //stm32minÎÞ·äÃùÆ÷
#include <exti.h>
//#include <iwdg.h> 
#include <wwdg.h> 
//#include <malloc.h> 

//u8 data1[200] = {1,2,3,4,5,6};
//u8 data;
int main()
{

	u16 t;

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	LED_Init();
	//KEY_Init();
	
 // len=USART_RX_STA&0x3fff;
	//for( t=0;t < 10;t++)
			//USART_RX_BUF[t]=data;
		while(1);
	//{		
			 // for(t=0;t<10;t++)
			// {
				 
			//	USART_SendData(USART1,data2[t]);
				
				//USART_SendData(USART1,USART_RX_BUF[t]);
				  //printf("%d ",USART_RX_BUF[t]);
//				  if(USART_RX_BUF[t]==0xaa)   //»º´æÇøÀïµÄÖµ£¿£¿£¿·¢ËÍµÄ
//					{
//				  LED1=0;
//         				
//				 delay_ms(500); 
//			 }
				//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	
	
	 //}

// }
}




#include <stm32f10x.h>
#include "stdio.h"
#include <led.h>
#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
//#include <beep.h> //stm32minÎÞ·äÃùÆ÷
#include <exti.h>
//#include <iwdg.h> 
#include <wwdg.h> 
//#include <malloc.h> 

u8 data1;

int main()
{
	u8 a=0;
	u8 b=1;
	u16 t;
	u16 len;
	u16 times;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	LED_Init();
	//KEY_Init();
	 while(1)
	 {
		 
//		 if(data1!=0xff)
//		{
//			if(data1==0xA1)
//		{
//			LED0=!LED0;
//		}else if(data1==0xA2)
//		{LED1=!LED1;}
//			
//			data1=0xff;
//		}
//}
		 if(USART_RX_STA&0x8000)
		 {
			 len=USART_RX_STA&0x3fff;
			 printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:£\\n");
			 for(t=0;t<len;t++)
			 {
				
				USART_SendData(USART1,USART_RX_BUF[t]);
				  if(USART_RX_BUF[t]==0x30)   //»º´æÇøÀïµÄÖµ£¿£¿£¿·¢ËÍµÄ
					{
				  LED1=0;
         				
				 delay_ms(500); 
					}else if(USART_RX_BUF[t]==0x31)
					{  LED1=1;	}
				 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	
				 
				 
			 }
			 
			 printf("\r\n");
			 USART_RX_STA=0;
		 }else
		 {
	     times++;
//			if(times%5000==0)
//			{
//				printf("\r\n hello\n");
//				//printf("ÕýµãÔ­×Ó\r\n");	
//	
//			}		
			if(times%200==0) printf("ÇëÊäÈëÊý¾Ý:\r\n");
     		//if(times%30==0) LED0=!LED0;
			delay_ms(10);
		}
	 }
 }



  //extern unsigned int TxBuffer1[10];
	//void USART_SendChar();
 //extern unsigned int RxBuffer1[10];
//void USART_Config(USART_TypeDef* USARTx)
//{
//	
//	 USART_InitTypeDef USART_InitStrue;
//   // µÚÈý²½ ³õÊ¼»¯´®¿ÚÏà¹Ø²ÎÊý  
//	USART_InitStrue.USART_BaudRate=115200; //²¨ÌØÂÊ115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //²»ÉèÖÃÓ²¼þ¿ØÖÆÁ÷
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //·¢ËÍÊ¹ÄÜ»ò½ÓÊÕÊ¹ÄÜ»òÁ½Õß¶¼Ê¹ÄÜ
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //ÉèÖÃÍ£Ö¹Î»Îª1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //²»ÉèÖÃÆæÅ¼Ð£Ñé
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //×Ö³¤ÉèÖÃÎª8 ¾ßÌå²»ÖªµÀ¸ÉÊ²Ã´µÄ£¿
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrueÖ¸ÏòUSART1µÄµØÖ·£¿£¿
////Ê¹ÄÜ´®¿Úº¯Êý 
//	USART_Cmd(USART1,ENABLE);//Ê¹ÄÜÁË´®¿Ú1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

//}
//void GPIO_config()
//{
//   GPIO_InitTypeDef GPIO_InitStrue;
//   // µÚ¶þ ²½   A9³õÊ¼»¯IO¿Ú Ä£Ê½ ²é±íµÃµ½ 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   ÉèÖÃÎª  ¸´ÓÃÍÆÍìÊä³ö£¬ÎªÊ²Ã´ GPIO_Mode_AF_PP = 0x18 £¿
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //ÉèÖÃ9ÎªÊä³öÒý½Å
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10³õÊ¼»¯ 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  ÉèÖÃÎª      ¸¡¿ÕÊäÈë
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //ÉèÖÃ10ÎªÊä³öÒý½Å
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);

//}
//void RCC_Configuration()
//{
//	//System_Init();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //µÚÒ»²½ Ê¹ÄÜÊ±ÖÓRCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//}

//void NVIC_Configuration()
//{
//	NVIC_InitTypeDef NVIC_InitStrue;
//	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //ÉèÖÃÍ¨µÀ´®¿Ú1Î»£USART1_IRQn ÔÚstm32f10x.hÍ·ÎÄ¼þÖÐ
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //Ê¹ÄÜÍ¨µÀ
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //ÉèÖÃÓÅÏÈ¼¶ ÕâÀï 0-3 £¬Ëæ±ãÉèÖÃÎª2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //×ÓÓÅÏÈ¼¶Ã»ÓÐËæ±ãÉèÖÃÎª1
//  NVIC_Init(&NVIC_InitStrue);            //ÉèÖÃÏàÓ¦ÖÐ¶ÏÏìÓ¦¡¢ÇÀÕ¼ÓÅÏÈ¼¶

//}
//void USART_SendChar(USART_TypeDef* USARTx,uint8_t data){
//    USART_SendData(USARTx,data);
//	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
//		}

//int main(void)
//{
//	//int len;
//	int rec_f;
//	unsigned int  TxBuffer1[10];
//	//TxBuffer1 = (int *)malloc(5*len);
//	uint8_t a=0;//
//	delay_init();     //³õÊ¼»¯ÑÓÊ±º¯Êý
//	LED_Init();        //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
//  RCC_Configuration();
//	NVIC_Configuration();
//	GPIO_config();
//	USART_Config(USART1);
//	USART_SendChar(USART1,10);
//	
//	while(1)
//	{
//		if(rec_f==1)
//			{
//				rec_f=0;
//				for(  unsigned int i=0;i<sizeof(TxBuffer1);i++)
//				{
//					USART_SendChar(USART1,TxBuffer1[i]);
//				   delay_ms(0xff00);
//				}
//				if(a==0){GPIO_SetBits(GPIOB, GPIO_Pin_5);a=1;}
//				 else{GPIO_ResetBits(GPIOB, GPIO_Pin_5);a=0;}
//			
//		}	
//	}
//}

//    
//		
//		void USART1_IRQHandler(void)      //??1 ??????
//{
//  unsigned int i;
//	unsigned int RxBuffer1[10];
//		unsigned int TxBuffer1[10];
//	unsigned int RxCounter1;
//	unsigned int rec_f;
//	unsigned int TxCounter1;
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)       //??????????
//  {    
//    RxBuffer1[RxCounter1++] = USART_ReceiveData(USART1);   //?????????????????
//    if(RxBuffer1[RxCounter1-2]==0x0d&&RxBuffer1[RxCounter1-1]==0x0a)//?????????0x0d 0x0a
//    {
//      for(i=0; i< RxCounter1; i++) TxBuffer1[i]    = RxBuffer1[i]; //????????????????,????
//      rec_f=1;                                        //??????
//      TxBuffer1[RxCounter1]=0;                                  //????????    
//      TxCounter1=RxCounter1;
//      RxCounter1=0;
//    }
//  }
//  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)  //???????STM32 USART ??????????BUG 
//  { 
//     USART_ITConfig(USART1, USART_IT_TXE, DISABLE);    //?????????, 
//  }     
//}





//void My_USART1_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStrue;//ÉùÃ÷GPIO£¿
//	USART_InitTypeDef USART_InitStrue;
//	NVIC_InitTypeDef NVIC_InitStrue;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //µÚÒ»²½ Ê¹ÄÜÊ±ÖÓRCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

//	// µÚ¶þ ²½   A9³õÊ¼»¯IO¿Ú Ä£Ê½ ²é±íµÃµ½ 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   ÉèÖÃÎª  ¸´ÓÃÍÆÍìÊä³ö£¬ÎªÊ²Ã´ GPIO_Mode_AF_PP = 0x18 £¿
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //ÉèÖÃ9ÎªÊä³öÒý½Å
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10³õÊ¼»¯ 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  ÉèÖÃÎª      ¸¡¿ÕÊäÈë
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //ÉèÖÃ10ÎªÊä³öÒý½Å
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	// µÚÈý²½ ³õÊ¼»¯´®¿ÚÏà¹Ø²ÎÊý  
//	USART_InitStrue.USART_BaudRate=115200; //²¨ÌØÂÊ115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //²»ÉèÖÃÓ²¼þ¿ØÖÆÁ÷
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //·¢ËÍÊ¹ÄÜ»ò½ÓÊÕÊ¹ÄÜ»òÁ½Õß¶¼Ê¹ÄÜ
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //ÉèÖÃÍ£Ö¹Î»Îª1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //²»ÉèÖÃÆæÅ¼Ð£Ñé
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //×Ö³¤ÉèÖÃÎª8 ¾ßÌå²»ÖªµÀ¸ÉÊ²Ã´µÄ£¿
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrueÖ¸ÏòUSART1µÄµØÖ·£¿£¿
////Ê¹ÄÜ´®¿Úº¯Êý 
//	USART_Cmd(USART1,ENABLE);//Ê¹ÄÜÁË´®¿Ú1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //¿ªÆôÁË½ÓÊÕÖÕ¶Ë //´®¿Ú1Ö´ÐÐÖÐ¶Ï£¬½ÓÊÕ»º³åÇø·Ç¿Õ£¬Ê¹ÄÜ¡£½ÓÊÕµ½Êý¾Ý     ¾Í»áÖ´ÐÐÖÐ¶Ï·þÎñº¯Êý 
// // ÖÕ¶ËÓÅÏÈ¼¶µÄÉèÖÃ         
//  NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //ÉèÖÃÍ¨µÀ´®¿Ú1Î»£USART1_IRQn ÔÚstm32f10x.hÍ·ÎÄ¼þÖÐ
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //Ê¹ÄÜÍ¨µÀ
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //ÉèÖÃÓÅÏÈ¼¶ ÕâÀï 0-3 £¬Ëæ±ãÉèÖÃÎª2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //×ÓÓÅÏÈ¼¶Ã»ÓÐËæ±ãÉèÖÃÎª1
//  NVIC_Init(&NVIC_InitStrue);            //ÉèÖÃÏàÓ¦ÖÐ¶ÏÏìÓ¦¡¢ÇÀÕ¼ÓÅÏÈ¼¶

//}

////½ÓÊÕÖÕ¶Ë·þÎñº¯Êý 
//void USART1_IRQHandler(void)   
//{
//	u8 res;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))   //´®¿Ú1£¬×´Ì¬½ÓÊÕ»º³åÇø·Ç¿Õ
//	{
//		res=USART_ReceiveData(USART1);
//	  USART_SendData(USART1,res);		

//	}
//	
//}






//int main(void)
//{
//	delay_init();     //³õÊ¼»¯ÑÓÊ±º¯Êý
//	
//	//ÉèÖÃÖÐ¶ÏÓÅÏÈ¼¶
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //Á½Î»µÄÏìÓ¦ÓÅÏÈ¼¶ºÍÁ½Î»ÇÀÕ¼ÓÅÏÈ¼¶
//  My_USART1_Init();
//	//uart_init(115200); //´®¿Ú³õÊ¼»¯115200
//	LED_Init();        //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
//	//BEEP_Init();       //³õÊ¼»¯Óë·äÃùÆ÷¶Ë¿Ú
//	//KEY_Init();       //³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
//	//EXTIX_Init();      //Íâ²¿ÖÐ¶Ï³õÊ¼»¯
//	LED0=1; 
//}


























/*

//7.´°¿Ú¿´ÃÅ¹· //³ÌÐòÓÐÎÊÌâÎ´ÄÜÊµÏÖ¹¦ÄÜ
int main(void)
{
  delay_init();
	//KEY_Init();
	LED_Init();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //??
	uart_init(115200);	
	LED0=0;

  //WWDG_Set_Counter(u8 cnt);
  
	delay_ms(300);
	WWDG_Init(0x7F,0x5F,WWDG_Prescaler_8 );//¼ÆËãÆ÷Îª7f£¬´°¿Ú¼Ä´æÆ÷Îª5f,·ÖÆµÊýÎª8
	WWDG_NVIC_Init();
	
	while(1)
	{
		//if(KEY_Scan(0)==WKUP_PRES)
		//{  WWDG_Set_Counter(u8 cnt);}
		LED0=1;
	}

}
*/







/*

//6.¶ÀÁ¢¿´ÃÅ¹·ÊµÑé
int main(void)
{
	delay_init();
	KEY_Init();
	LED_Init();
	
	delay_ms(200);
	
	LED0=0;
	IWDG_Init(4,625);//1s
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)
		{IWDG_ReloadCounter();}
	
	}
	
}
*/






//5.´®¿ÚÍ¨ÐÅ remove usart.c ×÷Õß×Ô¼ºÐ´µÄ  ´®¿Úº¯Êý


/*
//4.ÖÐ¶ÏÊµÑé  //Éè¶¨¼Ä´æÆ÷¹¤×÷ Ê± Óëcpu¶ÀÁ¢£¿  £¬ÉèÖÃÖÐ¶ÏÍ¨Öªcpu¹¤×÷½áÊø»òÌáÐÑµÈ

int main(void)
{
	delay_init();     //³õÊ¼»¯ÑÓÊ±º¯Êý
	
	//ÉèÖÃÖÐ¶ÏÓÅÏÈ¼¶
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //Á½Î»µÄÏìÓ¦ÓÅÏÈ¼¶ºÍÁ½Î»ÇÀÕ¼ÓÅÏÈ¼¶
  //My_USART1_Init();
	uart_init(115200); //´®¿Ú³õÊ¼»¯115200
	LED_Init();        //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	//BEEP_Init();       //³õÊ¼»¯Óë·äÃùÆ÷¶Ë¿Ú
	KEY_Init();       //³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	EXTIX_Init();      //Íâ²¿ÖÐ¶Ï³õÊ¼»¯
	LED0=1;               //µãÁÁLED0
	//BEEP=1;
	LED1=1;
	//EXTI9_5_IRQHandler();
	while (1)
	{
		printf("helloword\r\n");
		delay_ms(5000);
	}		
}
*/
/*
//3.u8 Êý¾ÝÀàÐÍ ´æ´¢·¶Î§Îª 0-255
int main(void)
{
	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LED_Init();  
	LED0=0;
	uart_init(115200);
	while(1)
	{
		printf("t:%d\r\n",t);
		delay_ms(100);
	  t++;
	}

}
 */








/* 
//2.°´¼üÊäÈëÊµÑé-GPIO×öÊäÈë
int main(void)
{
	
	u8 t=0;
	KEY_Init();//³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	delay_init();//ÑÓÊ±º¯Êý³õÊ¼»¯
	LED_Init(); //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
  LED0 = 0;    //µãÁÁLED
	while(1)
	{
		t=KEY_Scan(1);//µÃµ½¼üÖµ
			switch(t)
			{
				case KEY0_PRES:// 
				LED0=!LED0;
				break;
				case KEY1_PRES:// 
				LED1=!LED1;
				break;
				case WKUP_PRES://
					LED0=!LED0;
				LED1=!LED1;
				break;	
        default:delay_ms(10);		
			}
		
		}
		
	}

	
	//ledÎ»²Ù×÷
	delay_init();
	LED_Init();
	
	while(1)
	{
		GPIOA->ODR|=1<<8;
		GPIOD->ODR|=1<<2;
		delay_ms(500);
		GPIOA->ODR&=~(1<<8);
		GPIOD->ODR&=~(1<<2);
	delay_ms(500);
	
	}*/





/*
//1.led ÅÜÂíµÆ
int main(void)
{
	
	delay_init();
	LED_Init();
	
	
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_2); //ÉèÖÃGPIOD2Êä³öÎª1£¬µÈÍ¬ÓÚLED0=1
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		delay_ms(500);
		
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);//ÉèÖÃGPIOA8 Êä³öÎª0£¬µÈÍ¬ÓÚLED0=0
	delay_ms(500);
	
	
	}
}
*/