/**
 * @file HandleGPIO.h
 * @author Vincent de Man
 * @brief Header file for GPIO handler (.h)
 * @version 1.2
 * @date 2021-03-24
 * @details Header file for gpio handler class. Includes functions SetHigh SetLow SetGPIO InitializeGPIO.
 * @copyright Copyright (cpp) 2021
 * 
 */

#ifndef HandleGPIO_h
#define HandleGPIO_h

#include "esp_err.h"
#include "esp_system.h"
#include <driver/gpio.h>

extern "C"
{
  class HandleGPIO
  {
  public:
    HandleGPIO();

    esp_err_t SetHigh(gpio_num_t);
    esp_err_t SetLow(gpio_num_t);
    esp_err_t SetGPIO(gpio_num_t, int);
    esp_err_t InitializeGPIO(gpio_num_t);

  private:
    constexpr static const char* TAG = "GPIO";
  };
}

#endif