/*****************************************************************************
** 文件名称：timer.c
** 功    能：
** 修改日志：
******************************************************************************/
#include "includes.h"

extern unsigned int SamplingPeriod;
/******************************************************************************
** 函数名称： void Init_TimerA(void)
** 功    能:  定时器A的初始化,每隔6s唤醒LPMx模式下的MCU
** 修改日志：
******************************************************************************/
void Init_TimerA(void)
{
   	TA1CCTL0 = CCIE;                        // CCR0 interrupt enabled
   	TA1CCR0 = 512 - 1;			            // 1s一次中断
   	TA1EX0 = TAIDEX_7;                      //timer A 级联8分频,最终ACLK为32768/8/8=512HZ ,(31.25ms)
   	TA1CTL = TASSEL_1 + MC_1 + TACLR + ID_3; //with ACLK(32768) as clock ,up mode,输入8分频 divide
}
/******************************************************************************
** 函数名称： void Init_TimerB(void)
** 功    能:  定时器B的初始化
** 修改日志：  
******************************************************************************/
void Init_TimerB(uint a)
{
   	switch(a)
   	{
		case 0:
   			TBCCTL0 |= CCIE;                         // CCR0 interrupt enabled                        
   			TBCCR0 = 39063;
   			TBCTL = TBSSEL_2 + MC_1 + TBCLR + ID_0 ;// 512HZ,SMCLK = 20 000 000Hz, upmode, clear TBR
			break;
		case 1:
	  		TBCCTL0 |= CCIE;                         // CCR0 interrupt enabled                        
   			TBCCR0 = 9766;
   			TBCTL = TBSSEL_2 + MC_1 + TBCLR + ID_3 ;// 256HZ,SMCLK, upmode, clear TBR
			break;
		case 2:
	  		TBCCTL0 |= CCIE;                         // CCR0 interrupt enabled                        
   			TBCCR0 = 19531;
  	 		TBCTL = TBSSEL_2 + MC_1 + TBCLR + ID_3 ;// 128HZ,SMCLK, upmode, clear TBR
			break;
		case 3:
	  		TBCCTL0 = CCIE;                        	// CCR0 interrupt enabled                        
			TBCCR0 = 32 - 1;							//设置为1s产生中断。串口等待主机命令的总时间
			TBEX0 = TBIDEX_7;                      	//timer B 级联8分频,最终ACLK为32768/16/8/8=32HZ ,(31.25ms)
  	 		TBCTL = TBSSEL_1 + MC_1 + TBCLR + ID_3;// with ACLK(32768/16) as clock ,up mode,输入8分频 divide
		  	break;
		default:
	  		break;
	}
}