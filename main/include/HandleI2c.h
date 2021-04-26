/**
 * @file HandleI2c.h
 * @author Vincent de Man
 * @brief Header file for HandleI2c
 * @version 0.1
 * @date 2021-04-25
 * @details 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleI2C_H
#define HandleI2C_H


#include "driver/i2c.h"
#include "driver/gpio.h"
#include <string>
#include "esp_err.h"


class HandleI2C{

    public:
    HandleI2C();

    ~HandleI2C();
    void I2C_WriteData(uint8_t Data_ToSend, uint8_t slave_adress);
    void I2C_ReadString(std::string);
    esp_err_t I2C_TestConncetion();
    void I2C_Initialize(i2c_config_t &Configuration); 
    

    private:
    i2c_port_t I2C_Pin = GPIO_NUM_NC; 
    i2c_cmd_handle_t link_cmd;
};




#endif