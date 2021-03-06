#ifndef _KEY_H
#define _KEY_H  //宏定义？？？？
#include <sys.h>

//#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0 根据电路原理图可知，stm32板上key0与PC 5相连 通过宏定义把PC5的值赋值给ＫＥＹ０
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1   根据电路原理图可知，stm32板上key1与PA15相连
//#define KEY2 GPIO_ReadIputDataBit(GPIOE,GPIO_Pin4)//读取按2
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3（WK_UP）


#define KEY0_PRES 1//KEY0按下？�
#define KEY1_PRES 2//KEY1按下
#define WKUP_PRES 3//KEY_UP按下


void KEY_Init(void);  //IO初始化
u8 KEY_Scan(u8 mode);   //按键扫描函数 声明
#endif