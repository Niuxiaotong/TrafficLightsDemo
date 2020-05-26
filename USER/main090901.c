//SysTick¶¨Ê±Æ÷-¿ÉÐÐ
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

//×ÖÄ£
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????
	/*
//ÑÓ³Ùº¯Êý ²âÊÔ
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
//8Î»Êý¾Ý ´®ÐÐÊäÈë595
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
//SysTick ¶¨Ê±Æ÷¼ÆÊ±
//ÅäÖÃ systick ¼Ä´æÆ÷ 
void SysTick_Configuration(void) 
{ 
	 SysTick->VAL = 0; //SysTick µ±Ç°¼Ä´æÆ÷µÄÖµ
	 //SysTick ×Ô¶¯ÖØ×°³ýÖµ¼Ä´æÆ÷
	 SysTick->LOAD = (72000000/8000000)*1000;//´ú±íÃ¿¸ömsÐèÒªµÄ9000¸ösystickÊ±ÖÓÊý ¡
	 SysTick->CTRL |= 0x06; //SysTick ¿ØÖÆºÍ×´Ì¬¼Ä´æÆ÷

 } 
//ÖÐ¶Ï´¦Àíº¯Êý 
void SysTick_Handler(void) //???? 
{ 
extern unsigned long TimingDelay; // ????,????????? 
//SYSTICK_CURRENT=0; 
	 SysTick->VAL = 0; 
if (TimingDelay != 0x00) 
TimingDelay--; 
} 
//systick ÑÓÊ±º¯Êý
unsigned long TimingDelay;  // ????,????????? 
void Delay(unsigned long nTime)  //???? 
{ 
SysTick->CTRL |=0x07;   // ??SysTick??? 
TimingDelay = nTime; // ?????? 
while(TimingDelay != 0); // Óï¾ä×÷ÓÃ£¿£¿£¿
SysTick->CTRL |=0x06;// ??SysTick??? 
} 
  

int main() 
 {
	 //±äÁ¿ÉùÃ÷¼°³õÊ¼»¯
	 int j,k;
	 //½ÓÊÜLoraÊý¾ÝÖ¡£¬½âÎö³öValueÖµ¼°µ¹¼ÆÊ±Ê±¼äLoratime
	 //²âÊÔÖµ
	 int Value = 0;//Value = LoraData[];//Value = 0,ºìµÆÁÁ£¬Value=1£¬ÂÌµÆÁÁ
	
	SystemInit();    //

	LED_Init();
  SysTick_Configuration(); //
	 // ËÀÑ­»·
	while(1)
	{
		//Lora½ÓÊÕÄ£¿é
		//1¡¢ÁÁµÈÐÅÏ¢Value£¬0 1 2
		//2¡¢µ¹¼ÆÊ±Ê±³¤
		
		
		//LEDÄ£¿é
				//Yelio
		//GPIO_ResetBits(GPIOB,GPIO_Pin_5); //PA8ê?3?µí
		//DSP1
	//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//
		//Red
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ê?3?µí
		//Green
		//GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ê?3? µí
		/*//Test03?oµ1??ê±??ê:?o??ê?ê±??'ó0- 99
		*/
		//ºìµÆÁÁ£¬µ¹¼ÆÊ±¶¨¸öÔÚ99,ÂÌµÆÁÁ½ÓÊÜÊý¾Ý¿ªÊ¼µ¹¼ÆÊ±
		//Value = 0,ºìµÆÁÁ£¬Value=1£¬ÂÌµÆÁÁ
		
		if(Value == 0)
			{
				//ÂÌµÆÃð
				GPIO_SetBits(GPIOB,GPIO_Pin_7);//PB7 ê?3? µí	
				//Red 
			GPIO_ResetBits(GPIOB,GPIO_Pin_6); //PB6 ê?3?µí
		 //ÏÔÊ¾Ò»´ÎÊ±³öÏÖ´íÎó£¬ÏÔÊ¾Á½´Î--Õý³£ÏÔÊ¾
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;	
			SPI_595(Tab[9]);//LED2-Right
			SPI_595(Tab[9]);//LED1-Left
			LOAD0=1;
			LOAD0=0;
				//ÊýÂë¹ÜÏÔÊ¾99£¬ ºìµÆÁÁ£¬Ê±¼äÔõÃ´¹æ¶¨£¿
				//LedTime = LedTime*10000;
			Delay(50000); //5S  Ä£ÄâºìµÆÁÁµÈÊ±¼ä	
			Value = ~Value;
			}
		else if(Value == 1)
				{		
					//Value:01\ÓÒ¡¢ÖÐ£¬ÂÌµÆ  µ¹¼ÆÊ±¡¢×ó ºìµÆÁÁ µ¹¼ÆÊ±ÏÔÊ¾99
					//ºìµÆÃð
					GPIO_SetBits(GPIOB,GPIO_Pin_6); //PB6 ê?3?µí
					//Green
					GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 ê?3? µí	
					//µ¹¼ÆÊ±Ä£¿é,j£¬³õÖµLoraTime£¬ÕâÀïÎªj=9²âÊÔÖµ
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