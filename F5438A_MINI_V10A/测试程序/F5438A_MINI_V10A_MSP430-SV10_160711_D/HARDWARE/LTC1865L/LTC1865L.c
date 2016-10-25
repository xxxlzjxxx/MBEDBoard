
#include        "includes.h"

void delay (uint16_t i)
  {
    uint16_t jj=0,kk=0;
    for(jj=0;jj<i;jj++)
      for(kk=0;kk<3;kk++);
  }

/*****************************************************************************
** 文件名称：uint16_t SPIFlash_GPIO_GetBit(void)
** 功    能：读取一位数据
** 修改日志：
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
** 文件名称：void SpiAD_WriteTwoBit(uint8_t SDIBuffer)
** 功    能：写入两个BIT
** 修改日志：
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
    	SPIAD_Set_SCLK;                 //时钟线拉高，产生上升沿写入数据
    	SDIBuffer <<= 1;
    	_NOP();_NOP();
    	_NOP();_NOP();
  	}
  	SPIAD_Clr_SCLK;
  	SPIAD_Set_Conv;               //拉高控制位,开始软换
//  SPIAD_Set_DO;                //数据传送完毕，MOSI数据线置高表示空闲状态
}
/*****************************************************************************
** 文件名称：uint16_t SpiAD_ReadTwoByte(void)
** 功    能：读取SPI 2个字节数据
** 修改日志：
******************************************************************************/
uint16_t SpiAD_ReadTwoByte(void)
{
    SPIAD_Clr_Conv;
    uint8_t BitCount = 0;
    unsigned int retValue = 0;
    SPIAD_Clr_SCLK;            //时钟线拉高,恢复时钟线为低电平

    for(BitCount = 0;BitCount < 16; BitCount++)
    {
        retValue <<= 1;
        SPIAD_Set_SCLK;            //时钟线拉高,恢复时钟线为高电平
        if(SPIAD_Get_DI)
        {
            retValue |= 0x0001;
        }
        else
        {
            retValue &= 0xFFFE;
        }
        SPIAD_Clr_SCLK;            //时钟线拉低,产生下降沿读出数据
        _NOP();_NOP();_NOP();_NOP(); 
        _NOP();_NOP();_NOP();_NOP();    
    }
    SPIAD_Set_Conv;
    SPIAD_Set_SCLK;
    return (retValue);
}
/*****************************************************************************
** 文件名称：uint16_t LTC1865L_Read(uint8_t channel)
** 功    能：读取一个channel的数据
** 修改日志：
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