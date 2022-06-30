/*******************************************************************************
** 版权:     	xxxlzjxxx CO.,LTD
** 文件名:   	sysclk.c
** 工作环境: 	IAR 6.10
** 工程大小:	
** 作者:     	xxxlzjxxx
** 生成日期:	2015年12月9日 
** 功能:       系统时钟设置
** 相关器件:
** 修改日志：
			
*******************************************************************************/
/*********************************包含头文件************************************/

#include "includes.h"

/******************************************************************************/
/*******************************************************************************
** Name:			void SystemClock(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.12.9
** Function:		系统时钟初始化
                    MCLK = SMCLK = 12MHz
                    ACLK = REFOCLK = 32768Hz
** Version:	
*******************************************************************************/
void  SystemClock(void)
{
  	P5SEL  |= BIT2;                    //XT2复用功能
  	UCSCTL6 &=~XT2OFF;                //XT2on
  	do
  	{
    	UCSCTL7 &= ~XT2OFFG;             // Clear XT2 fault flags
  	}
   	while (UCSCTL7&XT2OFFG);          // Test XT2 fault flag
   	SFRIFG1 &= ~OFIFG;
   	UCSCTL3 |=0x50;
   	UCSCTL4 |=0x0255;           //MCLK = SMCLK = 12MHz  0分频，ACLK = REFOCLK=32.768K
   	UCSCTL5 |=0x0000;           //ACLK = 32768Hz 0分频;
   	return;
}
