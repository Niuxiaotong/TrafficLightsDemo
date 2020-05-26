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
//Env:Stm32f103x, 74Hc595
//Author@New
//Tmie￡o20180915
//INfo:
//IO?¨ò?:LED1-3:PB5-PB7
//74Hc595:PA5-PA7?￠LOAD0 PAout(5)?￠CLK PAout(6)?￠SDK PAout(7)
//ps:74Hc595 LoAD?? ??×??¨ò?ó?SysTick->LOAD ???′￡?1ê???aLOAD0
//Load0:??′??÷￡?CLK￡oò???ê±?ó ￡? SDK￡oêy?Y??
//CLK = 0;μíμ???￡?êy?Y?? SDK ê?è?êy?Y??′??÷￡?CLK=1;é?éy????ò?ò?è?êy?Y??′??÷êy?Y?íè???′??÷
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
	 	 int j,k;
	//delay_init();	    	 //?óê±oˉêy3?ê??ˉ	  
	SystemInit();    //??(??)??? 
 //GPIO_Init()(); //GPIO??? 
	LED_Init();
  SysTick_Configuration(); //??systick??? 
	while(1)
	{
				//Yelio
		GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8ê?3?μí
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ê?3?μí
		//Green
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ê?3? μí
		/*//Test03?oμ1??ê±??ê:?o??ê?ê±??'ó0- 99
		*/
		
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
		} 
                                                                              
  } 
} 
