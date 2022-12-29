/*******************************************************************************
* File Name  ��ad7414.c
* Function   ��Function declaration achieve
* Author     ��
* Version    ��
* Description��
* Chang Log  ��
*******************************************************************************/
#include "includes.h"

/******************************************************************************
* �������ƣ�void delay_us(unsigned int delaytimes)
* �������ܣ���ʱ,Լ10us
* ��ڲ�����nValue����ʱ����
* ���ڲ�������
* �޸���־��
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
* �������ƣ�void AD7414_Init(void)
* �������ܣ�IIC�˿ڳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* �޸���־��
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
* �������ƣ�void IIC_Start(void)
* �������ܣ�IIC start
* ��ڲ�������
* ���ڲ�������
* �޸���־��
******************************************************************************/
void AD7414_I2c_Start(void)
{ 
    SDA_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_HIGH;
    SDA_AD7414_OUT_LOW;
}
/******************************************************************************
* �������ƣ�void IIC_Stop(void)
* �������ܣ�IIC Stop
* ��ڲ�������
* ���ڲ�������
* �޸���־��
******************************************************************************/
void AD7414_I2c_Stop(void)
{ 
    SDA_AD7414_OUT_LOW;
    SCL_AD7414_OUT_HIGH;
    SDA_AD7414_OUT_HIGH;
}
/******************************************************************************
* �������ƣ�void I2cAck_AD7414(void)
* �������ܣ�IIC Read ack
* ��ڲ�������
* ���ڲ�������
* �޸���־��
******************************************************************************/
void AD7414_I2cAck_Slaver(void)
{
    uchar i =0;

    SCL_AD7414_OUT_HIGH;
    while(SDA_AD7414_READ&&(i<255))  i++;  
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* �������ƣ�void I2cAck_Mcu(void)
* �������ܣ�MCU ACK TO SLAVER
* ��ڲ�������
* ���ڲ�������
* �޸���־��
******************************************************************************/
void AD7414_I2cAck_Mcu(void)
{
    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_LOW;
    SCL_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* �������ƣ�void I2cNoAck_Mcu(void)
* �������ܣ�MCU NOACK  TO SLAVER
* ��ڲ�������
* ���ڲ�������
* �޸���־��
******************************************************************************/
void AD7414_I2cNoAck_Mcu(void)
{ 
//    SCL_AD7414_OUT_LOW;
    SDA_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_HIGH;
    SCL_AD7414_OUT_LOW;
}
/******************************************************************************
* �������ƣ�void IIC_I2cWriteByte(unsigned char wbyte)
* �������ܣ�IIC write a byte to slaver
* ��ڲ�����wbyte:The Writed data to slaver
* ���ڲ�������
* �޸���־��
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
* �������ƣ�unsigned char IIC_I2cReadByte(void)
* �������ܣ�IIC read a byte
* ��ڲ�������
* ���ڲ�����rbyte��IIC read d byte from slavr
* �޸���־��
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
* �������ƣ�float  AD7414_Read_Temp(unsigned char addr)
* ��������: Read temprature data
* ��ڲ�����addr:the register to temp
* ���ڲ�����temp:the real temp
* �޸���־��
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
    if(TempCode & 0x200)                 //���¶� Ӧ��
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