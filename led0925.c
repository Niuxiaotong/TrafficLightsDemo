#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//?????????,??????,??????????
//ALIENTEK??STM32???
//LED????	   
//????@ALIENTEK
//????:www.openedv.com
//????:2012/9/2
//??:V1.0
//????,?????
//Copyright(C) ????????????? 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//???PB5?PE5????.??????????		    
//LED IO???
//??? LED ???
//GPIO_Init(void)
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //??PA,PB????
	
	//???1?,PB5?PB6?PB7??
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 ????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //?????????GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 ???
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //-->PA.7 ????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //?????????GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_6);						 //PB.5 ???
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.5 ????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //?????????GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.5 ???
 
 //????????GPIO,????SPI1?IO
 //1???2?????3?????4?LOAD?
 //PA6\7\8
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOA,GPIO_Pin_6);	
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOA,GPIO_Pin_7);	
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);	
 GPIO_SetBits(GPIOA,GPIO_Pin_5);	
 
/*
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PE.5 ????, ????
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //???? ,IO????50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PE.5 ??? 
	*/
	
}
 
