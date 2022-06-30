#ifndef __OLED_H
#define __OLED_H

#include "includes.h"
//#include "sys.h"
//#include "stdlib.h"	  
#define  uchar unsigned char 
#define  uint unsigned int 
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0

//OLED:       CS  ->P8.0, RES->P8.2,  DC->P8.1,   D0(SCL)->P8.4,  D1(SDA)->P8.3

#define OLED_CS_Clr()  P8OUT &=~ BIT0
#define OLED_CS_Set()  P8OUT |= BIT0

#define OLED_RST_Clr() P8OUT &=~ BIT2
#define OLED_RST_Set() P8OUT |= BIT2

#define OLED_DC_Clr() P8OUT &=~ BIT1
#define OLED_DC_Set() P8OUT |= BIT1

#define OLED_SCLK_Clr() P8OUT &=~ BIT4
#define OLED_SCLK_Set() P8OUT |= BIT4

#define OLED_SDIN_Clr() P8OUT &=~ BIT3
#define OLED_SDIN_Set() P8OUT |= BIT3

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED�˿ڶ���----------------  					   

//const uchar F6x8[][6];
//const uchar F8X16[];
//const unsigned char Hzk[][32];
//unsigned char bmp1[];
 		
//OLED�����ú���
void OLED_WR_Byte(uchar dat,uchar cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uchar x,uchar y,uchar t);
void OLED_Fill(uchar x1,uchar y1,uchar x2,uchar y2,uchar dot);
void OLED_ShowChar(uchar x,uchar y,uchar chr);
void OLED_ShowNum(uchar x,uchar y,uint num,uchar len,uchar size2);
void OLED_ShowString(uchar x,uchar y, uchar *p);	 
void OLED_Set_Pos(uchar x, uchar y);
void OLED_ShowCHinese(uchar x,uchar y,uchar no);
void OLED_DrawBMP(uchar x0, uchar y0,uchar x1, uchar y1,uchar BMP[]);

#endif  
	 



