/*******************************************************************************
** ��Ȩ:     	xxxlzjxxx CO.,LTD
** �ļ���:   	wdog.c
** ��������: 	IAR 6.10
** ���̴�С:	
** ����:     	xxxlzjxxx
** ��������:	2015��12��9�� 
** ����:       �ⲿ���Ź�����
								  msp430f5438a
-------------------------------------------------------------------------------
SP706R:     WDI ->P4.7
-------------------------------------------------------------------------------
** �������:
            SP706REN
** �޸���־��
			
*******************************************************************************/
/*********************************����ͷ�ļ�************************************/

#include "includes.h"

/******************************************************************************/
/*******************************************************************************
** Name:			void GPIO_Init(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			2015.12.9
** Function:		����IO��
** Version:	
*******************************************************************************/
void GPIO_Init()
{
//����I/O��Ϊ���     
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
//����I/O������͵�ƽ  
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
//***************************����������Ҫʹ�õ�IO��****************************
    P11OUT |= BIT0 + BIT1 + BIT2;
}

void Ext_Wdog_Feed(void)
{
    P1OUT ^= BIT4;     //System WDOG
	P1OUT ^= BIT4;     //System WDOG
}