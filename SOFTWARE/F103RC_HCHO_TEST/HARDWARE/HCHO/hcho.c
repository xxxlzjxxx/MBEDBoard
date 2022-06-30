#include "sys.h"		    
#include "hcho.h"	 
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//HCHO���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


#ifdef EN_USART2_RX   	//���ʹ���˽���


//���ջ����� 	
u8 HCHO_RX_BUF[64];  	//���ջ���,���64���ֽ�.
//���յ������ݳ���
u8 HCHO_RX_CNT=0;   		  
  
void USART2_IRQHandler(void)
{
	u8 res;	    
 
 	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
	{	 
	 			 
		res =USART_ReceiveData(USART2); 	//��ȡ���յ�������
		if(HCHO_RX_CNT<64)
		{
			HCHO_RX_BUF[HCHO_RX_CNT]=res;		//��¼���յ���ֵ
			HCHO_RX_CNT++;						//������������1 
		} 
	}  											 
} 
#endif										 
//��ʼ��IO ����1
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void HCHO_Init(u32 bound)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,Dʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

#ifdef EN_USART2_RX		  	//���ʹ���˽���

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���	

	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); ; //��ʼ������

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�

	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

 #endif
}

//HCHO����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void HCHO_Send_Data(u8 *buf,u8 len)
{
	// u8 t;
	// HCHO_TX_EN=1;			//����Ϊ����ģʽ
  	// for(t=0;t<len;t++)		//ѭ����������
	// {		   
		// while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		// USART_SendData(USART2,buf[t]);
	// }	 
 
	// while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		
	// HCHO_RX_CNT=0;	  
	// HCHO_TX_EN=0;				//����Ϊ����ģʽ	
}
//HCHO��ѯ���յ�������
//buf:���ջ����׵�ַ
//len:���������ݳ���
void HCHO_Receive_Data(u8 *buf, u8 *len)
{
	u8 rxlen = HCHO_RX_CNT;
	u8 i = 0;
	*len = 0;				//Ĭ��Ϊ0
	delay_ms(10);		//�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս���
	if(rxlen == HCHO_RX_CNT && rxlen)//���յ�������,�ҽ��������
	{
		for(i=0;i<rxlen;i++)
		{
			buf[i] = HCHO_RX_BUF[i];	
		}		
		*len=HCHO_RX_CNT;	//��¼�������ݳ���
		HCHO_RX_CNT=0;		//����
	}
}





















