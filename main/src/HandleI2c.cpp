/**
 * @file HandleI2c.cpp
 * @author Vincent de Man
 * @brief Source file for HandleI2c.cpp
 * @version 0.1
 * @date 2021-04-25
 * @details
 * @copyright Copyright (c) 2021
 * 
 */

#include "driver/i2c.h"
#include "HandleI2C.h"
#include <string>
#include <iostream>

void HandleI2C::I2C_Initialize(i2c_config_t &Configuration)
{
    I2C_Pin = Configuration.sda_io_num;
    i2c_driver_install(I2C_Pin, Configuration.mode, 0, 0, 0);
}


void HandleI2C::I2C_WriteData(uint8_t Data_ToSend, uint8_t slave_adress)
{
    link_cmd = i2c_cmd_link_create();
    i2c_master_start(link_cmd);
    i2c_master_write_byte(link_cmd, slave_adress, true);
    i2c_master_write(link_cmd, &Data_ToSend, sizeof(Data_ToSend) / sizeof(uint8_t), true);
    i2c_master_stop(link_cmd);
    i2c_master_cmd_begin(I2C_Pin, link_cmd, 0xffff);
    i2c_cmd_link_delete(link_cmd);
}

HandleI2C::HandleI2C() {}

HandleI2C::~HandleI2C()
{
    i2c_driver_delete(I2C_Pin);
}
