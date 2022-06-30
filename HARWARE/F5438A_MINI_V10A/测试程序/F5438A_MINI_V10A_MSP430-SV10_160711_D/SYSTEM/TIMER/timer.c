/*****************************************************************************
** �ļ����ƣ�timer.c
** ��    �ܣ�
** �޸���־��
******************************************************************************/
#include "includes.h"

extern unsigned int SamplingPeriod;
/******************************************************************************
** �������ƣ� void Init_TimerA(void)
** ��    ��:  ��ʱ��A�ĳ�ʼ��,ÿ��6s����LPMxģʽ�µ�MCU
** �޸���־��
******************************************************************************/
void Init_TimerA(void)
{
   	TA1CCTL0 = CCIE;                        // CCR0 interrupt enabled
   	TA1CCR0 = 512 - 1;			            // 1sһ���ж�
   	TA1EX0 = TAIDEX_7;                      //timer A ����8��Ƶ,����ACLKΪ32768/8/8=512HZ ,(31.25ms)
   	TA1CTL = TASSEL_1 + MC_1 + TACLR + ID_3; //with ACLK(32768) as clock ,up mode,����8��Ƶ divide
}
/******************************************************************************
** �������ƣ� void Init_TimerB(void)
** ��    ��:  ��ʱ��B�ĳ�ʼ��
** �޸���־��  
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
			TBCCR0 = 32 - 1;							//����Ϊ1s�����жϡ����ڵȴ������������ʱ��
			TBEX0 = TBIDEX_7;                      	//timer B ����8��Ƶ,����ACLKΪ32768/16/8/8=32HZ ,(31.25ms)
  	 		TBCTL = TBSSEL_1 + MC_1 + TBCLR + ID_3;// with ACLK(32768/16) as clock ,up mode,����8��Ƶ divide
		  	break;
		default:
	  		break;
	}
}