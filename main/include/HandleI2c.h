/**
 * @file HandleI2c.h
 * @author Vincent de Man
 * @brief Header file for HandleI2c (.h)
 * @version 1.1
 * @date 2021-04-25
 * @details Header for the HandleI2c class. This class makes it easy to use the i2c peripheral of the esp32.
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleI2C_H
#define HandleI2C_H

#include "driver/i2c.h"
#include "driver/gpio.h"
#include <string>
#include "esp_err.h"

extern "C"{

class HandleI2C
{

public:
    HandleI2C();
    ~HandleI2C();
    
    void I2C_WriteData(uint8_t Data_ToSend, uint8_t slave_adress);
    uint8_t I2C_ReadByte(uint8_t slave_adress);
    esp_err_t I2C_TestConncetion();
    void I2C_Initialize(i2c_config_t &Configuration);

private:
    i2c_port_t I2C_Port = I2C_NUM_1;
};
}
#endif