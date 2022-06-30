#ifndef __ILI9488_H
#define __ILI9488_H		
#include "sys.h"	 
#include "stdlib.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//2.4��/2.8��/3.5��/4.3��/7�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963��		    
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/7/4
//�汾��V3.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2�޸�˵��
//֧����SPFD5408������,�����Һ��IDֱ�Ӵ�ӡ��HEX��ʽ.����鿴LCD����IC.
//V1.3
//�����˿���IO��֧��
//�޸��˱�����Ƶļ��ԣ�������V1.8���Ժ�Ŀ�����汾��
//����1.8�汾֮ǰ(������1.8)��Һ��ģ��,���޸�LCD_Init������LCD_LED=1;ΪLCD_LED=1;
//V1.4
//�޸���LCD_ShowChar������ʹ�û��㹦�ܻ��ַ���
//�����˺�������ʾ��֧��
//V1.5 20110730
//1,�޸���B505Һ������ɫ�����bug.
//2,�޸��˿���IO�������������÷�ʽ.
//V1.6 20111116
//1,�����LGDP4535Һ��������֧��
//V1.7 20120713
//1,����LCD_RD_DATA����
//2,���Ӷ�ILI9341��֧��
//3,����ILI9325�Ķ�����������
//4,����LCD_Scan_Dir����(����ʹ��)	  
//6,�����޸��˲���ԭ���ĺ���,����Ӧ9341�Ĳ���
//V1.8 20120905
//1,����LCD��Ҫ�������ýṹ��lcddev
//2,����LCD_Display_Dir����,֧�����ߺ������л�
//V1.9 20120911
//1,����RM68042������ID:6804��������6804��֧�ֺ�����ʾ����ԭ�򣺸ı�ɨ�跽ʽ��
//����6804��������ʧЧ���Թ��ܶ෽�������У���ʱ�޽⡣
//V2.0 20120924
//�ڲ�Ӳ����λ�������,ILI9341��ID��ȡ�ᱻ�����9300,�޸�LCD_Init,���޷�ʶ��
//�����������IDΪ9300/�Ƿ�ID��,ǿ��ָ������ICΪILI9341��ִ��9341�ĳ�ʼ����
//V2.1 20120930
//����ILI9325����ɫ��bug��
//V2.2 20121007
//����LCD_Scan_Dir��bug��
//V2.3 20130120
//����6804֧�ֺ�����ʾ
//V2.4 20131120
//1,����NT35310��ID:5310����������֧��
//2,����LCD_Set_Window����,�������ô���,�Կ������,�Ƚ�����,���Ǹú����ں���ʱ,��֧��6804.
//V2.5 20140211
//1,����NT35510��ID:5510����������֧��
//V2.6 20140504
//1,����ASCII 24*24�����֧��(���������û������������)  
//2,�޸Ĳ��ֺ�������,��֧��MDK -O2�Ż�
//3,���9341/35310/35510,дʱ������Ϊ���,�����ܵ�����ٶ�
//4,ȥ����SSD1289��֧��,��Ϊ1289ʵ����̫����,������Ҫ1us...��ֱ����.���ʺ�F4ʹ��
//5,����68042��C505��IC�Ķ���ɫ������bug.
//V2.7 20140710
//1,����LCD_Color_Fill������һ��bug. 
//2,����LCD_Scan_Dir������һ��bug.
//V2.8 20140721
//1,���MDKʹ��-O2�Ż�ʱLCD_ReadPoint��������ʧЧ������.
//2,����LCD_Scan_Dir����ʱ���õ�ɨ�跽ʽ��ʾ��ȫ��bug.
//V2.9 20141130
//1,������SSD1963 LCD��֧��.
//2,����LCD_SSD_BackLightSet����
//3,ȡ��ILI93XX��Rxx�Ĵ�������
//V3.0 20150423
//�޸�SSD1963 LCD������������.
//////////////////////////////////////////////////////////////////////////////////	 

//LCD��Ҫ������
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ�� 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_LED PBout(15)  		//LCD����    		 PB15 	    
//LCD��ַ�ṹ��
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A6��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define TFTLCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* ��8λR,G,Bת��Ϊ 16λRGB565��ʽ */
//enum
//{
//	CL_WHITE        = RGB(255,255,255),	/* ��ɫ */
//	CL_BLACK        = RGB(  0,  0,  0),	/* ��ɫ */
//	CL_RED          = RGB(255,	0,  0),	/* ��ɫ */
//	CL_GREEN        = RGB(  0,255,  0),	/* ��ɫ */
//	CL_BLUE         = RGB(  0,	0,255),	/* ��ɫ */
//	CL_YELLOW       = RGB(255,255,  0),	/* ��ɫ */

