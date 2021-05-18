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
    typedef struct{
        float VRX;
        float VRY;
        int SW;
    }JOY_Data_t;
class HandleJOYstick
{
    public:
    HandleJOYstick(const gpio_num_t VRX, const gpio_num_t VRY, const gpio_num_t SW);
    void test();
    private:

    HandleADC _VRX;
    HandleADC _VRY;
    HandlePIN _SW;

    constexpr static const int ZeroVRX = 1.25; 
    constexpr static const int ZeroVRY = 1.18;
    constexpr static const int VR_Hysteresisch = 0.05;

    constexpr static const char* TAG = "JOY";
};
}

#endif