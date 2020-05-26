#include <iwdg.h>
#include <stm32f10x.h>



void IWDG_Init(u8 prer,u16 rlr)
{
 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//设置寄存器写保护，操作寄存器PR RLR的值
	IWDG_SetPrescaler(prer);         //设置看门狗分频系数prer(IWDG_PR值) 范围0-7
	IWDG_SetReload(rlr);            //设置看门狗重装载值rlr（IWDG_RLR值）
	IWDG_ReloadCounter();       //向IWDG_KR写入0XAAA,按照IWDG重装载寄存器的值重装载IWDG计数器    
	//通过公式计算出看门狗溢出时间即喂狗时间 Tout=((4*2^prer)*rlr)/40  (单位Ms)
	//溢出时间？？
	IWDG_Enable();               //启动看门狗 向IWDG写入0XCCCC


}