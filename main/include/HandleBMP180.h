/**
 * @file HandleBMP180.h
 * @author Vincent de Man
 * @brief Handler of BMP180 sensor (.h)
 * @version 1.1
 * @date 2021-05-08
 * @details Header that includes the BMP180 specific functions. 
 * @copyright Copyright (c) 2021
 * @details Header file of Handle BMP180 class. It makes it a lot easier to work with the BMP180. 
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

    [[nodiscard]]float GetPressure();
    [[nodiscard]]float GetTemperature();
    [[nodiscard]]float GetAltitude();


    private:
    void BMP180_SetCalibrationData();

    uint16_t BMP180_GetRawTemperature();
    uint16_t BMP180_GetRawPressure();

    long BMP180_GetTrueTemperature(const uint16_t RawTemperature);
    long BMP180_GetTruePressure(const uint16_t RawPressure);

    esp_err_t BMP180_Write_Byte(uint8_t WriteAdress, uint8_t Data);
    uint16_t BMP180_Read_16Bit(uint8_t DataAdress);

    const uint8_t BMP180_I2C_ADRESS_Write = 0b11101110;
    const uint8_t BMP180_I2C_ADRESS_Read  = 0b11101111;

    const i2c_port_t I2C_Port = I2C_NUM_1;

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

    constexpr static const char* TAG = "BMP180";

};

}

#endif