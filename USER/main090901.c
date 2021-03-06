//SysTick定时器-可行
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

//字模
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//延迟函数 测试
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
//8位数据 串行输入595
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
//SysTick 定时器计时
//配置 systick 寄存器 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick 当前寄存器的值
	 //SysTick 自动重装除值寄存器
	 SysTick->LOAD = (72000000/8000000)*1000;//代表每个ms需要的9000个systick时钟数 �
	 SysTick->CTRL |= 0x06; //SysTick 控制和状态寄存器

 } 
//中断处理函数 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick 延时函数
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // 语句作用？？？
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //变量声明及初始化
	 int j,k;
	 //接受Lora数据帧，解析出Value值及倒计时时间Loratime
	 //测试值
	 int Value = 0;//Value = LoraData[];//Value = 0,红灯亮，Value=1，绿灯亮
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // 死循环
	while(1)
	{
		//Lora接收模块
		//1、亮等信息Value，0 1 2
		//2、倒计时时长
		
		
		//LED模块
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8�?3?淀
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?淀
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? 淀
		/*//Test03?o�1??瓯??�:?o??�?瓯??'�0- 99
		*/
		//红灯亮，倒计时定个在99,绿灯亮接受数据开始倒计时
		//Value = 0,红灯亮，Value=1，绿灯亮
		
		if(Value == 0)
			{
				//绿灯灭
				GPIO_SetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? 淀	
				//Red 
			GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?淀
		 //显示一次时出现错误，显示两次--正常显示
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//数码管显示99， 红灯亮，时间怎么规定？
				//LedTime = LedTime*10000;
			Delay(50000); //5S  模拟红灯亮等时间	
			Value = ~Value;
			}
		else if(Value == 1)
				{		
					//Value:01\右、中，绿灯  倒计时、左 红灯亮 倒计时显示99
					//红灯灭
					GPIO_SetBits(GPIOB,GPIO_Pin_6); //PB6 �?3?淀
					//Green
					GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 �?3? 淀	
					//倒计时模块,j，初值LoraTime，这里为j=9测试值
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