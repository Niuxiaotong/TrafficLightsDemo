#include <key.h>
#include <delay.h>

void KEY_Init(void) //IO初始化 为输入
{
	GPIO_InitTypeDef GPIO_InitStructure;//GPIO_InitStrcture指向	GPIO_InitTypeDef 的地址�

//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTC时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试？？？？
	
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置为上拉 �
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; ///PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置为上拉输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);//初始化GPIOC5

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//设置为	下拉输入
  GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.0 
	
}

////////////按键和引脚PA0，PA15，PC5之间的电平信息怎么传送？？->在key.h中用宏定义他们之间关系。按下键key0，电平变化传给那个变量??
///-》key0直接和引脚PC5相连，安下key0，也就是PC5的电平发生了改变
/////按键处理函数
/////返回按键值
////mode=0,不支持连续，1，支持连续

u8 KEY_Scan(u8 mode)    
{
	//u8 key_up=1;
	static u8 key_up=1;//按键按松开标志->使用静态变量，不释放存储空间
	if(mode) key_up=1;//支持连续  ？？？连续什么,还有key_up什么作用？？？(没有弄懂不支持和支持连续按的区别)
	if(key_up&&(KEY0 == 0||KEY1==0||WK_UP==1))  //什么意思？->初试化设置key0,1位上拉即为高电平，wk_up为下拉即为低电平，若key=0则说明key0被按下
	{
		delay_ms(10);//去抖动
		key_up=0;
	if(KEY0==0)return KEY0_PRES; //#define KEY0_PRES 1//那是起到按键后返回值的作用？？？
  else if(KEY1==0)	return KEY1_PRES;
	else if(WK_UP==1)	return WKUP_PRES;	
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1;
	return 0;//无按键按�
}/*
u8 KEY_Scan(u8 mode)  //支持连续
{
	 // static u8 key_up=1;
	//if(mode) key_up =1;
   u8 key_up=1;
	if( key_up &&(KEY0==0 || KEY1==0 || WK_UP==1))
	{
		delay_ms(10);
		//key_up=0;
		if (KEY0==0) return KEY0_PRES;
		else if (KEY1==0) return KEY1_PRES;
		else if (WK_UP==1) return WKUP_PRES;
	}
		return 0;


}*/
/*
u8 KEY_Scan(u8 mode)  //不支持连续
{
	  static u8 key_up=1;
	//if(mode) key_up =1;
	//u8 key_up=1;
	if(key_up && (KEY0==0 || KEY1==0 || WK_UP==1))
	{
		delay_ms(10);//延时防抖
		key_up=0;
		if (KEY0==0) return KEY0_PRES;
		else if (KEY1==0) return KEY1_PRES;
		else if (WK_UP==1) return WKUP_PRES;
	} 
	  else if (KEY0==1 || KEY1==1 || WK_UP==0) key_up=1;
		return 0;
}
*/