/**
 * @file HandleBMP180.cpp
 * @author your name (you@domain.com)
 * @brief Handler of BMP180 sensor (.cpp)
 * @version 0.1
 * @date 2021-05-08
 * @class HandleBMP180 Advanced class to get data from the sensor.
 * @copyright Copyright (c) 2021
 * @details Implementation of the handle BMP180 class. It uses calculations to convert data from the sensor to true data.
 * 
 */

#include "HandleBMP180.h"
#include "driver/i2c.h"
#include "HandleI2C.h"
#include <bitset>
#include <iostream>
#include <cmath>
#include "esp_log.h"



extern "C"
{
    /**
     * @brief Construct a new HandleBMP180::HandleBMP180object,
     *
     * @details Sets up a default I2C connection. And asks the BMP180 for the calibration coeficients.  
     */
    HandleBMP180::HandleBMP180()
    {
        ESP_LOGI(TAG,"Constructor BMP180 called.\n");
        BMP180_SetCalibrationData();
    }

    /**
     * @brief Destroy the HandleBMP180::HandleBMP180 object.
     * 
     * @details Destroys the HandleBMP180 object.
     */
    HandleBMP180::~HandleBMP180()
    {
       ESP_LOGI(TAG,"Destructor BMP180 called.\n"); 
    }

    /**
     * @brief Function to get the measured pressure.
     * 
     * @return float pressure value (Hpa).
     * 
     * @details User function to get the True pressure measured.
     */
    float HandleBMP180::GetPressure()
    {
        BMP180_GetTrueTemperature(BMP180_GetRawTemperature()); //update values
        return (((float)BMP180_GetTruePressure(BMP180_GetRawPressure())) / 10);
    }

    /**
     * @brief Function to get the relative altitude.
     * 
     * @return float altitude value (Meter).
     * 
     * @details User function to easily get the relative altitude based on the measured pressure and the pressure at sea level.
     */
    float HandleBMP180::GetAltitude()
    {
        float pressure = GetPressure();
        float altitude = 44330 * (1 - pow((pressure / 1013.25), (1.0 / 5.255)));
        return altitude;
    }

    /**
     * @brief Function to get the Temperature.
     * 
     * @return float Temperature in (celcius).
     * 
     * @details User function to get the true temperature. 
     */
    float HandleBMP180::GetTemperature()
    {

        return (((float)BMP180_GetTrueTemperature(BMP180_GetRawTemperature())) / 10);
    }

    /**
     * @brief Function to set the calibration data.
     * 
     * @details Private function to get the device specific calibration data. This data will later be used in calculations. 
     */
    void HandleBMP180::BMP180_SetCalibrationData()
    {
        AC1 = BMP180_Read_16Bit(0xAA);
        AC2 = BMP180_Read_16Bit(0xAC);
        AC3 = BMP180_Read_16Bit(0xAE);
        AC4 = BMP180_Read_16Bit(0xB0);
        AC5 = BMP180_Read_16Bit(0xB2);
        AC6 = BMP180_Read_16Bit(0xB4);
        B1  = BMP180_Read_16Bit(0xB6);
        B2  = BMP180_Read_16Bit(0xB8);
        MB  = BMP180_Read_16Bit(0xBA);
        MC  = BMP180_Read_16Bit(0xBC);
        MD  = BMP180_Read_16Bit(0xBE);

        ESP_LOGD(TAG,"Calibration Data: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",AC1,AC2,AC3,AC4,AC5,AC6,B1,B2,MB,MC,MD);
    }

    /**
     * @brief Function to get the Raw temperature data from the BMP180.
     * 
     * @return uint16_t The returned two bytes.
     * 
     * @details Function to get the Raw adc temperature measurments from register 0xF6.
     */
    uint16_t HandleBMP180::BMP180_GetRawTemperature()
    {
        BMP180_Write_Byte(0xF4, 0x2E);
        ets_delay_us(4500);
        return BMP180_Read_16Bit(0xF6);
    }

    /**
     * @brief Function to get the true temperature from the raw temperature.
     * 
     * @param _RawTemperature The Raw adc temperature value from register 0xF6.
     * @return long the True temperature value in 0.1 degrees celcius.
     * 
     * @details Private function to get the true temperature value from the Raw temperature. 
     */
    long HandleBMP180::BMP180_GetTrueTemperature(const uint16_t _RawTemperature)
    {
        long RawTemperature = (long)_RawTemperature;
        long X1 = (RawTemperature - AC6) * AC5 / pow(2, 15);
        long X2 = MC * pow(2, 11) / (X1 + MD);
        B5 = X1 + X2;
        return ((B5 + 8) / pow(2, 4));
    }

    /**
     * @brief Function to get the raw pressure from the BMP180.
     * 
     * @return uint16_t The Raw adc pressure value.
     * 
     * @details Private function to get the Raw pressure value from the BMP180. 
     */
    uint16_t HandleBMP180::BMP180_GetRawPressure()
    {
        BMP180_Write_Byte(0xF4, 0x34);
        ets_delay_us(4500);
        return BMP180_Read_16Bit(0xF6);
    }

    /**
     * @brief Function to go from raw pressure to true pressure.
     * 
     * @param _RawPressure The Raw Pressure from register 0xF6 of the BMP180
     * @return long The Pressure value in pa
     * 
     * @details Function to calculate the raw pressure to true pressure. Returns the pressure value in pa. 
     */
    long HandleBMP180::BMP180_GetTruePressure(const uint16_t _RawPressure)
    {
        long RawPressure = (long)_RawPressure;
        long pressure;

        long B6 = B5 - 4000;
        long X1 = (B2 * (B6 * B6 / pow(2, 12))) / pow(2, 11);
        long X2 = AC2 * B6 / pow(2, 11);
        long X3 = X1 + X2;
        long B3 = (((long)AC1 * 4 + X3) + 2) / 4;
        X1 = AC3 * B6 / pow(2, 13);
        X2 = (B1 * (B6 * B6 / pow(2, 12))) / pow(2, 16);
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
        X1 = (X1 * 3038) / pow(2, 16);
        X2 = (-7357 * pressure) / pow(2, 16);
        return (pressure + (X1 + X2 + 3791) / pow(2, 4));
    }

    /**
     * @brief Function to write a byte to the BMP180.
     * 
     * @param WriteAdress The adress where the data will be written to.
     * @param WriteData The data that will be written to the BMP180.
     * 
     * @details Function to write a byte of data to the BMP180 using I2c. 
     */
    esp_err_t HandleBMP180::BMP180_Write_Byte(uint8_t WriteAdress, uint8_t WriteData)
    {
        esp_err_t Error = ESP_OK;
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        Error |= i2c_master_start(link_cmd);
        Error |= i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
        Error |= i2c_master_write(link_cmd, &WriteAdress, sizeof(WriteAdress), true);

        Error |= i2c_master_write(link_cmd, &WriteData, sizeof(WriteData), true);
        Error |= i2c_master_stop(link_cmd);
        Error |= i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        return Error;
    }

    /**
     * @brief Function to read two bytes from the BMP180.
     * 
     * @param DataAdress The adress where the reading will start.
     * @return uint16_t The data that has been read from the BMP180.
     * 
     * @details Function to read 16 bits from the BMP180 using I2C. 
     */
    uint16_t HandleBMP180::BMP180_Read_16Bit( uint8_t DataAdress)
    {
        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
        i2c_master_write(link_cmd, &DataAdress, sizeof(DataAdress), true);
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