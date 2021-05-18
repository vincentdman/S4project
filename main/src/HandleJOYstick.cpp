/**
 * @file HandleJOYstick.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HandleJOYstick.h"
extern "C"{
HandleJOYstick::HandleJOYstick(const gpio_num_t VRX, const gpio_num_t VRY, const gpio_num_t SW)
    : _VRX(VRX), _VRY(VRY), _SW(SW,GPIO_MODE_INPUT)
    {   
      if(ESP_OK != _SW.PIN_Initialize())
      {
          ESP_LOGE(TAG,"PIN Initialization error");
      }
    }

void HandleJOYstick::test()
{
  ESP_LOGI(TAG,"VRX = %.2f",_VRX.GetVoltage());
  ESP_LOGI(TAG,"VRY = %.2f",_VRY.GetVoltage());
  ESP_LOGI(TAG,"SW = %d\n",_SW.PIN_GetLevel());
}


}

