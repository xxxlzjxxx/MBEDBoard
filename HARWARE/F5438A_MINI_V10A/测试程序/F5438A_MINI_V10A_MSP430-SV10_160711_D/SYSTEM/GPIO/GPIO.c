/*******************************************************************************
** 版权:     	xxxlzjxxx CO.,LTD
** 文件名:   	wdog.c
** 工作环境: 	IAR 6.10
** 工程大小:	
** 作者:     	xxxlzjxxx
** 生成日期:	2015年12月9日 
** 功能:       外部看门狗程序
								  msp430f5438a
-------------------------------------------------------------------------------
SP706R:     WDI ->P4.7
-------------------------------------------------------------------------------
** 相关器件:
            SP706REN
** 修改日志：
			
*******************************************************************************/
/*********************************包含头文件************************************/

#include "includes.h"

/******************************************************************************/
/*******************************************************************************
** Name:			void GPIO_Init(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.12.9
** Function:		配置IO口
** Version:	
*******************************************************************************/
void GPIO_Init()
{
//设置I/O口为输出     
	P1DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7; 
	P2DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P3DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P4DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P5DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P6DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P7DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P8DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
    P9DIR |= BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7;
	P10DIR |= BIT0|BIT1|BIT2|BIT3|BIT4;
	P11DIR |= BIT0|BIT1|BIT2;
//设置I/O口输出低电平  
	P1OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7); 
	P2OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P3OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P4OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P5OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P6OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P7OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P8OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P9OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7);
	P10OUT &= ~(BIT0|BIT1|BIT2|BIT3|BIT4);
	P11OUT &= ~(BIT0|BIT1|BIT2);
//***************************以下设置需要使用的IO口****************************
    P11OUT |= BIT0 + BIT1 + BIT2;
}

void Ext_Wdog_Feed(void)
{
    P1OUT ^= BIT4;     //System WDOG
	P1OUT ^= BIT4;     //System WDOG
}