
#ifndef __INCLUDES_H
#define __INCLUDES_H

#define uchar unsigned char  
#define uint unsigned int
#define ushort unsigned short 

//******************************************************************************

#define HighBytePosition 1	//定义串口高低字节顺序。若为1，高字节在前；若为0，高字节在后。

//******************************************************************************

#include        "msp430f5438a.h"

#include 		"math.h"
#include 		"stdio.h"
#include        "string.h"

#include        "wdog.h"
#include        "GPIO.h"
#include        "sysclk.h"
#include        "fft.h"
#include        "timer.h"
#include        "uart.h"
#include        "adc12.h"
#include        "check.h"
#include        "delay.h"

#include        "LTC1865L.h"
#include        "ad7414.h"
#include        "eeprom.h"
#include        "oled.h"
#include        "oledfont.h"


#endif