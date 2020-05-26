//SysTick��ʱ��-����
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

//��ģ
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//�ӳٺ��� ����
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
//8λ���� ��������595
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
//SysTick ��ʱ����ʱ
//���� systick �Ĵ��� 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick ��ǰ�Ĵ�����ֵ
	 //SysTick �Զ���װ��ֵ�Ĵ���
	 SysTick->LOAD = (72000000/8000000)*1000;//����ÿ��ms��Ҫ��9000��systickʱ���� �
	 SysTick->CTRL |= 0x06; //SysTick ���ƺ�״̬�Ĵ���

 } 
//�жϴ����� 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick ��ʱ����
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // ������ã�����
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //������������ʼ��
	 int j,k;
	 //����Lora����֡��������Valueֵ������ʱʱ��Loratime
	 //����ֵ
	 int Value = 0;//Value = LoraData[];//Value = 0,�������Value=1���̵���
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // ��ѭ��
	while(1)
	{
		//Lora����ģ��
		//1��������ϢValue��0 1 2
		//2������ʱʱ��
		
		
		//LEDģ��
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8�?3?��
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?��
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? ��
		/*//Test03?o�1??�??�:?o??�?�??'�0- 99
		*/
		//�����������ʱ������99,�̵����������ݿ�ʼ����ʱ
		//Value = 0,�������Value=1���̵���
		
		if(Value == 0)
			{
				//�̵���
				GPIO_SetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? ��	
				//Red 
			GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?��
		 //��ʾһ��ʱ���ִ�����ʾ����--������ʾ
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//�������ʾ99�� �������ʱ����ô�涨��
				//LedTime = LedTime*10000;
			Delay(50000); //5S  ģ��������ʱ��	
			Value = ~Value;
			}
		else if(Value == 1)
				{		
					//Value:01\�ҡ��У��̵�  ����ʱ���� ����� ����ʱ��ʾ99
					//�����
					GPIO_SetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?��
					//Green
					GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? ��	
					//����ʱģ��,j����ֵLoraTime������Ϊj=9����ֵ
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
				else if(Value == 2)
				{
					
				
				
				
				
				
				
				
				
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