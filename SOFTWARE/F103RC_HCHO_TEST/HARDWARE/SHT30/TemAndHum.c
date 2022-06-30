
#include "TemAndHum.h"
#include "delay.h"
#include "myiic.h"

#define  i2cAddWrite_8bit           0x88
#define  i2cAddRead_8bit            0x89
/*CRC*/
#define POLYNOMIAL             0x131   // P(x) = x^8 + x^5 + x^4 + 1 = 100110001

float Tem_Value = 0.0;
float  RH_Value = 0.0;

u8 buffer[6];

void SHT3X_WriteCMD(u16 cmd)
{
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd>>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(10);
}

void SHT3X_SetPeriodicMeasurement()
{
    SHT3X_WriteCMD(CMD_MEAS_PERI_2_H);
}

void SHT3X_ReadState(u8 *temp)
{
    IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);
	IIC_Wait_Ack();
	IIC_Send_Byte(0xf3);
	IIC_Wait_Ack();
	IIC_Send_Byte(0X2d);
	IIC_Wait_Ack();
//     IIC_Stop(); 
	delay_ms(100);
    IIC_Start();
	IIC_Send_Byte(i2cAddRead_8bit);
	IIC_Wait_Ack();

	temp[0] = IIC_Read_Byte(1);
//	IIC_Ack();
	temp[1] = IIC_Read_Byte(1);
//	IIC_Ack();
	temp[2] = IIC_Read_Byte(0);
//	IIC_NAck(); 
	IIC_Stop(); 
}

void SHX3X_ReadResults(u16 cmd,  u8 *p)
{
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd>>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);
	IIC_Wait_Ack();
//	IIC_Stop();
	
	delay_ms(10);
	IIC_Start();
	IIC_Send_Byte(i2cAddRead_8bit);
	IIC_Wait_Ack();

	p[0] = IIC_Read_Byte(1);
//	IIC_Ack();
	p[1] = IIC_Read_Byte(1);
//	IIC_Ack();
	p[2] = IIC_Read_Byte(1);
//	IIC_Ack();
	p[3] = IIC_Read_Byte(1);
//	IIC_Ack();
	p[4] = IIC_Read_Byte(1);
//	IIC_Ack();
	p[5] =IIC_Read_Byte(0);
//	IIC_NAck();
	IIC_Stop();
	delay_ms(10);
}


u8 IC_Read_Byte(void)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA…Ë÷√Œ™ ‰»Î
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }			
return receive;	
}

void SHT_Init(void)
{
    delay_ms(200); /* Must add delay */
    SHT3X_SetPeriodicMeasurement();
    delay_ms(200); /* Must add delay */
}

u8 SHT3X_CalcCrc(uint8_t *data, uint8_t nbrOfBytes)
{
	uint8_t bit;        // bit mask
    uint8_t crc = 0xFF; // calculated checksum
    uint8_t byteCtr;    // byte counter

    // calculates 8-Bit checksum with given polynomial
    for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++) {
        crc ^= (data[byteCtr]);
        for(bit = 8; bit > 0; --bit) {
            if(crc & 0x80) {
                crc = (crc << 1) ^ POLYNOMIAL;
            }  else {
                crc = (crc << 1);
            }
        }
    }
	return crc;
}

u8 SHT3X_CheckCrc(uint8_t *pdata, uint8_t nbrOfBytes, uint8_t checksum)
{
    uint8_t crc;
	crc = SHT3X_CalcCrc(pdata, nbrOfBytes);// calculates 8-Bit checksum
    if(crc != checksum) 
    {   
        return 1;           
    }
    return 0;              
}

float SHT3X_CalcTemperature(uint16_t rawValue)
{
    // calculate temperature 
    float temp;
    temp = (175 * (float)rawValue / 65535 - 45) ; // T = -45 + 175 * rawValue / (2^16-1)
    return temp;
}

float SHT3X_CalcRH(uint16_t rawValue)
{
    // calculate relative humidity [%RH]
    float temp1 = (100 * (float)rawValue / 65535) ;  // RH = rawValue / (2^16-1) * 100

    return temp1;
}

void SHT_GetValue(void)
{	
    u8 temp = 0;
    u16 dat;
    u8 p[3];
    
    SHX3X_ReadResults(CMD_FETCH_DATA, buffer);
    /* check tem */
    p[0] = buffer[0];
    p[1] = buffer[1];
    p[2] = buffer[2];
    temp = SHT3X_CheckCrc(p,2,p[2]);
   if( !temp ) /* value is ture */
    {
        dat = ((u16)buffer[0] << 8) | buffer[1];
        Tem_Value = SHT3X_CalcTemperature( dat );    
    }
    /* check humidity */
    p[0] = buffer[3];
    p[1] = buffer[4];
    p[2] = buffer[5];
    temp = SHT3X_CheckCrc(p,2,p[2]);
    if( !temp )
    {
        dat = ((u16)p[0] << 8) | p[1];
        RH_Value = SHT3X_CalcRH( dat ); 
    }
}







