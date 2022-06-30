/*******************************************************************************
* File Name  ：ad7414.c
* Function   ：Function declaration achieve
* Author     ：
* Version    ：
* Description：
* Chang Log  ：
*******************************************************************************/
#include "includes.h"

/******************************************************************************
* 函数名称：void delay_us(unsigned int delaytimes)
* 函数功能：延时,约10us
* 入口参数：nValue：延时变量
* 出口参数：无
* 修改日志：
******************************************************************************/
void delay_usad7414(unsigned int delaytimes)
{
    unsigned char dely;
    while(delaytimes--)
    {
        dely=13;
        for (;--dely;);
    }
}
/******************************************************************************
* 函数名称：void AD7414_Init(void)
* 函数功能：IIC端口初始化
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_Init(void)
{
    SDA_AD7414_SEL_GPIO;
    SCL_AD7414_SEL_GPIO;
    AD7414_ALT_SEL_GPIO;
    SCL_AD7414_DIR_OUTPUT;
    SDA_AD7414_DIR_OUTPUT;
    AD7414_ALT_DIR_INPUT;

    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_LOW;
}
/******************************************************************************
* 函数名称：void IIC_Start(void)
* 函数功能：IIC start
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2c_Start(void)
{ 
    SDA_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_HIGH;
    SDA_AD7414_OUT_LOW;
}
/******************************************************************************
* 函数名称：void IIC_Stop(void)
* 函数功能：IIC Stop
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2c_Stop(void)
{ 
    SDA_AD7414_OUT_LOW;
    SCL_AD7414_OUT_HIGH;
    SDA_AD7414_OUT_HIGH;
}
/******************************************************************************
* 函数名称：void I2cAck_AD7414(void)
* 函数功能：IIC Read ack
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2cAck_Slaver(void)
{
    uchar i =0;

    SCL_AD7414_OUT_HIGH;
    while(SDA_AD7414_READ&&(i<255))  i++;  
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* 函数名称：void I2cAck_Mcu(void)
* 函数功能：MCU ACK TO SLAVER
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2cAck_Mcu(void)
{
    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_LOW;
    SCL_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* 函数名称：void I2cNoAck_Mcu(void)
* 函数功能：MCU NOACK  TO SLAVER
* 入口参数：无
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2cNoAck_Mcu(void)
{ 
//    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* 函数名称：void IIC_I2cWriteByte(unsigned char wbyte)
* 函数功能：IIC write a byte to slaver
* 入口参数：wbyte:The Writed data to slaver
* 出口参数：无
* 修改日志：
******************************************************************************/
void AD7414_I2cWriteByte(unsigned char wbyte)
{
    for(unsigned char i = 0; i < 8; i++)
    {
        SCL_AD7414_OUT_LOW;
        delay_usad7414(20);
        if(wbyte & 0x80)
        {
          	SDA_AD7414_OUT_HIGH;
        }
        else
        {
          	SDA_AD7414_OUT_LOW;
        }
        wbyte <<=1;
        SCL_AD7414_OUT_HIGH;
        delay_usad7414(10);
     }
    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_HIGH;
}
/******************************************************************************
* 函数名称：unsigned char IIC_I2cReadByte(void)
* 函数功能：IIC read a byte
* 入口参数：无
* 出口参数：rbyte：IIC read d byte from slavr
* 修改日志：
******************************************************************************/
unsigned char AD7414_I2cReadByte(void)
{
    unsigned char i, rbyte=0;
    SCL_AD7414_OUT_LOW;
    SDA_AD7414_DIR_INPUT;
    asm("nop");asm("nop");
    for(i=0; i<8; i++)
    {
      	SCL_AD7414_OUT_HIGH;
      	rbyte<<=1;
      	if(SDA_AD7414_READ)rbyte |=1;
      	SCL_AD7414_OUT_LOW;
      	delay_usad7414(5);
    }
    return rbyte;
}
/******************************************************************************
* 函数名称：float  AD7414_Read_Temp(unsigned char addr)
* 函数功能: Read temprature data
* 入口参数：addr:the register to temp
* 出口参数：temp:the real temp
* 修改日志：
******************************************************************************/
float AD7414_Read_Temp(void)
{
    unsigned int TempH = 0;	//high 8
    unsigned int TempL = 0;	//low 8
    unsigned int TempCode = 0;	
    float temp = 0.0;			//Temperature

	AD7414_Init();
    AD7414_I2c_Start();
    AD7414_I2cWriteByte(AD7414_WriteDeviceAddress);
    AD7414_I2cAck_Slaver();
    AD7414_I2cWriteByte(AD7414IICAddress);
    AD7414_I2cAck_Slaver();
    AD7414_I2c_Stop();

    AD7414_I2c_Start();
    AD7414_I2cWriteByte(AD7414_ReadDeviceAddress);
    AD7414_I2cAck_Slaver();
    TempH = AD7414_I2cReadByte();
	
	Ext_Wdog_Feed();
	
    AD7414_I2cAck_Mcu();
    TempL = AD7414_I2cReadByte();
	
	Ext_Wdog_Feed();
	
    AD7414_I2cNoAck_Mcu();
    AD7414_I2c_Stop();
    TempCode = (TempH << 8) | TempL;
    TempCode = TempCode >> 6;
    if(TempCode & 0x200)                 //负温度 应变
    {
      	TempCode &= 0x1ff;
      	temp = ((float)TempCode - 512) / 4;
    }
    else
    {
        temp = (float)TempCode / 4;
    }
    SDA_AD7414_OUT_LOW ;
    SCL_AD7414_OUT_LOW ;
    SDA_AD7414_DIR_INPUT;
    SCL_AD7414_DIR_INPUT;
    
	return temp;
}