#include "bmp180.h"
#include "delay.h"
#include "math.h"

BMP180_t BMP180;

//��ʼ��IIC�ӿ�
void BMP180_Init(void){
	IIC_Init();
}

uint8_t BMP180_ReadOneByte(uint8_t ReadAddr){				  
	uint8_t temp=0;	
    
	IIC_Start();  
	IIC_Send_Byte(0XEE);	   //оƬ��ַ+д�ź�  
	IIC_Wait_Ack(); 
	IIC_Send_Byte(ReadAddr);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XEF);           //оƬ��ַ+���ź�			   
	IIC_Wait_Ack();	 
	temp=IIC_Read_Byte(1);		   
	IIC_Stop();	  
    
	return temp;
}

short BMP180_ReadTwoByte(uint8_t ReadAddr){				  
	short temp=0;
	uint8_t msb,lsb;
    
	IIC_Start();  
	IIC_Send_Byte(0XEE);	   //оƬ��ַ+д�ź�  
	IIC_Wait_Ack(); 
	IIC_Send_Byte(ReadAddr);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XEF);           //оƬ��ַ+���ź�			   
	IIC_Wait_Ack();	 
	msb=IIC_Read_Byte(1);		
	lsb=IIC_Read_Byte(0);
	IIC_Stop();	    
	temp = msb * 256 + lsb;
	return temp;
}

void BMP180_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite){				   	  	    																 
	IIC_Start();  
	IIC_Send_Byte(0XEE);	    //����д����
	IIC_Wait_Ack();	   
	IIC_Send_Byte(WriteAddr);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
	IIC_Stop();//����һ��ֹͣ���� 
    
	delay_ms(10);	 
}

//��BMP180�Ļ�ȡ�������
void BMP180_ReadCalibrationData(void){
	BMP180.AC1 = BMP180_ReadTwoByte(0xAA);
	BMP180.AC2 = BMP180_ReadTwoByte(0xAC);
	BMP180.AC3 = BMP180_ReadTwoByte(0xAE);
	BMP180.AC4 = BMP180_ReadTwoByte(0xB0);
	BMP180.AC5 = BMP180_ReadTwoByte(0xB2);
	BMP180.AC6 = BMP180_ReadTwoByte(0xB4);
	BMP180.B1  = BMP180_ReadTwoByte(0xB6);
	BMP180.B2  = BMP180_ReadTwoByte(0xB8);
	BMP180.MB  = BMP180_ReadTwoByte(0xBA);
	BMP180.MC  = BMP180_ReadTwoByte(0xBC);
	BMP180.MD  = BMP180_ReadTwoByte(0xBE);
}

//��BMP180��ȡδ�������¶�
long BMP_Read_UT(void){
	long temp = 0;
    
	BMP180_WriteOneByte(0xF4,0x2E);
	delay_ms(5);
	temp = (long)BMP180_ReadTwoByte(0xF6);
    
	return temp;
}

//��BMP180��ȡδ�����Ĵ���ѹ
long BMP_Read_UP(void){
	long pressure = 0;
    
	BMP180_WriteOneByte(0xF4,0x34);
	delay_ms(5);
	pressure = (long)BMP180_ReadTwoByte(0xF6);
	pressure = ((pressure << 8) + BMP180_ReadOneByte(0xF8)) >> 8;
	pressure &= 0x0000FFFF;
    
	return pressure;
}

uint8_t BMP180_CheckID(void){
    BMP180.ID = BMP180_ReadOneByte(0xd0);
    return BMP180.ID;
}

//�û�ȡ�Ĳ������¶Ⱥʹ���ѹ���������������㺣��
void BMP_UncompemstatedToTrue(void){
    BMP180.UT = BMP_Read_UT();//��һ�ζ�ȡ����
    BMP180.UT = BMP_Read_UT();//���еڶ��ζ�ȡ��������
    BMP180.UP = BMP_Read_UP();

    BMP180.X1 = ((BMP180.UT - BMP180.AC6) * BMP180.AC5) >> 15;
    BMP180.X2 = (((long)BMP180.MC) << 11) / (BMP180.X1 + BMP180.MD);
    BMP180.B5 = BMP180.X1 + BMP180.X2;
    BMP180.Temp  = (BMP180.B5 + 8) >> 4;

    BMP180.B6 = BMP180.B5 - 4000;
    BMP180.X1 = ((long)BMP180.B2 * (BMP180.B6 * BMP180.B6 >> 12)) >> 11;
    BMP180.X2 = ((long)BMP180.AC2) * BMP180.B6 >> 11;
    BMP180.X3 = BMP180.X1 + BMP180.X2;

    BMP180.B3 = ((((long)BMP180.AC1) * 4 + BMP180.X3) + 2) /4;
    BMP180.X1 = ((long)BMP180.AC3) * BMP180.B6 >> 13;
    BMP180.X2 = (((long)BMP180.B1) *(BMP180.B6*BMP180.B6 >> 12)) >>16;
    BMP180.X3 = ((BMP180.X1 + BMP180.X2) + 2) >> 2;
    BMP180.B4 = ((long)BMP180.AC4) * (unsigned long)(BMP180.X3 + 32768) >> 15;
    BMP180.B7 = ((unsigned long)BMP180.UP - BMP180.B3) * 50000;

    if(BMP180.B7 < 0x80000000)
    {
        BMP180.p = (BMP180.B7 * 2) / BMP180.B4;     
    }
    else
    {
        BMP180.p = (BMP180.B7 / BMP180.B4) * 2;
    }

    BMP180.X1 = (BMP180.p >> 8) * (BMP180.p >>8);
    BMP180.X1 = (((long)BMP180.X1) * 3038) >> 16;
    BMP180.X2 = (-7357 * BMP180.p) >> 16;

    BMP180.p = BMP180.p + ((BMP180.X1 + BMP180.X2 + 3791) >> 4);

    BMP180.altitude = 44330 * (1-pow(((BMP180.p) / 101325.0),(1.0/5.255)));  
}

