#ifndef _KEY_H
#define _KEY_H  //ºê¶¨Òå£¿£¿£¿£¿
#include <sys.h>

//#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//¶ÁÈ¡°´¼ü0 ¸ù¾İµçÂ·Ô­ÀíÍ¼¿ÉÖª£¬stm32°åÉÏkey0ÓëPC 5ÏàÁ¬ Í¨¹ıºê¶¨Òå°ÑPC5µÄÖµ¸³Öµ¸ø£Ë£Å£Ù£°
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//¶ÁÈ¡°´¼ü1   ¸ù¾İµçÂ·Ô­ÀíÍ¼¿ÉÖª£¬stm32°åÉÏkey1ÓëPA15ÏàÁ¬
//#define KEY2 GPIO_ReadIputDataBit(GPIOE,GPIO_Pin4)//¶ÁÈ¡°´2
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//¶ÁÈ¡°´¼ü3£¨WK_UP£©


#define KEY0_PRES 1//KEY0°´ÏÂ£¿£
#define KEY1_PRES 2//KEY1°´ÏÂ
#define WKUP_PRES 3//KEY_UP°´ÏÂ


void KEY_Init(void);  //IO³õÊ¼»¯
u8 KEY_Scan(u8 mode);   //°´¼üÉ¨Ãèº¯Êı ÉùÃ÷
#endif