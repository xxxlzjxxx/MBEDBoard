#ifndef __HCHO_H
#define __HCHO_H			 
#include "sys.h"	 								  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//HCHO驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	  		  	
extern u8 HCHO_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 HCHO_RX_CNT;   			//接收到的数据长度

//如果想串口中断接收，请不要注释以下宏定义
#define EN_USART1_RX 1			//0,不接收;1,接收.




void HCHO_Init(u32 bound);
void HCHO_Send_Data(u8 *buf,u8 len);
void HCHO_Receive_Data(u8 *buf,u8 *len);


#endif	   
















