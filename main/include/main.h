/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef main_h
#define main_h

#include <stdio.h>
#include <iostream>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <esp_wifi.h>
#include <bitset>
#include <sstream>
#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "HandleGPIO.h"
#include "RGB_Control.h"
#include "PWM_GPIO.h"
#include "LCD_Commands.h"
#include "LCD_Control.h"
#include "driver/i2c.h"
#include "HandleI2C.h"
#include "HandleBMP180.h"
#include "esp_log.h"
#include "HandleADC.h"
#include "driver/adc.h"
#include "HandlePIN.h"
#include "cstdlib"
#include "HandleJOYstick.h"

#define Build_Version 3.0

__attribute((__unused__)) static const char *TAG = "main";




#endif

//extern "C" void app_main(void)
// {
//   ESP_LOGI(TAG, "\n\nBuild version: %.2f\n", Build_Version);
//   ESP_LOGI(TAG, "Created by Vincent de Man\n");

//   LCD_Pinout_t Configs;
//   Configs._BitMode = I2CMode;
//   Configs._SDA = GPIO_NUM_21;
//   Configs._SCL = GPIO_NUM_22;
  

//   HandleI2C I2c(true);
//   LCD_Control LCD(Configs);
//   RGB_Control LED(GPIO_NUM_23,GPIO_NUM_19,GPIO_NUM_4);
//   HandleBMP180 BMP;

//   LCD.LCD_Write_Command(LCD_DISPLAY_ON_CURSOR_OFF);
//   LCD.LCD_Write_Command(LCD_CLEAR);


//   while (1)
//   {
//     LCD.LCD_Write_Command(LCD_HOME);
//     LCD.LCD_Write_String("Temperature:");
//     LCD.LCD_Write_Float(BMP.GetTemperature());
//     LCD.LCD_Write_Command(LCD_NEXT_LINE);
    
//     LCD.LCD_Write_String("Pressure: ");
//     LCD.LCD_Write_Float(BMP.GetPressure());
    
//     LED.SetRGB(rand()%100,rand()%100,rand()%100);
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//   }
// }