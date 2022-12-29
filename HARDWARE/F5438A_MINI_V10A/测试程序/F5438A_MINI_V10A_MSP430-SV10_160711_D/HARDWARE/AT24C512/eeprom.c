/*******************************************************************************
** 文件名称：eeprom.c
** 功    能：
** 修改日志：
********************************************************************************/

#include "includes.h"

/*******************************************************************************
** 函数名称：void I2cInit(void)
** 功   能： 将总线拉高以释放总线
** 修改日志：
*******************************************************************************/
void I2cInit(void)
{
  SDA_SEL_GPIO;
  SCL_SEL_GPIO;
  WP_SEL_GPIO;
  
  SCL_DIR_OUTPUT;
  SDA_DIR_OUTPUT;
  WP_DIR_OUTPUT;
  
  SCL_OUT_HIGH;
  SDA_OUT_HIGH;
  WP_OUT_LOW; 
}
/*******************************************************************************
** 函数名称：void I2cStart(void)
** 功   能： SCL在高电平期间，SDA一个下降沿启动信号
** 修改日志：
*******************************************************************************/
void I2cStart(void)
{
    SCL_DIR_OUTPUT;
    SDA_DIR_OUTPUT;
    SDA_OUT_HIGH;
    SCL_OUT_HIGH;   
    SDA_OUT_LOW;
}
/*******************************************************************************
** 函数名称：void I2cStop(void)
** 功   能： SCL在高电平期间，SDA一个上升沿停止信号
** 修改日志：
*******************************************************************************/
void I2cStop(void)
{
    SDA_DIR_OUTPUT;    
    SDA_OUT_LOW;
    SCL_OUT_HIGH; 
    SDA_OUT_HIGH; 
}
/*******************************************************************************
** 函数名称：void I2cAck_Eeprom()
** 功   能： SCL在高电平期间，SDA被从设备拉为低电平表示应答 Eeprom应答
** 修改日志：
*******************************************************************************/
void I2cAck_Eeprom(void)
{
    uchar i =0;
    SDA_DIR_INPUT;
    SCL_OUT_HIGH; 
    while(SDA_READ&&(i<255))  i++;  
    SCL_OUT_LOW;
}
/*******************************************************************************
** 函数名称：void I2cAck_Cpu()
** 功   能： SCL在高电平期间，SDA输出低电平表示应答 CPU应答
** 修改日志：
*******************************************************************************/
void I2cAck_Cpu(void)
{
    SDA_DIR_OUTPUT;
    SDA_OUT_LOW;
    SCL_OUT_HIGH;
    SCL_OUT_LOW;
}
/*******************************************************************************
** 函数名称：void I2cNoAck_Cpu()
** 功   能： 
** 修改日志：
*******************************************************************************/
void I2cNoAck_Cpu(void)
{
    SDA_DIR_OUTPUT;
    SDA_OUT_HIGH;
    SCL_OUT_HIGH;
    SCL_OUT_LOW;
}

/*******************************************************************************
** 函数名称：void I2cWriteByte(unsigned char wbyte)
** 功   能： 
** 修改日志：
*******************************************************************************/
void I2cWriteByte(unsigned char wbyte)
{
    SDA_DIR_OUTPUT;   
    for(unsigned char i=0; i<8; i++){
        SCL_OUT_LOW;
        delay_us(20);
        if(wbyte & 0x80){
          SDA_OUT_HIGH;
        }
        else{
          SDA_OUT_LOW;
        }
         wbyte <<=1;
         SCL_OUT_HIGH;
         delay_us(20);
     }
    SCL_OUT_LOW;
    delay_us(10);
    SDA_OUT_HIGH;
    delay_us(10);
}
/*******************************************************************************
** 函数名称：unsigned char I2cReadByte(void)
** 功   能： 
** 修改日志：
*******************************************************************************/
unsigned char I2cReadByte(void)
{
    unsigned char rbyte=0;
    SCL_OUT_LOW;
    SDA_DIR_INPUT;  
    for( unsigned char i=0; i<8; i++)
    {
      SCL_OUT_HIGH;
      rbyte<<=1;
      if(SDA_READ)
      {
        rbyte |=1;;
      }
       SCL_OUT_LOW;
    }
    return rbyte;
}

