/**
 * @file HandleGPIO.h
 * @author Vincent de Man
 * @brief Header file for GPIO handler (.h)
 * @version 1.1
 * @date 2021-03-24
 * @details Header file for gpio handler class. Include functions SetHigh SetLow SetGPIO InitializeGPIO
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

    void SetHigh(gpio_num_t);
    void SetLow(gpio_num_t);
    void SetGPIO(gpio_num_t, int);
    void InitializeGPIO(gpio_num_t);
  };
}

#endif