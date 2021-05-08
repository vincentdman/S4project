/**
 * @file HandleBMP180.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "HandleBMP180.h"
#include "driver/i2c.h"
#include "HandleI2C.h"
#include <bitset>
#include <iostream>
#include <cmath>

extern "C"
{
    HandleBMP180::HandleBMP180()
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

        BMP180_SetCalibrationData();
    }
    HandleBMP180::~HandleBMP180()
    {
        i2c_driver_delete(I2C_Port);
    }

    float HandleBMP180::GetPressure()
    {
        GetTemperature(); //update values
        return (((float)BMP180_GetTruePressure(BMP180_GetRawPressure()))/10);
    }

    float HandleBMP180::GetAltitude()
    {
        
    }

    float HandleBMP180::GetTemperature()
    {

        return (((float)BMP180_GetTrueTemperature(BMP180_GetRawTemperature()))/10);
    }

    void HandleBMP180::BMP180_SetCalibrationData()
    {
        AC1 = BMP180_Read_16Bit(0xAA);
        AC2 = BMP180_Read_16Bit(0xAC);
        AC3 = BMP180_Read_16Bit(0xAE);
        AC4 = BMP180_Read_16Bit(0xB0);
        AC5 = BMP180_Read_16Bit(0xB2);
        AC6 = BMP180_Read_16Bit(0xB4);
        B1 = BMP180_Read_16Bit(0xB6);
        B2 = BMP180_Read_16Bit(0xB8);
        MB = BMP180_Read_16Bit(0xBA);
        MC = BMP180_Read_16Bit(0xBC);
        MD = BMP180_Read_16Bit(0xBE);

        std::cout << "Calibration Data: " << AC1 << ',' << AC2 << ',' << AC3 << ',' << AC4 << ',' << AC5 << ',' << AC6 << ',' << B1 << ',' << B2 << ',' << MB << ',' << MC << ',' << MD << std::endl;
    }

    uint16_t HandleBMP180::BMP180_GetRawTemperature()
    {
        BMP180_Write_Byte(0xF4, 0x2E);
        ets_delay_us(4500);
        return BMP180_Read_16Bit(0xF6);;
    }

    long HandleBMP180::BMP180_GetTrueTemperature(uint16_t _RawTemperature)
    {
        long RawTemperature = (long)_RawTemperature;
        long X1 = (RawTemperature - AC6) * AC5 / pow(2, 15);
        long X2 = MC * pow(2, 11) / (X1 + MD);
        B5 = X1 + X2;
        return ((B5 + 8) / pow(2, 4));
    }

    uint16_t HandleBMP180::BMP180_GetRawPressure()
    {
        BMP180_Write_Byte(0xF4, 0x34);
        ets_delay_us(4500);
        return BMP180_Read_16Bit(0xF6);
    }

    long HandleBMP180::BMP180_GetTruePressure(uint16_t _RawPressure)
    {
        long RawPressure = (long)_RawPressure;
        long pressure;

        long B6 = B5 - 4000;
        long X1 = (B2 * (B6 * B6 / pow(2, 12))) / pow(2, 11);
        long X2 = AC2 * B6 / pow(2, 11);
        long X3 = X1 + X2;
        long B3 = (((long)AC1 * 4 + X3) + 2) / 4;
        X1 = AC3 * B6 / pow(2, 15);
        X2 = (B1 * (B6 * B6 / pow(2, 12))) / pow(2, 15);
        X3 = ((X1 + X2) + 2) / pow(2, 2);
        unsigned long B4 = AC4 * (unsigned long)(X3 + 32768) / pow(2, 15);
        unsigned long B7 = ((unsigned long)RawPressure - B3) * (5000);
        if (B7 < 0x80000000)
        {
            pressure = (B7 * 2) / B4;
        }
        else
        {
            pressure = (B7 / B4) * 2;
        }
        X1 = (pressure / pow(2, 8)) * (pressure / pow(2, 8));
        X1 = (X1 * 3038) / pow(2, 15);
        X2 = (-7357 * pressure) / pow(2, 15);
        return (pressure + (X1 + X2 + 3791) / pow(2, 4));
    }

    void HandleBMP180::BMP180_Write_Byte(uint8_t WriteAdress, uint8_t WriteData)
    {
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
        i2c_master_write(link_cmd, &WriteAdress, sizeof(WriteAdress) / sizeof(uint8_t), true);
        // i2c_master_stop(link_cmd);
        // i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        // i2c_cmd_link_delete(link_cmd);

        // link_cmd = i2c_cmd_link_create();
        // i2c_master_start(link_cmd);
        //i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
        i2c_master_write(link_cmd, &WriteData, sizeof(WriteData) / sizeof(uint8_t), true);
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);
    }

    uint16_t HandleBMP180::BMP180_Read_16Bit(uint8_t DataAdress)
    {
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
        i2c_master_write(link_cmd, &DataAdress, sizeof(DataAdress) / sizeof(uint8_t), true);
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        uint8_t most_significant_bit;
        uint8_t least_significant_bit;
        uint16_t Result;
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Read, true);
        i2c_master_read_byte(link_cmd, &most_significant_bit, I2C_MASTER_ACK);
        i2c_master_read_byte(link_cmd, &least_significant_bit, I2C_MASTER_LAST_NACK);
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        Result = ((uint16_t)most_significant_bit << 8) | least_significant_bit;

        return Result;
    }
}