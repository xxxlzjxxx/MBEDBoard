
#include        "includes.h"

void delay (uint16_t i)
  {
    uint16_t jj=0,kk=0;
    for(jj=0;jj<i;jj++)
      for(kk=0;kk<3;kk++);
  }

/*****************************************************************************
** �ļ����ƣ�uint16_t SPIFlash_GPIO_GetBit(void)
** ��    �ܣ���ȡһλ����
** �޸���־��
******************************************************************************/
uint16_t SpiAD_GPIO_GetBit(void)
{
  uint16_t retValue = 0;
  uint16_t valueTemp = 0;
  valueTemp = P4IN;
  retValue = (valueTemp & BIT0);            
  return retValue;
}

/*****************************************************************************
** �ļ����ƣ�void SpiAD_WriteTwoBit(uint8_t SDIBuffer)
** ��    �ܣ�д������BIT
** �޸���־��
******************************************************************************/
void SpiAD_WriteTwoBit(uint8_t SDIBuffer)
{
  	uint8_t BitCount=0;
  	
	SPIAD_Set_SCLK;
  	SPIAD_Clr_Conv;
  	for(BitCount = 0; BitCount < 16; BitCount++)
  	{
    	SPIAD_Clr_SCLK;
    	if(SDIBuffer & 0x02)
    	{
      		SPIAD_Set_DO;
    	}
    	else
    	{
      		SPIAD_Clr_DO;
    	}
    	SPIAD_Set_SCLK;                 //ʱ�������ߣ�����������д������
    	SDIBuffer <<= 1;
    	_NOP();_NOP();
    	_NOP();_NOP();
  	}
  	SPIAD_Clr_SCLK;
  	SPIAD_Set_Conv;               //���߿���λ,��ʼ��
//  SPIAD_Set_DO;                //���ݴ�����ϣ�MOSI�������ø߱�ʾ����״̬
}
/*****************************************************************************
** �ļ����ƣ�uint16_t SpiAD_ReadTwoByte(void)
** ��    �ܣ���ȡSPI 2���ֽ�����
** �޸���־��
******************************************************************************/
uint16_t SpiAD_ReadTwoByte(void)
{
    SPIAD_Clr_Conv;
    uint8_t BitCount = 0;
    unsigned int retValue = 0;
    SPIAD_Clr_SCLK;            //ʱ��������,�ָ�ʱ����Ϊ�͵�ƽ

    for(BitCount = 0;BitCount < 16; BitCount++)
    {
        retValue <<= 1;
        SPIAD_Set_SCLK;            //ʱ��������,�ָ�ʱ����Ϊ�ߵ�ƽ
        if(SPIAD_Get_DI)
        {
            retValue |= 0x0001;
        }
        else
        {
            retValue &= 0xFFFE;
        }
        SPIAD_Clr_SCLK;            //ʱ��������,�����½��ض�������
        _NOP();_NOP();_NOP();_NOP(); 
        _NOP();_NOP();_NOP();_NOP();    
    }
    SPIAD_Set_Conv;
    SPIAD_Set_SCLK;
    return (retValue);
}
/*****************************************************************************
** �ļ����ƣ�uint16_t LTC1865L_Read(uint8_t channel)
** ��    �ܣ���ȡһ��channel������
** �޸���־��
******************************************************************************/
uint16_t LTC1865L_Read(uint8_t channel)
{
    uint16_t ADC_value = 0;
    SpiAD_WriteTwoBit(channel);
    delay(10);
    ADC_value = SpiAD_ReadTwoByte();
	_NOP();
    return ADC_value;
}