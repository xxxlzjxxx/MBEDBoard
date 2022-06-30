#ifndef _BMP180_H
#define _BMP180_H
#include "sys.h"
#include "myiic.h"

typedef struct {
    uint8_t ID;
    
    short AC1;
    short AC2;
    short AC3;
    unsigned short AC4;
    unsigned short AC5;
    unsigned short AC6;
    short B1;
    short B2;
    short MB;
    short MC;
    short MD;
    long UT;
    long UP;
    long X1;
    long X2;
    long X3;
    long B3;
    unsigned long B4;
    long B5;
    long B6;
    long B7;
    
    long p;
    long Temp;
    float altitude;
}BMP180_t;



void BMP180_Init(void);
uint8_t BMP180_ReadOneByte(uint8_t ReadAddr);
short BMP180_ReadTwoByte(uint8_t ReadAddr);
void BMP180_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);
void BMP180_ReadCalibrationData(void);
long BMP_Read_UT(void);
long BMP_Read_UP(void);
uint8_t BMP180_CheckID(void);
void BMP_UncompemstatedToTrue(void);


#endif