/*******************************************************************************
** 函数名称：void EepromByteWrite(unsigned int addr,unsigned char wdata)
** 功   能： 
** 修改日志：
*******************************************************************************/
void EepromByteWrite(unsigned int page,unsigned char wdata)
{
    unsigned int addr;
    addr = page<<7;   
    I2cStart();
    I2cWriteByte(0xa0);
    I2cAck_Eeprom();
    I2cWriteByte(*(1+(char*)&addr));
    I2cAck_Eeprom();
    I2cWriteByte(*(char*)&addr);
    I2cAck_Eeprom();
    I2cWriteByte(wdata);
    I2cAck_Eeprom();
    I2cStop();
    delay_us(20);
}
/*******************************************************************************
** 函数名称：unsigned char EepromByteRead(unsigned int page)
** 功   能： 
** 修改日志：
*******************************************************************************/
unsigned char EepromByteRead(unsigned int page)
{
    unsigned char buffer;
    unsigned int  addr;
    addr = page<<7;   
    I2cStart();
    I2cWriteByte(0xa0);
    I2cAck_Eeprom();    
    I2cWriteByte(*(1+(char*)&addr));
    I2cAck_Eeprom();
    I2cWriteByte(*(char*)&addr);
    I2cAck_Eeprom();
    I2cStart();
    I2cWriteByte(0xa1);
    I2cAck_Eeprom();
    buffer=I2cReadByte();
    I2cStop();
    return buffer;    
}
/*******************************************************************************
** 函数名称：void delay_us(unsigned int delaytimes)
** 功   能： 
** 修改日志：
*******************************************************************************/
//void delay_us(unsigned int delaytimes)
//{
//    unsigned char dely;
//    while(delaytimes--)
//    {
//        dely=13;
//        for (;--dely;);
//    }
//}
/*******************************************************************************
** 函数名称：void EepromWritePage(unsigned int page,unsigned char  * buf,unsigned char len)
** 功   能： 页写函数
** 修改日志：
*******************************************************************************/
void EepromWritePage(unsigned int page,unsigned char * buf,unsigned char len)
{ 
    unsigned int addr=0;
    addr = page<<7;
    I2cStart();
    I2cWriteByte(0xa0);
    I2cAck_Eeprom();
    I2cWriteByte(*(1+(char*)&addr));   
    I2cAck_Eeprom();
    I2cWriteByte(*(char*)&addr);
    I2cAck_Eeprom();
    for(unsigned char  i=0; i<len; i++)
    {
      I2cWriteByte(buf[i]);
      I2cAck_Eeprom();
   
    }    
    I2cStop();
    delay_ms(10);
//  Delay_10ms(1);         /*根据芯片手册延时10ms*/
  
    return ;
}
/*****************************************************************************
** 文件名称：void EepromWriteMorePage(unsigned int page,unsigned char * pbuf,unsigned int len)
** 功    能：多页写函数
** 修改日志：
******************************************************************************/
void EepromWriteMorePage(unsigned int page,unsigned char * pbuf,unsigned int len)
{
   unsigned int Write_Page_Num=0;

   Write_Page_Num = len/128;
   if((len%128) !=0) Write_Page_Num +=1;
   for(unsigned int i=0; i<Write_Page_Num; i++)
   {    
     EepromWritePage(page+i,pbuf,128);
     pbuf = pbuf+128;   
   }
   return ;
}
/*******************************************************************************
** 函数名称：void EepromSequentialRead(unsigned int addr,unsigned char * buf,unsigned int len)
** 功   能： 
** 修改日志：
*******************************************************************************/
void EepromSequentialRead(unsigned int page,unsigned char * buf,unsigned int len)
{
    unsigned int addr;
    addr = page<<7;
    I2cStart();
    I2cWriteByte(0xa0);
    I2cAck_Eeprom();
    I2cWriteByte(*(1+(char*)&addr));
    I2cAck_Eeprom();
    I2cWriteByte(*(char*)&addr);
    I2cAck_Eeprom(); 
    I2cStart();
    I2cWriteByte(0xa1);
    I2cAck_Eeprom();  
    for(unsigned int i=0;i<len;i++)
    {
//      WDI_OUT_OVERTURN;                           /*外部看门狗喂狗    */    
      buf[i]=I2cReadByte();   
      if(i !=(len -1))
         I2cAck_Cpu();
      else
         I2cNoAck_Cpu();
      delay_us(1);            
    }
    I2cStop();
    delay_us(20);
    return ;
}

