/**
 * @file HandleGPIO.h
 * @author Vincent de Man
 * @brief Header file for GPIO handler (.h)
 * @version 1.2
 * @date 2021-03-24
 * @details Header file for gpio handler class. Includes functions SetHigh SetLow SetGPIO InitializeGPIO_Output.
 * @copyright Copyright (cpp) 2021
 * 
 */

#ifndef HandleGPIO_h
#define HandleGPIO_h

#include <driver/gpio.h>
#include <iostream>

#include "esp_err.h"
#include "esp_system.h"
#include "assert.h"
#include "esp_log.h"

extern "C"
{
  class HandleGPIO
  {
  public:
    HandleGPIO();

    esp_err_t SetHigh(const gpio_num_t PIN);
    esp_err_t SetLow(const gpio_num_t PIN);
    esp_err_t SetGPIO(const gpio_num_t PIN, const int);
    esp_err_t InitializeGPIO_Output(const gpio_num_t PIN);
    esp_err_t InitializeGPIO_Input(const gpio_num_t PIN); 
    int GetLevel(const gpio_num_t PIN);

  private:
    constexpr static const char* TAG = "GPIO";
  };
}

#endif