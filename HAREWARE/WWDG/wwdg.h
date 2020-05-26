#ifndef __WWDG_H
#define __WWDG_H

#include <sys.h>

//void IWDG_Init(u8 pre,u16 rlr);
void WWDG_Init(u8 tr,u8 wr,u32 fprer);
void WWDG_Set_Counter(u8 cnt);
void WWDG_NVIC_Init();
 void WWDG_IRQnHandler(void);
	

#endif