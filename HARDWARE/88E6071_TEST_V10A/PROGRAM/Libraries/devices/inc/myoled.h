#ifndef __MYOLED_H
#define __MYOLED_H			  	 
#include "gpio.h"
#include "stdlib.h"	 
#include "stdint.h"
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//OLED ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	  
 

//OLEDģʽ����
//0: 4�ߴ���ģʽ  ��ģ���BS1��BS2����GND��
//1: ����8080ģʽ ��ģ���BS1��BS2����VCC��
#define OLED_MODE 	0 
		    						  
//-----------------OLED�˿ڶ���----------------  					   
#define OLED_CS 	PCout(7)
#define OLED_RST  	PCout(8)	
#define OLED_RS 	PCout(9)
#define OLED_WR 	PCout(4)		  
#define OLED_RD 	PCout(3)
 
//ʹ��4�ߴ��нӿ�ʱʹ�� 
#define OLED_SCLK 	PCout(10)
#define OLED_SDIN 	PCout(11)
		     
#define OLED_CMD  	0		//д����
#define OLED_DATA 	1		//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	 
#endif  
	 



