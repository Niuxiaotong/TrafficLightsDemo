#include <beep.h>
#include <stm32f10x.h>
#include <sys.h>

void BEEP_Init(void)  //stm32min�޷�����
{
	GPIO_InitTypeDef GPIO_InitStructure;//��ʼ��,����ʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIOB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//BEEP-->PB.8 �˿����ã�������
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;//GPIOB����Ϊ������������Ϊ50MHZ
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;//�ٶ�Ϊ50MHZ
	
  GPIO_Init(GPIOB,&GPIO_InitStructure);//���ݲ�����ʼ��GPIOB.8
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8);//���0���رշ��������



}