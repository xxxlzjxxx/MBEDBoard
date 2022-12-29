
#include "includes.h"

//*************************���¶������������͵��������**************************


/******************************************************************************
** �������ƣ�void Usart_Wire_Temp_Init_9600(void)
** ��    �ܣ�����A0��ʼ�� ,���ղ�ͬҪ��Ĳ����ʽ��г�ʼ��
** �޸���־��
*******************************************************************************/
void UsartInit(void)
{
  	USART_TX_232_SEL;
  	USART_RX_232_SEL;

    UCA0CTL1 |= UCSWRST;              // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL__SMCLK;        // SMCLK

	UCA0BR0 = 0X08;                   //baud ���òο� user's guide Page 954
    UCA0BR1 = 0x02;					// 20MHz/(8*256+37) = 9600
//    UCA1BR0 = 52;                   //baud ���òο� user's guide Page 954
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
** �������ƣ�Send_232_data(uchar *tdata,uint data_length);
** ��    �ܣ�232���ݷ��� UART_A0
** �޸���־��
*****************************************************************************/
void Send_232_data(unsigned char *tdata, unsigned int data_length)
{
//   while (!(UCA1IFG & UCTXIFG));
   	for(unsigned char s = 0; s < data_length; s++)
   	{
    	while(!(UCA0IFG & UCTXIFG));	// �ж��Ƿ������
		UCA0TXBUF = *(tdata + s);
   	}
   	while (!(UCA0IFG & UCTXIFG));		// �ж��Ƿ������  
}
/*******************************************************************************
** Name:			int putchar(int ch)
** Workspace: 		IAR 6.10 
** Designed by:	xxxlzjxxx
** Date: 			 
** Function:		printf���
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
** Function:		scanf���
** Version:		
*******************************************************************************/
int getchar(void)
{
  	char ch; 
  	while (!(UCA0IFG & UCTXIFG));
	ch = UCA0RXBUF;
  	return ch;
}