/**
 * @file HandleJOYstick.h
 * @author Vincent de Man
 * @brief Header file for HandleJOYstick class (.h)
 * @version 0.1
 * @date 2021-05-18
 * @details Header file for HandleJOYstick class (.h)
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

#define ZeroVRX 1.25
#define ZeroVRY 1.18
#define VR_Hysteresisch 0.7
#define VR_MaxVoltage 2.60
#define VR_Range 50


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
    void PrintValues();
    JOY_Data_t GetConverted();
    float GetRawVRX();
    float GetRawVRY();
    int getSW();
    private:

    HandleADC _VRX;
    HandleADC _VRY;
    HandlePIN _SW;

    constexpr static const char* TAG = "JOY";
};

}

#endif