//	CL_GREY			= RGB( 98, 98, 98), 	/* ���ɫ */
//	CL_GREY1		= RGB( 150, 150, 150), 	/* ǳ��ɫ */
//	CL_GREY2		= RGB( 180, 180, 180), 	/* ǳ��ɫ */
//	CL_GREY3		= RGB( 200, 200, 200), 	/* ��ǳ��ɫ */
//	CL_GREY4		= RGB( 230, 230, 230), 	/* ��ǳ��ɫ */

//	CL_BUTTON_GREY	= RGB( 220, 220, 220), /* WINDOWS ��ť�����ɫ */
//	CL_MAGENTA      = 0xF81F,	/* ����ɫ�����ɫ */
//	CL_CYAN         = 0x7FFF,	/* ����ɫ����ɫ */
//	CL_BLUE1        = RGB(  0,  0, 240),		/* ����ɫ */
//	CL_BLUE2        = RGB(  0,  0, 128),		/* ����ɫ */
//	CL_BLUE3        = RGB(  68, 68, 255),		/* ǳ��ɫ1 */
//	CL_BLUE4        = RGB(  0, 64, 128),		/* ǳ��ɫ1 */
//	/* UI ���� Windows�ؼ�����ɫ */
//	CL_BTN_FACE		= RGB(236, 233, 216),	/* ��ť������ɫ(��) */	
//	CL_BTN_FONT		= CL_BLACK,				/* ��ť������ɫ���ڣ� */	
//	CL_BOX_BORDER1	= RGB(172, 168,153),	/* �����������ɫ */
//	CL_BOX_BORDER2	= RGB(255, 255,255),	/* �������Ӱ����ɫ */
//	CL_MASK			= 0x9999	/* ��ɫ���룬�������ֱ���͸�� */
//};


//������ɫ
#define tWHITE         	 0xFFFF
#define tBLACK         	 0x0000	  
#define tBLUE         	 0x001F  
#define tBRED             0XF81F
#define tGRED 			 0XFFE0
#define tGBLUE			 0X07FF
#define tRED           	 0xF800
#define tMAGENTA       	 0xF81F
#define tGREEN         	 0x07E0
#define tCYAN          	 0x7FFF
#define tYELLOW        	 0xFFE0
#define tBROWN 			 0XBC40 //��ɫ
#define tBRRED 			 0XFC07 //�غ�ɫ
#define tGRAY  			 0X8430 //��ɫ
//GUI��ɫ
#define tDARKBLUE      	 0X01CF	//����ɫ
#define tLIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define tGRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
#define tLIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define tLGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define tLGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define tLBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//RGB2GBR
#define WHITE 	(LCD_BGR2RGB(tWHITE))
#define BLACK 	(LCD_BGR2RGB(tBLACK))
#define BLUE  	(LCD_BGR2RGB(tBLUE))
#define BRED 	(LCD_BGR2RGB(tBRED))
#define GRED 	(LCD_BGR2RGB(tGRED))
#define GBLUE  	(LCD_BGR2RGB(tGBLUE))
#define RED 	(LCD_BGR2RGB(tRED))
#define MAGENTA (LCD_BGR2RGB(tRED))
#define GREEN  	(LCD_BGR2RGB(tGREEN))
#define CYAN 	(LCD_BGR2RGB(tCYAN))
#define YELLOW	(LCD_BGR2RGB(tYELLOW))
#define BROWN  	(LCD_BGR2RGB(tBROWN))
#define BRRED 	(LCD_BGR2RGB(tBRRED))
#define GRAY 	(LCD_BGR2RGB(tGRAY))

#define DARKBLUE  	(LCD_BGR2RGB(tDARKBLUE))
#define LIGHTBLUE  	(LCD_BGR2RGB(tLIGHTBLUE))
#define GRAYBLUE 	(LCD_BGR2RGB(tGRAYBLUE))
#define LIGHTGREEN  (LCD_BGR2RGB(tLIGHTGREEN))
#define LGRAY  		(LCD_BGR2RGB(tLGRAY))
#define LGRAYBLUE  	(LCD_BGR2RGB(tLGRAYBLUE))
#define LBBLUE  	(LCD_BGR2RGB(tLBBLUE))
	    															  
void ILI9488_Init(void);													   	//��ʼ��
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_DrawPoint(u16 x,u16 y);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//���ٻ���
u16  LCD_ReadPoint(u16 x,u16 y); 											//���� 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//��ʾһ���ַ���,12/16����

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(u8 dir);									//������ɨ�跽��
void LCD_Display_Dir(u8 dir);								//������Ļ��ʾ����
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);	//���ô���					   						   																			 
//LCD�ֱ�������
#define SSD_HOR_RESOLUTION		480		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		320		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
	 



