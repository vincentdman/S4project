/**
 * @file HandleI2c.cpp
 * @author Vincent de Man
 * @brief Source file for HandleI2c.cpp
 * @version 0.2
 * @date 2021-04-25
 * @details Implementation of the HandleI2C class.
 * @class HandleI2c class to make it easier to use the i2c peripheral of the esp32.
 * @copyright Copyright (c) 2021
 * 
 */

#include "driver/i2c.h"
#include "HandleI2C.h"
#include <string>
#include <iostream>

extern "C"
{

    /**
     * @brief Construct a new Handle I2C object.
     * 
     * @details Default constructor does nothing 
     */
    HandleI2C::HandleI2C() 
    {   
         
    }

    /**
    * @brief Destroy the Handle I2C object.
    * 
    * @details Deletes the driver so it sets system resources free. 
    */
    HandleI2C::~HandleI2C()
    {
        i2c_driver_delete(I2C_Port);
    }

    /**
     * @brief Construct a new HandleI2C::HandleI2C object and starts i2c with default settings.
     * 
     * @param __attribute__((unused)) IGNORE to overload the constructor.
     * 
     * @details Constructor that installs the i2c driver with default settings so i2c can be used by other components. 
     */
    HandleI2C::HandleI2C( bool __attribute__((unused)) IGNORE) 
    {   
        i2c_config_t Configuration;
        Configuration.mode = I2C_MODE_MASTER;
        Configuration.sda_io_num = 21;
        Configuration.scl_io_num = 22;
        Configuration.sda_pullup_en = GPIO_PULLUP_ENABLE;
        Configuration.scl_pullup_en = GPIO_PULLUP_ENABLE;
        Configuration.master.clk_speed = 100000;

        i2c_param_config(I2C_Port, &Configuration);
        i2c_driver_install(I2C_Port, Configuration.mode, 0, 0, 0);
    }


    /**
     * @brief Construct a new HandleI2C::HandleI2C object and initializes 
     * 
     * @param config i2c_config_t configuration struct.
     * 
     * @details Default constructor that takes in a user created structure with the I2C init data. 
     */
    HandleI2C::HandleI2C(i2c_config_t &config)
    {
        i2c_param_config(I2C_Port, &config);
        i2c_driver_install(I2C_Port, config.mode, 0, 0, 0);
    }

    /**
    * @brief Function to initialize the lcd.
    * 
    * @param Configuration the configuration struct
    * 
    * @details Function to initialize the lcd by taking in the i2c_config_t struct.
    */
    esp_err_t HandleI2C::I2C_Initialize(i2c_config_t &Configuration)
    {
        esp_err_t Error = ESP_OK; 
        Error |= i2c_param_config(I2C_Port, &Configuration);
        Error |= i2c_driver_install(I2C_Port, Configuration.mode, 0, 0, 0);
        return Error;
    }

    /**
    * @brief Function to write data as a master to slave.
    * 
    *  @param Data_ToSend The data that gets send to the slave.
    * @param slave_adress The adress of the slave device.
    * 
    * @details Function to send data to the slave. input is the data to send as uint8_t and the slave adress.
    */
    esp_err_t HandleI2C::I2C_WriteData(uint8_t Data_ToSend, uint8_t slave_adress)
    {
        esp_err_t Error = ESP_OK; 
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        Error |= i2c_master_start(link_cmd);
        Error |= i2c_master_write_byte(link_cmd, (slave_adress << 1) | I2C_MASTER_WRITE, true);
        Error |= i2c_master_write(link_cmd, &Data_ToSend, sizeof(Data_ToSend) / sizeof(uint8_t), true);
        Error |= i2c_master_stop(link_cmd);
        Error |= i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
                 i2c_cmd_link_delete(link_cmd);
        return Error;
    }

    /**
    * @brief Function to read data from the slave device.
    * 
    * @param slave_adress The adress of the slave
    * @return uint8_t DataRead that gets returned to caller of the function.
    * 
    * @details Function to read data from the slave device. 
    */
    uint8_t HandleI2C::I2C_ReadByte(uint8_t slave_adress)
    {
        uint8_t DataRead;
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (slave_adress << 1) | I2C_MASTER_READ, true);
        i2c_master_read_byte(link_cmd, &DataRead, I2C_MASTER_ACK);
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);
        return DataRead;
    }

  
}
