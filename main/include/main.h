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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <driver/gpio.h>
#include <driver/adc.h>
#include <esp_wifi.h>
#include "HandleGPIO.h"
#include "RGB_Control.h"
#include "PWM_GPIO.h"
#include "LCD_Commands.h"
#include "LCD_Control.h"
#include "driver/i2c.h"
#include "HandleI2C.h"
#include <string>
#include "HandleBMP180.h"
#include <bitset>
#include <sstream>
#include "esp_log.h"
#include "HandleADC.h"
#include "driver/adc.h"
#include "HandlePIN.h"
#include "cstdlib"
#include "HandleJOYstick.h"

#define Build_Version 3.0

static const char *TAG = "main";




#endif