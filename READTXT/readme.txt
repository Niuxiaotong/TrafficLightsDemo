-----------------\
20180928:
//SysTick?¨ê±?÷-?éDD
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
//Env:Stm32Ff103x?￠???ü ??í¨μ???ê??￡?é
//Time:20180907-
//Info:?óêüLora êy?Y???￠·???ìáè?êy?Y?￠????LED?￠êy??1üμ1??ê±
//LED1:PB5-PB7
//êy??1ü￡oPA5-PA7
//èí?téè???ò?ü￡o ?óêüêy?Yó? Value ?????éμ?μ? μ1??ê±ê±???￠ááμ?D??￠?￡

//Function:???ü??í¨μ???ê??￡?é
//Env:Stm32f103x, 74Hc595￡?Keil
//Author@New
//Tmie￡o20180915
//INfo:
//IO?¨ò?:LED1-3:PB5-PB7
//74Hc595:PA5-PA7?￠LOAD0 PAout(5)?￠CLK PAout(6)?￠SDK PAout(7)
//ps:74Hc595 LoAD?? ??×??¨ò?ó?SysTick->LOAD ???′￡?1ê???aLOAD0
//Load0:??′??÷￡?CLK￡oò???ê±?ó ￡? SDK￡oêy?Y??
//CLK = 0;μíμ???￡?êy?Y?? SDK ê?è?êy?Y??′??÷￡?CLK=1;é?éy????ò?ò?è?êy?Y??′??÷êy?Y?íè???′??÷
//SysTick ????2???￡ohttps://blog.csdn.net/qq_40025335/article/details/79122244
//info:R-PA6,G-PA7,Y-PA5(DS0)
//Env:Stm32Ff103x、智能 交通灯显示模块
//Time:20180907-
//Info:接受Lora 数据帧、分割提取数据、控制LED、数码管倒计时
//LED1:PB5-PB7
//数码管：PA5-PA7
//软件设计框架： 接受数据与 Value 运算可得到 倒计时时间、亮灯信息。

//Function:智能交通灯显示模块
//Env:Stm32f103x, 74Hc595，Keil
//Author@New
//Tmie：20180919
//INfo:
//IO定义:LED1-3:PB5-PB7，LED4-6：PB8-PB10
//74Hc595:PA6-PA8、LOAD0 PAout(8)、CLK PAout(6)、SDK PAout(7)
//ps:74Hc595 LoAD位 名字定义与SysTick->LOAD 重复，故改为LOAD0
//Load0:锁存器，CLK：移位时钟 ， SDK：数据位
//CLK = 0;低电平，数据位 SDK 输入数据寄存器，CLK=1;上升沿将已移入数据寄存器数据送入锁存器
//SysTick 配置参见：https://blog.csdn.net/qq_40025335/article/details/79122244
//20180928：2个交通灯 LED1、LED2、表示直行、右转、左转�
//接受Lora数据、读取数据帧内容、eg: 相位信息：01;通行时间（亮绿灯）：time;
//ED1亮绿灯 开始倒计时 ：直行、右转；同时 LED2亮红灯、禁止左转
//LED1：PA1、PA5、 LED2�    pc4\pc11�
  
//×??￡
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//?ó3ùoˉêy 2aê?
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
//8??êy?Y ′?DDê?è?595
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
//SysTick ?¨ê±?÷??ê±
//???? systick ??′??÷ 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick μ±?°??′??÷μ??μ
	 //SysTick ×??ˉ??×°3y?μ??′??÷
	 SysTick->LOAD = (72000000/8000000)*1000;//′ú±í????msDèòaμ?9000??systickê±?óêy ?
	 SysTick->CTRL |= 0x06; //SysTick ????oí×′ì???′??÷

 } 
