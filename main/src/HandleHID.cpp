/**
 * @file HandleHID.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "HandleHID.h"


extern "C" {

    HandleHID::HandleHID(const gpio_num_t Output)
        : _OutputPin(Output, GPIO_MODE_INPUT, GPIO_FLOATING)
    {
        ESP_LOGI(TAG,"Handle Class for the HID has been created\n");     
    }

    int HandleHID::GetState(void)
    {
        return _OutputPin.PIN_GetLevel(); 
    }

}