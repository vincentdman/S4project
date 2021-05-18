/**
 * @file HandleJOYstick.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleJOYstick_h
#define HandleJOYstick_h

#include "HandleADC.h"
#include "HandlePIN.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

extern "C"{
class HandleJOYstick
{
    public:
    HandleJOYstick(const gpio_num_t VRX, const gpio_num_t VRY, const gpio_num_t SW);

    private:
    HandleADC _VRX;
    HandleADC _VRY;
    HandlePIN _SW;

    constexpr static const char* TAG = "I2C";
};
}

#endif