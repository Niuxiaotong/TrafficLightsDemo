#ifndef _KEY_H
#define _KEY_H  //�궨�壿������
#include <sys.h>

//#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY0 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����0 ���ݵ�·ԭ��ͼ��֪��stm32����key0��PC 5���� ͨ���궨���PC5��ֵ��ֵ���ˣţ٣�
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ����1   ���ݵ�·ԭ��ͼ��֪��stm32����key1��PA15����
//#define KEY2 GPIO_ReadIputDataBit(GPIOE,GPIO_Pin4)//��ȡ��2
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3��WK_UP��


#define KEY0_PRES 1//KEY0���£��
#define KEY1_PRES 2//KEY1����
#define WKUP_PRES 3//KEY_UP����


void KEY_Init(void);  //IO��ʼ��
u8 KEY_Scan(u8 mode);   //����ɨ�躯�� ����
#endif