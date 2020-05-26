#include <key.h>
#include <delay.h>

void KEY_Init(void) //IO³õÊ¼»¯ ÎªÊäÈë
{
	GPIO_InitTypeDef GPIO_InitStructure;//GPIO_InitStrctureÖ¸Ïò	GPIO_InitTypeDef µÄµØÖ·ò

//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//Ê¹ÄÜPORTAÊ±ÖÓ
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//Ê¹ÄÜPORTCÊ±ÖÓ
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//¹Ø±Õjtag£¬Ê¹ÄÜSWD£¬¿ÉÒÔÓÃSWDÄ£Ê½µ÷ÊÔ£¿£¿£¿£¿
	
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//ÉèÖÃÎªÉÏÀ­ À
	GPIO_Init(GPIOA,&GPIO_InitStructure);//³õÊ¼»¯GPIOA15
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; ///PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//ÉèÖÃÎªÉÏÀ­ÊäÈë
	GPIO_Init(GPIOC,&GPIO_InitStructure);//³õÊ¼»¯GPIOC5

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//ÉèÖÃÎª	ÏÂÀ­ÊäÈë
  GPIO_Init(GPIOA,&GPIO_InitStructure);//³õÊ¼»¯GPIOA.0 
	
}

////////////°´¼üºÍÒı½ÅPA0£¬PA15£¬PC5Ö®¼äµÄµçÆ½ĞÅÏ¢ÔõÃ´´«ËÍ£¿£¿->ÔÚkey.hÖĞÓÃºê¶¨ÒåËûÃÇÖ®¼ä¹ØÏµ¡£°´ÏÂ¼ükey0£¬µçÆ½±ä»¯´«¸øÄÇ¸ö±äÁ¿??
///-¡·key0Ö±½ÓºÍÒı½ÅPC5ÏàÁ¬£¬°²ÏÂkey0£¬Ò²¾ÍÊÇPC5µÄµçÆ½·¢ÉúÁË¸Ä±ä
/////°´¼ü´¦Àíº¯Êı
/////·µ»Ø°´¼üÖµ
////mode=0,²»Ö§³ÖÁ¬Ğø£¬1£¬Ö§³ÖÁ¬Ğø

u8 KEY_Scan(u8 mode)    
{
	//u8 key_up=1;
	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾->Ê¹ÓÃ¾²Ì¬±äÁ¿£¬²»ÊÍ·Å´æ´¢¿Õ¼ä
	if(mode) key_up=1;//Ö§³ÖÁ¬Ğø  £¿£¿£¿Á¬ĞøÊ²Ã´,»¹ÓĞkey_upÊ²Ã´×÷ÓÃ£¿£¿£¿(Ã»ÓĞÅª¶®²»Ö§³ÖºÍÖ§³ÖÁ¬Ğø°´µÄÇø±ğ)
	if(key_up&&(KEY0 == 0||KEY1==0||WK_UP==1))  //Ê²Ã´ÒâË¼£¿->³õÊÔ»¯ÉèÖÃkey0,1Î»ÉÏÀ­¼´Îª¸ßµçÆ½£¬wk_upÎªÏÂÀ­¼´ÎªµÍµçÆ½£¬Èôkey=0ÔòËµÃ÷key0±»°´ÏÂ
	{
		delay_ms(10);//È¥¶¶¶¯
		key_up=0;
	if(KEY0==0)return KEY0_PRES; //#define KEY0_PRES 1//ÄÇÊÇÆğµ½°´¼üºó·µ»ØÖµµÄ×÷ÓÃ£¿£¿£¿
  else if(KEY1==0)	return KEY1_PRES;
	else if(WK_UP==1)	return WKUP_PRES;	
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1;
	return 0;//ÎŞ°´¼ü°´Ï
}/*
u8 KEY_Scan(u8 mode)  //Ö§³ÖÁ¬Ğø
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
u8 KEY_Scan(u8 mode)  //²»Ö§³ÖÁ¬Ğø
{
	  static u8 key_up=1;
	//if(mode) key_up =1;
	//u8 key_up=1;
	if(key_up && (KEY0==0 || KEY1==0 || WK_UP==1))
	{
		delay_ms(10);//ÑÓÊ±·À¶¶
		key_up=0;
		if (KEY0==0) return KEY0_PRES;
		else if (KEY1==0) return KEY1_PRES;
		else if (WK_UP==1) return WKUP_PRES;
	} 
	  else if (KEY0==1 || KEY1==1 || WK_UP==0) key_up=1;
		return 0;
}
*/