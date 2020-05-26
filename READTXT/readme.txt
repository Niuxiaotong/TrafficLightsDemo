-----------------\
20180928:
//SysTick?������?��-?��DD
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
//Env:Stm32Ff103x?��???�� ??������???��??��?��
//Time:20180907-
//Info:?������Lora ��y?Y???�顤???������?��y?Y?��????LED?�騺y??1����1??����
//LED1:PB5-PB7
//��y??1����oPA5-PA7
//����?t����???��?����o ?��������y?Y��? Value ?????����?��? ��1??��������???�騢����?D??��?��

//Function:???��??������???��??��?��
//Env:Stm32f103x, 74Hc595��?Keil
//Author@New
//Tmie��o20180915
//INfo:
//IO?����?:LED1-3:PB5-PB7
//74Hc595:PA5-PA7?��LOAD0 PAout(5)?��CLK PAout(6)?��SDK PAout(7)
//ps:74Hc595 LoAD?? ??��??����?��?SysTick->LOAD ???���?1��???aLOAD0
//Load0:??��??�¡�?CLK��o��???����?�� ��? SDK��o��y?Y??
//CLK = 0;�̨���???��?��y?Y?? SDK ��?��?��y?Y??��??�¡�?CLK=1;��?��y????��?��?��?��y?Y??��??�¨�y?Y?����???��??��
//SysTick ????2???��ohttps://blog.csdn.net/qq_40025335/article/details/79122244
//info:R-PA6,G-PA7,Y-PA5(DS0)
//Env:Stm32Ff103x������ ��ͨ����ʾģ��
//Time:20180907-
//Info:����Lora ����֡���ָ���ȡ���ݡ�����LED������ܵ���ʱ
//LED1:PB5-PB7
//����ܣ�PA5-PA7
//�����ƿ�ܣ� ���������� Value ����ɵõ� ����ʱʱ�䡢������Ϣ��

//Function:���ܽ�ͨ����ʾģ��
//Env:Stm32f103x, 74Hc595��Keil
//Author@New
//Tmie��20180919
//INfo:
//IO����:LED1-3:PB5-PB7��LED4-6��PB8-PB10
//74Hc595:PA6-PA8��LOAD0 PAout(8)��CLK PAout(6)��SDK PAout(7)
//ps:74Hc595 LoADλ ���ֶ�����SysTick->LOAD �ظ����ʸ�ΪLOAD0
//Load0:��������CLK����λʱ�� �� SDK������λ
//CLK = 0;�͵�ƽ������λ SDK �������ݼĴ�����CLK=1;�����ؽ����������ݼĴ�����������������
//SysTick ���òμ���https://blog.csdn.net/qq_40025335/article/details/79122244
//20180928��2����ͨ�� LED1��LED2����ʾֱ�С���ת����ת�
//����Lora���ݡ���ȡ����֡���ݡ�eg: ��λ��Ϣ��01;ͨ��ʱ�䣨���̵ƣ���time;
//�LED1���̵� ��ʼ����ʱ ��ֱ�С���ת��ͬʱ LED2����ơ���ֹ��ת
//LED1��PA1��PA5�� �LLED2�    pc4\pc11�
  
//��??��
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//?��3��o����y 2a��?
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
//8??��y?Y ��?DD��?��?595
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
//SysTick ?������?��??����
//???? systick ??��??�� 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick �̡�?��??��??�¦�??��
	 //SysTick ��??��??����3y?��??��??��
	 SysTick->LOAD = (72000000/8000000)*1000;//�䨲����????msD����a��?9000??systick����?����y ?
	 SysTick->CTRL |= 0x06; //SysTick ????o�����䨬???��??��

 } 
