//SysTick?¡§¨º¡À?¡Â-?¨¦DD
#include <led.h>
#include <stm32f10x.h>
#include <sys.h>
//***************************************************************** 
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
//Info:½ÓÊÜLora Êı¾İÖ¡¡¢·Ö¸îÌáÈ¡Êı¾İ¡¢¿ØÖÆLED¡¢ÊıÂë¹Üµ¹¼ÆÊ±
//LED1:PB5-PB7
//ÊıÂë¹Ü£ºPA5-PA7
//Èí¼şÉè¼Æ¿ò¼Ü£º ½ÓÊÜÊı¾İÓë Value ÔËËã¿ÉµÃµ½ µ¹¼ÆÊ±Ê±¼ä¡¢ÁÁµÆĞÅÏ¢¡£

//Function:ÖÇÄÜ½»Í¨µÆÏÔÊ¾Ä£¿é
//Env:Stm32f103x, 74Hc595£¬Keil
//Author@New
//Tmie£º20180919
//INfo:
//IO¶¨Òå:LED1-3:PB5-PB7£¬LED4-6£ºPB8-PB10
//74Hc595:PA6-PA8¡¢LOAD0 PAout(8)¡¢CLK PAout(6)¡¢SDK PAout(7)
//ps:74Hc595 LoADÎ» Ãû×Ö¶¨ÒåÓëSysTick->LOAD ÖØ¸´£¬¹Ê¸ÄÎªLOAD0
//Load0:Ëø´æÆ÷£¬CLK£ºÒÆÎ»Ê±ÖÓ £¬ SDK£ºÊı¾İÎ»
//CLK = 0;µÍµçÆ½£¬Êı¾İÎ» SDK ÊäÈëÊı¾İ¼Ä´æÆ÷£¬CLK=1;ÉÏÉıÑØ½«ÒÑÒÆÈëÊı¾İ¼Ä´æÆ÷Êı¾İËÍÈëËø´æÆ÷
//SysTick ÅäÖÃ²Î¼û£ºhttps://blog.csdn.net/qq_40025335/article/details/79122244
//20180928£º2¸ö½»Í¨µÆ LED1¡¢LED2¡¢±íÊ¾Ö±ĞĞ¡¢ÓÒ×ª¡¢×ó×ª¡
//½ÓÊÜLoraÊı¾İ¡¢¶ÁÈ¡Êı¾İÖ¡ÄÚÈİ¡¢eg: ÏàÎ»ĞÅÏ¢£º01;Í¨ĞĞÊ±¼ä£¨ÁÁÂÌµÆ£©£ºtime;
//¢LED1ÁÁÂÌµÆ ¿ªÊ¼µ¹¼ÆÊ± £ºÖ±ĞĞ¡¢ÓÒ×ª£»Í¬Ê± LED2ÁÁºìµÆ¡¢½ûÖ¹×ó×ª
//LED1£ºPA1¡¢PA5¡¢ £LLED2£    pc4\pc11º
//20180928 Running OK! Finish,
//¡Á??¡ê
  unsigned char Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
	//0 1 2 3 4 5 6 7 8 9 A B C D F ? . //  ?????

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
		
				//LED2 ÁÁºìµÆ£¬½ûÖ¹×ó×ª
				//GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PA5
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED2\Red\PC4
					//LED1 ÂÌµÆÁÁ¡¢Ö±ĞĞ¡¢ÓÒ×ª£»µ¹¼ÆÊ± loraTime
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
				//LED2  ÁÁÂÌµÆ £»  ×ó×ª£»µ¹¼ÆÊ±
					GPIO_ResetBits(GPIOC,GPIO_Pin_11);//LED2¡¢PC11¡¢Green
				//GPIO_ResetBits(GPIOA,GPIO_Pin_5); //PA5
				//GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED1\Red\PC4
					//LED1 ÁÁºìµÆ,½ûÖ¹Ö±ĞĞ¡¢ÓÒ×ª£»
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					//µ¹¼ÆÊ±
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
						//LED1¡¢LED2 ¾ùÁÁºìµÆ
						//½ûÖ¹ Ö±ĞĞ¡¢ÓÒ×ª¡¢×ó×ª£¬ÊıÂë¹ÜÏÔÊ¾99
						//LED1 ÁÁºìµÆ,½ûÖ¹Ö±ĞĞ¡¢ÓÒ×ª£»
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
										//LED2 ÁÁºìµÆ£¬½ûÖ¹×ó×ª
					GPIO_ResetBits(GPIOC,GPIO_Pin_4);//LED2\Red\PC4
						//ÊıÂë¹ÜÏÔÊ¾99
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
