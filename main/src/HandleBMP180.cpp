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
#include <bitset>
#include <iostream>

extern "C"{
HandleBMP180::HandleBMP180(){

}

uint8_t HandleBMP180::test(){
   

    //uint8_t adress = 0xF6;
    return BMP180_Read_16Bit(0xF6);

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

    std::cout<<"Calibration Data: "<<AC1 << ','<<AC2 << ','<<AC3 << ','<<AC4 << ','<<AC5 << ','<<AC6 << ','<<B1 << ','<<B2 << ','<<MB << ','<<MC << ','<<MD <<std::endl;
    
    
    

}

uint16_t HandleBMP180::BMP180_Read_16Bit(uint8_t DataAdress){


    i2c_port_t I2C_Portt = I2C_NUM_1;
    i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
    i2c_master_start(link_cmd);
    i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Write, true);
    i2c_master_write(link_cmd, &DataAdress, sizeof(DataAdress) / sizeof(uint8_t), true);
    i2c_master_stop(link_cmd);
    i2c_master_cmd_begin(I2C_Portt, link_cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(link_cmd);

    uint8_t most_significant_bit;
    uint8_t least_significant_bit;
    uint16_t Result;
    link_cmd = i2c_cmd_link_create();
    i2c_master_start(link_cmd);
    i2c_master_write_byte(link_cmd, BMP180_I2C_ADRESS_Read, true);
    i2c_master_read_byte(link_cmd,&most_significant_bit,I2C_MASTER_ACK);
    i2c_master_read_byte(link_cmd,&least_significant_bit,I2C_MASTER_LAST_NACK);
    i2c_master_stop(link_cmd);
    i2c_master_cmd_begin(I2C_Portt, link_cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(link_cmd);

   
    Result = ((uint16_t)most_significant_bit << 8) | least_significant_bit;

    return Result;
}

}