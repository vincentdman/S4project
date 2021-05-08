/**
 * @file HandleBMP180.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleBMP180_h
#define HandleBMP180_h

#include "HandleI2C.h"

class HandleBMP180 : public HandleI2C //dont forget to put to private after testing
{
    public:
    HandleBMP180();
    void BMP180_SetCalibrationData();
    uint8_t BMP180_Read_16Bit(uint8_t DataAdress);
    uint8_t test();

    private:
    const uint8_t BMP180_I2C_ADRESS_Write = 0b11101110;
    const uint8_t BMP180_I2C_ADRESS_Read  = 0b11101111;
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

};



#endif