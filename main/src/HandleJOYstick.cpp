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
      ESP_LOGI(TAG,"For better working of the HandleJoy stick class try using youre own zeroing values!");
      if(ESP_OK != _SW.PIN_Initialize())
      {
          ESP_LOGE(TAG,"PIN Initialization error");
      }
    }

void HandleJOYstick::PrintValues()
{
  ESP_LOGI(TAG,"VRX = %.2f",_VRX.GetVoltage());
  ESP_LOGI(TAG,"VRY = %.2f",_VRY.GetVoltage());
  ESP_LOGI(TAG,"SW = %d\n",_SW.PIN_GetLevel());
}
    float HandleJOYstick::GetRawVRX()
    {
      return _VRX.GetVoltage();
    }
    
    float HandleJOYstick::GetRawVRY()
    {
      return _VRY.GetVoltage();
    }
    
    int HandleJOYstick::getSW()
    {
      return _SW.PIN_GetLevel(); 
    }

    JOY_Data_t HandleJOYstick::GetConverted()
    {
      JOY_Data_t JOYD;

      float VRY = _VRY.GetVoltage();
      float VRX = _VRX.GetVoltage();
      JOYD.SW = !_SW.PIN_GetLevel(); 
      
      if(VRX >= (ZeroVRX))
      {
       VRX = (VRX - ZeroVRX) * (VR_Range)/(VR_MaxVoltage-ZeroVRX);
      }
      else
      {
       VRX = (VRX) * (VR_Range)/(ZeroVRX)-VR_Range;
      }

      if(VRY >= (ZeroVRY))
      {
       VRY = (VRY - ZeroVRY) * (VR_Range)/(VR_MaxVoltage-ZeroVRY);
      }
      else
      {
       VRY = (VRY) * (VR_Range)/(ZeroVRY)-VR_Range;
      }
      
      if((VRX < VR_Hysteresisch)&&(VRX > -VR_Hysteresisch))
      {
        VRX = 0; 
      }

      if((VRY < VR_Hysteresisch)&&(VRY > -VR_Hysteresisch))
      {
        VRY = 0; 
      }
      JOYD.VRX = VRX;
      JOYD.VRY = VRY;


      return JOYD;
    }
    
}

