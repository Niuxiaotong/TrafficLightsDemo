#include <key.h>
#include <delay.h>

void KEY_Init(void) //IO��ʼ�� Ϊ����
{
	GPIO_InitTypeDef GPIO_InitStructure;//GPIO_InitStrctureָ��	GPIO_InitTypeDef �ĵ�ַ�

//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTCʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ���ԣ�������
	
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����Ϊ���� �
	GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; ///PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����Ϊ��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);//��ʼ��GPIOC5

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//����Ϊ	��������
  GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA.0 
	
}

////////////����������PA0��PA15��PC5֮��ĵ�ƽ��Ϣ��ô���ͣ���->��key.h���ú궨������֮���ϵ�����¼�key0����ƽ�仯�����Ǹ�����??
///-��key0ֱ�Ӻ�����PC5����������key0��Ҳ����PC5�ĵ�ƽ�����˸ı�
/////����������
/////���ذ���ֵ
////mode=0,��֧��������1��֧������

u8 KEY_Scan(u8 mode)    
{
	//u8 key_up=1;
	static u8 key_up=1;//�������ɿ���־->ʹ�þ�̬���������ͷŴ洢�ռ�
	if(mode) key_up=1;//֧������  ����������ʲô,����key_upʲô���ã�����(û��Ū����֧�ֺ�֧��������������)
	if(key_up&&(KEY0 == 0||KEY1==0||WK_UP==1))  //ʲô��˼��->���Ի�����key0,1λ������Ϊ�ߵ�ƽ��wk_upΪ������Ϊ�͵�ƽ����key=0��˵��key0������
	{
		delay_ms(10);//ȥ����
		key_up=0;
	if(KEY0==0)return KEY0_PRES; //#define KEY0_PRES 1//�����𵽰����󷵻�ֵ�����ã�����
  else if(KEY1==0)	return KEY1_PRES;
	else if(WK_UP==1)	return WKUP_PRES;	
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1;
	return 0;//�ް������
}/*
u8 KEY_Scan(u8 mode)  //֧������
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
u8 KEY_Scan(u8 mode)  //��֧������
{
	  static u8 key_up=1;
	//if(mode) key_up =1;
	//u8 key_up=1;
	if(key_up && (KEY0==0 || KEY1==0 || WK_UP==1))
	{
		delay_ms(10);//��ʱ����
		key_up=0;
		if (KEY0==0) return KEY0_PRES;
		else if (KEY1==0) return KEY1_PRES;
		else if (WK_UP==1) return WKUP_PRES;
	} 
	  else if (KEY0==1 || KEY1==1 || WK_UP==0) key_up=1;
		return 0;
}
*/