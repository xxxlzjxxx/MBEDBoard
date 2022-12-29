/*******************************************************************************
** �ļ����ƣ�eeprom.c
** ��    �ܣ�
** �޸���־��
********************************************************************************/

#include "includes.h"

/*******************************************************************************
** �������ƣ�void I2cInit(void)
** ��   �ܣ� �������������ͷ�����
** �޸���־��
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
** �������ƣ�void I2cStart(void)
** ��   �ܣ� SCL�ڸߵ�ƽ�ڼ䣬SDAһ���½��������ź�
** �޸���־��
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
** �������ƣ�void I2cStop(void)
** ��   �ܣ� SCL�ڸߵ�ƽ�ڼ䣬SDAһ��������ֹͣ�ź�
** �޸���־��
*******************************************************************************/
void I2cStop(void)
{
    SDA_DIR_OUTPUT;    
    SDA_OUT_LOW;
    SCL_OUT_HIGH; 
    SDA_OUT_HIGH; 
}
/*******************************************************************************
** �������ƣ�void I2cAck_Eeprom()
** ��   �ܣ� SCL�ڸߵ�ƽ�ڼ䣬SDA�����豸��Ϊ�͵�ƽ��ʾӦ�� EepromӦ��
** �޸���־��
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
** �������ƣ�void I2cAck_Cpu()
** ��   �ܣ� SCL�ڸߵ�ƽ�ڼ䣬SDA����͵�ƽ��ʾӦ�� CPUӦ��
** �޸���־��
*******************************************************************************/
void I2cAck_Cpu(void)
{
    SDA_DIR_OUTPUT;
    SDA_OUT_LOW;
    SCL_OUT_HIGH;
    SCL_OUT_LOW;
}
/*******************************************************************************
** �������ƣ�void I2cNoAck_Cpu()
** ��   �ܣ� 
** �޸���־��
*******************************************************************************/
void I2cNoAck_Cpu(void)
{
    SDA_DIR_OUTPUT;
    SDA_OUT_HIGH;
    SCL_OUT_HIGH;
    SCL_OUT_LOW;
}

/*******************************************************************************
** �������ƣ�void I2cWriteByte(unsigned char wbyte)
** ��   �ܣ� 
** �޸���־��
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
** �������ƣ�unsigned char I2cReadByte(void)
** ��   �ܣ� 
** �޸���־��
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
** �������ƣ�void EepromByteWrite(unsigned int addr,unsigned char wdata)
** ��   �ܣ� 
** �޸���־��
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
** �������ƣ�unsigned char EepromByteRead(unsigned int page)
** ��   �ܣ� 
** �޸���־��
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
** �������ƣ�void delay_us(unsigned int delaytimes)
** ��   �ܣ� 
** �޸���־��
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
** �������ƣ�void EepromWritePage(unsigned int page,unsigned char  * buf,unsigned char len)
** ��   �ܣ� ҳд����
** �޸���־��
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
//  Delay_10ms(1);         /*����оƬ�ֲ���ʱ10ms*/
  
    return ;
}
/*****************************************************************************
** �ļ����ƣ�void EepromWriteMorePage(unsigned int page,unsigned char * pbuf,unsigned int len)
** ��    �ܣ���ҳд����
** �޸���־��
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
** �������ƣ�void EepromSequentialRead(unsigned int addr,unsigned char * buf,unsigned int len)
** ��   �ܣ� 
** �޸���־��
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
//      WDI_OUT_OVERTURN;                           /*�ⲿ���Ź�ι��    */    
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

