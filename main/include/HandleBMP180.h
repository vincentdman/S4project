/**
 * @file HandleBMP180.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * @details Header that includes the BMP180 specific functions. 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleBMP180_h
#define HandleBMP180_h

#include "HandleI2C.h"
extern "C"{
class HandleBMP180  
{
    public:
    HandleBMP180();
    ~HandleBMP180();

    float GetPressure();
    float GetTemperature();
    float GetAltitude();

    void BMP180_SetCalibrationData();
    uint16_t BMP180_GetRawTemperature();
    long BMP180_GetTrueTemperature(uint16_t RawTemperature);
    
    uint16_t BMP180_GetRawPressure();
    long BMP180_GetTruePressure(uint16_t RawPressure);

    void BMP180_Write_Byte(uint8_t WriteAdress, uint8_t Data);
    uint16_t BMP180_Read_16Bit(uint8_t DataAdress);
    

    private:
    
    const uint8_t BMP180_I2C_ADRESS_Write = 0b11101110;
    const uint8_t BMP180_I2C_ADRESS_Read  = 0b11101111;

    i2c_port_t I2C_Port = I2C_NUM_1;

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

    long B5;

};

}

#endif