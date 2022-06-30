#ifndef __ILI9488_H
#define __ILI9488_H		
#include "sys.h"	 
#include "stdlib.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//2.4寸/2.8寸/3.5寸/4.3寸/7寸 TFT液晶驱动	  
//支持驱动IC型号包括:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963等		    
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/7/4
//版本：V3.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2修改说明
//支持了SPFD5408的驱动,另外把液晶ID直接打印成HEX格式.方便查看LCD驱动IC.
//V1.3
//加入了快速IO的支持
//修改了背光控制的极性（适用于V1.8及以后的开发板版本）
//对于1.8版本之前(不包括1.8)的液晶模块,请修改LCD_Init函数的LCD_LED=1;为LCD_LED=1;
//V1.4
//修改了LCD_ShowChar函数，使用画点功能画字符。
//加入了横竖屏显示的支持
//V1.5 20110730
//1,修改了B505液晶读颜色有误的bug.
//2,修改了快速IO及横竖屏的设置方式.
//V1.6 20111116
//1,加入对LGDP4535液晶的驱动支持
//V1.7 20120713
//1,增加LCD_RD_DATA函数
//2,增加对ILI9341的支持
//3,增加ILI9325的独立驱动代码
//4,增加LCD_Scan_Dir函数(慎重使用)	  
//6,另外修改了部分原来的函数,以适应9341的操作
//V1.8 20120905
//1,加入LCD重要参数设置结构体lcddev
//2,加入LCD_Display_Dir函数,支持在线横竖屏切换
//V1.9 20120911
//1,新增RM68042驱动（ID:6804），但是6804不支持横屏显示！！原因：改变扫描方式，
//导致6804坐标设置失效，试过很多方法都不行，暂时无解。
//V2.0 20120924
//在不硬件复位的情况下,ILI9341的ID读取会被误读成9300,修改LCD_Init,将无法识别
//的情况（读到ID为9300/非法ID）,强制指定驱动IC为ILI9341，执行9341的初始化。
//V2.1 20120930
//修正ILI9325读颜色的bug。
//V2.2 20121007
//修正LCD_Scan_Dir的bug。
//V2.3 20130120
//新增6804支持横屏显示
//V2.4 20131120
//1,新增NT35310（ID:5310）驱动器的支持
//2,新增LCD_Set_Window函数,用于设置窗口,对快速填充,比较有用,但是该函数在横屏时,不支持6804.
//V2.5 20140211
//1,新增NT35510（ID:5510）驱动器的支持
//V2.6 20140504
//1,新增ASCII 24*24字体的支持(更多字体用户可以自行添加)  
//2,修改部分函数参数,以支持MDK -O2优化
//3,针对9341/35310/35510,写时间设置为最快,尽可能的提高速度
//4,去掉了SSD1289的支持,因为1289实在是太慢了,读周期要1us...简直奇葩.不适合F4使用
//5,修正68042及C505等IC的读颜色函数的bug.
//V2.7 20140710
//1,修正LCD_Color_Fill函数的一个bug. 
//2,修正LCD_Scan_Dir函数的一个bug.
//V2.8 20140721
//1,解决MDK使用-O2优化时LCD_ReadPoint函数读点失效的问题.
//2,修正LCD_Scan_Dir横屏时设置的扫描方式显示不全的bug.
//V2.9 20141130
//1,新增对SSD1963 LCD的支持.
//2,新增LCD_SSD_BackLightSet函数
//3,取消ILI93XX的Rxx寄存器定义
//V3.0 20150423
//修改SSD1963 LCD屏的驱动参数.
//////////////////////////////////////////////////////////////////////////////////	 

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令 
}_lcd_dev; 	  

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
#define	LCD_LED PBout(15)  		//LCD背光    		 PB15 	    
//LCD地址结构体
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define TFTLCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向

//#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* 将8位R,G,B转化为 16位RGB565格式 */
//enum
//{
//	CL_WHITE        = RGB(255,255,255),	/* 白色 */
//	CL_BLACK        = RGB(  0,  0,  0),	/* 黑色 */
//	CL_RED          = RGB(255,	0,  0),	/* 红色 */
//	CL_GREEN        = RGB(  0,255,  0),	/* 绿色 */
//	CL_BLUE         = RGB(  0,	0,255),	/* 蓝色 */
//	CL_YELLOW       = RGB(255,255,  0),	/* 黄色 */

//	CL_GREY			= RGB( 98, 98, 98), 	/* 深灰色 */
//	CL_GREY1		= RGB( 150, 150, 150), 	/* 浅灰色 */
//	CL_GREY2		= RGB( 180, 180, 180), 	/* 浅灰色 */
//	CL_GREY3		= RGB( 200, 200, 200), 	/* 最浅灰色 */
//	CL_GREY4		= RGB( 230, 230, 230), 	/* 最浅灰色 */

//	CL_BUTTON_GREY	= RGB( 220, 220, 220), /* WINDOWS 按钮表面灰色 */
//	CL_MAGENTA      = 0xF81F,	/* 红紫色，洋红色 */
//	CL_CYAN         = 0x7FFF,	/* 蓝绿色，青色 */
//	CL_BLUE1        = RGB(  0,  0, 240),		/* 深蓝色 */
//	CL_BLUE2        = RGB(  0,  0, 128),		/* 深蓝色 */
//	CL_BLUE3        = RGB(  68, 68, 255),		/* 浅蓝色1 */
//	CL_BLUE4        = RGB(  0, 64, 128),		/* 浅蓝色1 */
//	/* UI 界面 Windows控件常用色 */
//	CL_BTN_FACE		= RGB(236, 233, 216),	/* 按钮表面颜色(灰) */	
//	CL_BTN_FONT		= CL_BLACK,				/* 按钮字体颜色（黑） */	
//	CL_BOX_BORDER1	= RGB(172, 168,153),	/* 分组框主线颜色 */
//	CL_BOX_BORDER2	= RGB(255, 255,255),	/* 分组框阴影线颜色 */
//	CL_MASK			= 0x9999	/* 颜色掩码，用于文字背景透明 */
//};


//画笔颜色
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
#define tBROWN 			 0XBC40 //棕色
#define tBRRED 			 0XFC07 //棕红色
#define tGRAY  			 0X8430 //灰色
//GUI颜色
#define tDARKBLUE      	 0X01CF	//深蓝色
#define tLIGHTBLUE      	 0X7D7C	//浅蓝色  
#define tGRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define tLIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define tLGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define tLGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define tLBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

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
	    															  
void ILI9488_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//开显示
void LCD_DisplayOff(void);													//关显示
void LCD_Clear(u16 Color);	 												//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//设置光标
void LCD_DrawPoint(u16 x,u16 y);											//画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//快速画点
u16  LCD_ReadPoint(u16 x,u16 y); 											//读点 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//画圆
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//画矩形
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充单色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//填充指定颜色
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//显示 数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(u8 dir);									//设置屏扫描方向
void LCD_Display_Dir(u8 dir);								//设置屏幕显示方向
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);	//设置窗口					   						   																			 
//LCD分辨率设置
#define SSD_HOR_RESOLUTION		480		//LCD水平分辨率
#define SSD_VER_RESOLUTION		320		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		1		//水平脉宽
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		1		//垂直脉宽
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下几个参数，自动计算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
	 



