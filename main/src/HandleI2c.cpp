/**
 * @file HandleI2c.cpp
 * @author Vincent de Man
 * @brief Source file for HandleI2c.cpp
 * @version 0.2
 * @date 2021-04-25
 * @details Implementation of the HandleI2C class.
 * @copyright Copyright (c) 2021
 * 
 */

#include "driver/i2c.h"
#include "HandleI2C.h"
#include <string>
#include <iostream>

/**
 * @brief Function to initialize the lcd.
 * 
 * @param Configuration the configuration struct
 * 
 * @details Function to initialize the lcd by taking in the i2c_config_t struct.
 */
void HandleI2C::I2C_Initialize(i2c_config_t &Configuration)
{
    i2c_param_config(I2C_Port, &Configuration);
    i2c_driver_install(I2C_Port, Configuration.mode, 0, 0, 0);
}

void HandleI2C::I2C_WriteData(uint8_t Data_ToSend, uint8_t slave_adress)
{
    i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
    i2c_master_start(link_cmd);
    i2c_master_write_byte(link_cmd, (slave_adress<<1) | I2C_MASTER_WRITE, true);
    i2c_master_write(link_cmd, &Data_ToSend, sizeof(Data_ToSend) / sizeof(uint8_t), true);
    i2c_master_stop(link_cmd);
    i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(link_cmd);
}

uint8_t HandleI2C::I2C_ReadByte(uint8_t slave_adress){
    uint8_t DataRead;
    i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
    i2c_master_start(link_cmd);
    i2c_master_write_byte(link_cmd, (slave_adress<<1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(link_cmd, &DataRead, I2C_MASTER_ACK);
    i2c_master_stop(link_cmd);
    i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(link_cmd);
    return DataRead;
}

HandleI2C::HandleI2C() {}

HandleI2C::~HandleI2C()
{
    i2c_driver_delete(I2C_Port);
}
