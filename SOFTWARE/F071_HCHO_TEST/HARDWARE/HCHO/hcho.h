#ifndef __HCHO_H
#define __HCHO_H			 
#include "sys.h"	 								  
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
	  		  	
extern u8 HCHO_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern u8 HCHO_RX_CNT;   			//���յ������ݳ���

//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_USART1_RX 1			//0,������;1,����.




void HCHO_Init(u32 bound);
void HCHO_Send_Data(u8 *buf,u8 len);
void HCHO_Receive_Data(u8 *buf,u8 *len);


#endif	   
