//?D??′|àíoˉêy 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick ?óê±oˉêy
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // ó???×÷ó?￡?￡?￡?
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //±?á?éù?÷?°3?ê??ˉ
	 int j,k;
	 //?óêüLoraêy?Y??￡??a??3?Value?μ?°μ1??ê±ê±??Loratime
	 //2aê??μ
	 int Value = 0;//Value = LoraData[];//Value = 0,oìμ?áá￡?Value=1￡??ìμ?áá
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // ?à?-?·
	 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 /*
	  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_11);*/
	 
	while(1)
	{
		//Lora?óê??￡?é
		//1?￠ááμèD??￠Value
		//2?￠μ1??ê±ê±3¤
		
		
		//LED?￡?é
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8ê?3?μí
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ê?3?μí
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ê?3? μí
		/*//Test03?oμ1??ê±??ê:?o??ê?ê±??'ó0- 99
		*/
		//oìμ?áá￡?μ1??ê±?¨???ú99,?ìμ?áá?óêüêy?Y?aê?μ1??ê±
		//Value = 0,oìμ?áá￡?Value=1￡??ìμ?áá
		
		if(~Value)
			{
				//?ìμ??e
				GPIO_SetBits(GPIOA,GPIO_Pin_1);//PB1 LED1
				//Red 
			GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PB5
		 //??ê?ò?′?ê±3???′í?ó￡???ê?á?′?--?y3￡??ê?
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//êy??1ü??ê?99￡? oìμ?áá￡?ê±?????′1??¨￡?
				//LedTime = LedTime*10000;
			Delay(50000); //5S  ?￡?aoìμ?ááμèê±??	
			Value = ~Value;
			}
		else 
				{		
					//oìμ??e
					GPIO_SetBits(GPIOA,GPIO_Pin_5); //PB6 ê?3?μí
					//Green
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB7 ê?3? μí	
					//μ1??ê±?￡?é,j￡?3??μLoraTime￡??aà??aj=92aê??μ
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

//SysTick定时器-可行
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
//Systick定时器-有问题
#include <stm32f10x.h>
#include <led.h>
//#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
#include <core_cm3.h>
//#include <beep.h> //stm32min无蜂鸣器
//#include <exti.h>


/*void Delay(u32 nTime)
{
	u32 tmp = nTime;
	//u32 tmp = 
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//
}*/
///////@NXT:用中断方式实现延时
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

//上位机测试：
#include <stm32f10x.h>
#include "stdio.h"
#include <led.h>
#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
//#include <beep.h> //stm32min无蜂鸣器
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
//				  if(USART_RX_BUF[t]==0xaa)   //缓存区里的值？？？发送的
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
//#include <beep.h> //stm32min无蜂鸣器
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
			 printf("\r\n您发送的消息为:\n");
			 for(t=0;t<len;t++)
			 {
				
				USART_SendData(USART1,USART_RX_BUF[t]);
				  if(USART_RX_BUF[t]==0x30)   //缓存区里的值？？？发送的
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
//				//printf("正点原子\r\n");	
//	
//			}		
			if(times%200==0) printf("请输入数据:\r\n");
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
//   // 第三步 初始化串口相关参数  
//	USART_InitStrue.USART_BaudRate=115200; //波特率115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //不设置硬件控制流
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //发送使能或接收使能或两者都使能
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //设置停止位为1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //不设置奇偶校验
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //字长设置为8 具体不知道干什么的？
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrue指向USART1的地址？？
////使能串口函数 
//	USART_Cmd(USART1,ENABLE);//使能了串口1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

//}
//void GPIO_config()
//{
//   GPIO_InitTypeDef GPIO_InitStrue;
//   // 第二 步   A9初始化IO口 模式 查表得到 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   设置为  复用推挽输出，为什么 GPIO_Mode_AF_PP = 0x18 ？
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //设置9为输出引脚
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10初始化 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  设置为      浮空输入
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //设置10为输出引脚
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);

//}
//void RCC_Configuration()
//{
//	//System_Init();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //第一步 使能时钟RCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//}

//void NVIC_Configuration()
//{
//	NVIC_InitTypeDef NVIC_InitStrue;
//	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //设置通道串口1位SART1_IRQn 在stm32f10x.h头文件中
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //使能通道
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //设置优先级 这里 0-3 ，随便设置为2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //子优先级没有随便设置为1
//  NVIC_Init(&NVIC_InitStrue);            //设置相应中断响应、抢占优先级

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
//	delay_init();     //初始化延时函数
//	LED_Init();        //初始化与LED连接的硬件接口
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
//	GPIO_InitTypeDef GPIO_InitStrue;//声明GPIO？
//	USART_InitTypeDef USART_InitStrue;
//	NVIC_InitTypeDef NVIC_InitStrue;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //第一步 使能时钟RCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

//	// 第二 步   A9初始化IO口 模式 查表得到 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   设置为  复用推挽输出，为什么 GPIO_Mode_AF_PP = 0x18 ？
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //设置9为输出引脚
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10初始化 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  设置为      浮空输入
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //设置10为输出引脚
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	// 第三步 初始化串口相关参数  
//	USART_InitStrue.USART_BaudRate=115200; //波特率115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //不设置硬件控制流
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //发送使能或接收使能或两者都使能
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //设置停止位为1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //不设置奇偶校验
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //字长设置为8 具体不知道干什么的？
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrue指向USART1的地址？？
////使能串口函数 
//	USART_Cmd(USART1,ENABLE);//使能了串口1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //开启了接收终端 //串口1执行中断，接收缓冲区非空，使能。接收到数据     就会执行中断服务函数 
// // 终端优先级的设置         
//  NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //设置通道串口1位SART1_IRQn 在stm32f10x.h头文件中
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //使能通道
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //设置优先级 这里 0-3 ，随便设置为2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //子优先级没有随便设置为1
//  NVIC_Init(&NVIC_InitStrue);            //设置相应中断响应、抢占优先级

//}

////接收终端服务函数 
//void USART1_IRQHandler(void)   
//{
//	u8 res;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))   //串口1，状态接收缓冲区非空
//	{
//		res=USART_ReceiveData(USART1);
//	  USART_SendData(USART1,res);		

//	}
//	
//}






//int main(void)
//{
//	delay_init();     //初始化延时函数
//	
//	//设置中断优先级
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //两位的响应优先级和两位抢占优先级
//  My_USART1_Init();
//	//uart_init(115200); //串口初始化115200
//	LED_Init();        //初始化与LED连接的硬件接口
//	//BEEP_Init();       //初始化与蜂鸣器端口
//	//KEY_Init();       //初始化与按键连接的硬件接口
//	//EXTIX_Init();      //外部中断初始化
//	LED0=1; 
//}


























/*

//7.窗口看门狗 //程序有问题未能实现功能
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
	WWDG_Init(0x7F,0x5F,WWDG_Prescaler_8 );//计算器为7f，窗口寄存器为5f,分频数为8
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

//6.独立看门狗实验
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






//5.串口通信 remove usart.c 作者自己写的  串口函数


/*
//4.中断实验  //设定寄存器工作 时 与cpu独立？  ，设置中断通知cpu工作结束或提醒等

int main(void)
{
	delay_init();     //初始化延时函数
	
	//设置中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //两位的响应优先级和两位抢占优先级
  //My_USART1_Init();
	uart_init(115200); //串口初始化115200
	LED_Init();        //初始化与LED连接的硬件接口
	//BEEP_Init();       //初始化与蜂鸣器端口
	KEY_Init();       //初始化与按键连接的硬件接口
	EXTIX_Init();      //外部中断初始化
	LED0=1;               //点亮LED0
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
//3.u8 数据类型 存储范围为 0-255
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
//2.按键输入实验-GPIO做输入
int main(void)
{
	
	u8 t=0;
	KEY_Init();//初始化与按键连接的硬件接口
	delay_init();//延时函数初始化
	LED_Init(); //初始化与LED连接的硬件接口
  LED0 = 0;    //点亮LED
	while(1)
	{
		t=KEY_Scan(1);//得到键值
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

	
	//led位操作
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
//1.led 跑马灯
int main(void)
{
	
	delay_init();
	LED_Init();
	
	
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_2); //设置GPIOD2输出为1，等同于LED0=1
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		delay_ms(500);
		
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);//设置GPIOA8 输出为0，等同于LED0=0
	delay_ms(500);
	
	
	}
}
*/