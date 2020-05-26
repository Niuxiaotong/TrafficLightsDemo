//SysTick?������?��-?��DD
#include <led.h>
#include <stm32f10x.h>
#include <sys.h>
//***************************************************************** 
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
//20180928 Running OK! Finish,
//��??��
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????

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
  //Lora

int main() 
 {
	 // 
	 int j,k;
	 // Loratime
	 int Value = 3;//Value = LoraData[];//Value = 0;loraTime
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // 
	 //GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	// GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	 
	while(1)
	{
		
		if(Value==1)
			{
		
				//LED2 ����ƣ���ֹ��ת
				//GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PA5
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED2\Red\PC4
					//LED1 �̵�����ֱ�С���ת������ʱ loraTime
				//Green
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);//LED1\Green\ PA1	

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

			}
		else if(Value==2) 
				{		
				//LED2  ���̵� ��  ��ת������ʱ
					GPIO_ResetBits(GPIOC,GPIO_Pin_11);//LED2��PC11��Green
				//GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PA5
				//GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED1\Red\PC4
					//LED1 �����,��ֱֹ�С���ת��
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					//����ʱ
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
				
				}	
				else if(Value == 3 || Value == 4)
				{
						//LED1��LED2 �������
						//��ֹ ֱ�С���ת����ת���������ʾ99
						//LED1 �����,��ֱֹ�С���ת��
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
										//LED2 ����ƣ���ֹ��ת
					GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED2\Red\PC4
						//�������ʾ99
					SPI_595(Tab[9]);//LED2-Right
					SPI_595(Tab[9]);//LED1-Left
					LOAD0=1;
					LOAD0=0;	
					SPI_595(Tab[9]);//LED2-Right
					SPI_595(Tab[9]);//LED1-Left
					LOAD0=1;
					LOAD0=0;							
				
				}
                                                                              
  } 
} 