//?D??��|����o����y 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick ?������o����y
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // ��???���¨�?��?��?��?
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //��?��?����?��?��3?��??��
	 int j,k;
	 //?������Lora��y?Y??��??a??3?Value?��?���1??��������??Loratime
	 //2a��??��
	 int Value = 0;//Value = LoraData[];//Value = 0,o����?������?Value=1��??����?����
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // ?��?-?��
	 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 /*
	  GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_11);*/
	 
	while(1)
	{
		//Lora?����??��?��
		//1?�騢���̨�D??��Value
		//2?���1??��������3��
		
		
		//LED?��?��
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8��?3?�̨�
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ��?3?�̨�
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ��?3? �̨�
		/*//Test03?o��1??����??��:?o??��?����??'��0- 99
		*/
		//o����?������?��1??����?��???��99,?����?����?��������y?Y?a��?��1??����
		//Value = 0,o����?������?Value=1��??����?����
		
		if(~Value)
			{
				//?����??e
				GPIO_SetBits(GPIOA,GPIO_Pin_1);//PB1 LED1
				//Red 
			GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PB5
		 //??��?��?��?����3???�䨪?����???��?��?��?--?y3��??��?
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//��y??1��??��?99��? o����?������?����?????��1??����?
				//LedTime = LedTime*10000;
			Delay(50000); //5S  ?��?ao����?�����̨�����??	
			Value = ~Value;
			}
		else 
				{		
					//o����??e
					GPIO_SetBits(GPIOA,GPIO_Pin_5); //PB6 ��?3?�̨�
					//Green
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PB7 ��?3? �̨�	
					//��1??����?��?��,j��?3??��LoraTime��??a��??aj=92a��??��
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

//SysTick��ʱ��-����
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
//Systick��ʱ��-������
#include <stm32f10x.h>
#include <led.h>
//#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
#include <core_cm3.h>
//#include <beep.h> //stm32min�޷�����
//#include <exti.h>


/*void Delay(u32 nTime)
{
	u32 tmp = nTime;
	//u32 tmp = 
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(SystemCoreClock / 1000);//
}*/
///////@NXT:���жϷ�ʽʵ����ʱ
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

//��λ�����ԣ�
#include <stm32f10x.h>
#include "stdio.h"
#include <led.h>
#include <delay.h>
#include <sys.h>
#include <key.h>
#include <usart.h>
//#include <beep.h> //stm32min�޷�����
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
//				  if(USART_RX_BUF[t]==0xaa)   //���������ֵ���������͵�
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
//#include <beep.h> //stm32min�޷�����
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
			 printf("\r\n�����͵���ϢΪ:�\\n");
			 for(t=0;t<len;t++)
			 {
				
				USART_SendData(USART1,USART_RX_BUF[t]);
				  if(USART_RX_BUF[t]==0x30)   //���������ֵ���������͵�
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
//				//printf("����ԭ��\r\n");	
//	
//			}		
			if(times%200==0) printf("����������:\r\n");
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
//   // ������ ��ʼ��������ز���  
//	USART_InitStrue.USART_BaudRate=115200; //������115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //������Ӳ��������
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //����ʹ�ܻ����ʹ�ܻ����߶�ʹ��
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //����ֹͣλΪ1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //��������żУ��
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //�ֳ�����Ϊ8 ���岻֪����ʲô�ģ�
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrueָ��USART1�ĵ�ַ����
////ʹ�ܴ��ں��� 
//	USART_Cmd(USART1,ENABLE);//ʹ���˴���1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

//}
//void GPIO_config()
//{
//   GPIO_InitTypeDef GPIO_InitStrue;
//   // �ڶ� ��   A9��ʼ��IO�� ģʽ ���õ� 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   ����Ϊ  �������������Ϊʲô GPIO_Mode_AF_PP = 0x18 ��
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //����9Ϊ�������
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10��ʼ�� 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  ����Ϊ      ��������
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //����10Ϊ�������
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);

//}
//void RCC_Configuration()
//{
//	//System_Init();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //��һ�� ʹ��ʱ��RCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//}

//void NVIC_Configuration()
//{
//	NVIC_InitTypeDef NVIC_InitStrue;
//	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //����ͨ������1λ�USART1_IRQn ��stm32f10x.hͷ�ļ���
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //ʹ��ͨ��
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //�������ȼ� ���� 0-3 ���������Ϊ2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //�����ȼ�û���������Ϊ1
//  NVIC_Init(&NVIC_InitStrue);            //������Ӧ�ж���Ӧ����ռ���ȼ�

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
//	delay_init();     //��ʼ����ʱ����
//	LED_Init();        //��ʼ����LED���ӵ�Ӳ���ӿ�
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
//	GPIO_InitTypeDef GPIO_InitStrue;//����GPIO��
//	USART_InitTypeDef USART_InitStrue;
//	NVIC_InitTypeDef NVIC_InitStrue;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //��һ�� ʹ��ʱ��RCC_APB1PeriphClockCmd
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

//	// �ڶ� ��   A9��ʼ��IO�� ģʽ ���õ� 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//USARTx_Tx   ����Ϊ  �������������Ϊʲô GPIO_Mode_AF_PP = 0x18 ��
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9; //����9Ϊ�������
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	//A10��ʼ�� 
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING; //USARTx_Rx  ����Ϊ      ��������
// 	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10; //����10Ϊ�������
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	// ������ ��ʼ��������ز���  
//	USART_InitStrue.USART_BaudRate=115200; //������115200;
//	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //������Ӳ��������
//	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;                         //����ʹ�ܻ����ʹ�ܻ����߶�ʹ��
//	USART_InitStrue.USART_StopBits=USART_StopBits_1; //����ֹͣλΪ1
//	USART_InitStrue.USART_Parity=USART_Parity_No;     //��������żУ��
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b; //�ֳ�����Ϊ8 ���岻֪����ʲô�ģ�
//	
//  USART_Init(USART1,&USART_InitStrue); //USART_InitStrueָ��USART1�ĵ�ַ����
////ʹ�ܴ��ں��� 
//	USART_Cmd(USART1,ENABLE);//ʹ���˴���1
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);  //�����˽����ն� //����1ִ���жϣ����ջ������ǿգ�ʹ�ܡ����յ�����     �ͻ�ִ���жϷ����� 
// // �ն����ȼ�������         
//  NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;   //����ͨ������1λ�USART1_IRQn ��stm32f10x.hͷ�ļ���
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;     //ʹ��ͨ��
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;    //�������ȼ� ���� 0-3 ���������Ϊ2    
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;        //�����ȼ�û���������Ϊ1
//  NVIC_Init(&NVIC_InitStrue);            //������Ӧ�ж���Ӧ����ռ���ȼ�

//}

////�����ն˷����� 
//void USART1_IRQHandler(void)   
//{
//	u8 res;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))   //����1��״̬���ջ������ǿ�
//	{
//		res=USART_ReceiveData(USART1);
//	  USART_SendData(USART1,res);		

//	}
//	
//}






//int main(void)
//{
//	delay_init();     //��ʼ����ʱ����
//	
//	//�����ж����ȼ�
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //��λ����Ӧ���ȼ�����λ��ռ���ȼ�
//  My_USART1_Init();
//	//uart_init(115200); //���ڳ�ʼ��115200
//	LED_Init();        //��ʼ����LED���ӵ�Ӳ���ӿ�
//	//BEEP_Init();       //��ʼ����������˿�
//	//KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
//	//EXTIX_Init();      //�ⲿ�жϳ�ʼ��
//	LED0=1; 
//}


























/*

//7.���ڿ��Ź� //����������δ��ʵ�ֹ���
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
	WWDG_Init(0x7F,0x5F,WWDG_Prescaler_8 );//������Ϊ7f�����ڼĴ���Ϊ5f,��Ƶ��Ϊ8
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

//6.�������Ź�ʵ��
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






//5.����ͨ�� remove usart.c �����Լ�д��  ���ں���


/*
//4.�ж�ʵ��  //�趨�Ĵ������� ʱ ��cpu������  �������ж�֪ͨcpu�������������ѵ�

int main(void)
{
	delay_init();     //��ʼ����ʱ����
	
	//�����ж����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //��λ����Ӧ���ȼ�����λ��ռ���ȼ�
  //My_USART1_Init();
	uart_init(115200); //���ڳ�ʼ��115200
	LED_Init();        //��ʼ����LED���ӵ�Ӳ���ӿ�
	//BEEP_Init();       //��ʼ����������˿�
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	EXTIX_Init();      //�ⲿ�жϳ�ʼ��
	LED0=1;               //����LED0
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
//3.u8 �������� �洢��ΧΪ 0-255
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
//2.��������ʵ��-GPIO������
int main(void)
{
	
	u8 t=0;
	KEY_Init();//��ʼ���밴�����ӵ�Ӳ���ӿ�
	delay_init();//��ʱ������ʼ��
	LED_Init(); //��ʼ����LED���ӵ�Ӳ���ӿ�
  LED0 = 0;    //����LED
	while(1)
	{
		t=KEY_Scan(1);//�õ���ֵ
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

	
	//ledλ����
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
//1.led �����
int main(void)
{
	
	delay_init();
	LED_Init();
	
	
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_2); //����GPIOD2���Ϊ1����ͬ��LED0=1
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		delay_ms(500);
		
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);//����GPIOA8 ���Ϊ0����ͬ��LED0=0
	delay_ms(500);
	
	
	}
}
*/