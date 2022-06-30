
#include "includes.h"

//*************************以下定义与主机发送的命令相关**************************


/******************************************************************************
** 函数名称：void Usart_Wire_Temp_Init_9600(void)
** 功    能：串口A0初始化 ,按照不同要求的波特率进行初始化
** 修改日志：
*******************************************************************************/
void UsartInit(void)
{
  	USART_TX_232_SEL;
  	USART_RX_232_SEL;

    UCA0CTL1 |= UCSWRST;              // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL__SMCLK;        // SMCLK

	UCA0BR0 = 0X08;                   //baud 设置参考 user's guide Page 954
    UCA0BR1 = 0x02;					// 20MHz/(8*256+37) = 9600
//    UCA1BR0 = 52;                   //baud 设置参考 user's guide Page 954
//    UCA1BR1 = 0;					//9600

    UCA0MCTL = UCBRS_0;                  // Modulation
    UCA0CTL1 &= ~UCSWRST;            // **Initialize USCI state machine**
//    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt


//  	UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
//  	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
//  	UCA0BR0 = 6;                              // 1MHz 9600 (see User's Guide)
//  	UCA0BR1 = 0;                              // 1MHz 9600
//  	UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
//                                            // over sampling
//  	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
//  	UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}
/*****************************************************************************
** 函数名称：Send_232_data(uchar *tdata,uint data_length);
** 功    能：232数据发送 UART_A0
** 修改日志：
*****************************************************************************/
void Send_232_data(unsigned char *tdata, unsigned int data_length)
{
//   while (!(UCA1IFG & UCTXIFG));
   	for(unsigned char s = 0; s < data_length; s++)
   	{
    	while(!(UCA0IFG & UCTXIFG));	// 判断是否发送完毕
		UCA0TXBUF = *(tdata + s);
   	}
   	while (!(UCA0IFG & UCTXIFG));		// 判断是否发送完毕  
}
/*******************************************************************************
** Name:			int putchar(int ch)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			 
** Function:		printf相关
** Version:		
*******************************************************************************/
int putchar(int ch)
{
  	UCA0TXBUF = ch; 
  	while (!(UCA0IFG & UCTXIFG));   
  	return ch;
}
/*******************************************************************************
** Name:			int getchar(void)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			 
** Function:		scanf相关
** Version:		
*******************************************************************************/
int getchar(void)
{
  	char ch; 
  	while (!(UCA0IFG & UCTXIFG));
	ch = UCA0RXBUF;
  	return ch;
}