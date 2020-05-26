#include <iwdg.h>
#include <stm32f10x.h>



void IWDG_Init(u8 prer,u16 rlr)
{
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//���üĴ���д�����������Ĵ���PR RLR��ֵ
	IWDG_SetPrescaler(prer);         //���ÿ��Ź���Ƶϵ��prer(IWDG_PRֵ) ��Χ0-7
	IWDG_SetReload(rlr);            //���ÿ��Ź���װ��ֵrlr��IWDG_RLRֵ��
	IWDG_ReloadCounter();       //��IWDG_KRд��0XAAA,����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������    
	//ͨ����ʽ��������Ź����ʱ�伴ι��ʱ�� Tout=((4*2^prer)*rlr)/40  (��λMs)
	//���ʱ�䣿��
	IWDG_Enable();               //�������Ź� ��IWDGд��0XCCCC


}