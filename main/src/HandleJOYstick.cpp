/**
 * @file HandleJOYstick.cpp
 * @author Vincent de Man
 * @brief Source file for HandleJOYstick (.cpp)
 * @version 0.1
 * @date 2021-05-18
 * @class HandleJOYstick class to control the joystick.
 * @copyright Copyright (c) 2021
 * @details Source file with the implementation of the HandleJOYstick class. 
 */
#include "HandleJOYstick.h"

extern "C"
{
  /**
   * @brief Construct a new HandleJOYstick::HandleJOYstick object
   * 
   * @param VRX The Pin connected to the X-axis.
   * @param VRY The Pin connected to the Y-axis.
   * @param SW The Pin connected to the switch.
   * 
   * @details Default constructor to initialize a new HandleJOYstick object. 
   */
  HandleJOYstick::HandleJOYstick(const gpio_num_t VRX, const gpio_num_t VRY, const gpio_num_t SW)
      : _VRX(VRX), _VRY(VRY), _SW(SW, GPIO_MODE_INPUT)
  {
    ESP_LOGI(TAG, "For better working of the HandleJoy stick class try using youre own zeroing values!");
    if (ESP_OK != _SW.PIN_Initialize())
    {
      ESP_LOGE(TAG, "PIN Initialization error");
    }
  }

  /**
 * @brief Function to print the measured values.
 * @details Debug function to print the measured values. Might be useful to debug or to get the zero values.
 */
  void HandleJOYstick::PrintValues()
  {
    ESP_LOGI(TAG, "VRX = %.2f", _VRX.GetVoltage());
    ESP_LOGI(TAG, "VRY = %.2f", _VRY.GetVoltage());
    ESP_LOGI(TAG, "SW = %d\n", _SW.PIN_GetLevel());
  }

  /**
   * @brief Function to get the Raw voltage on the X-axis.
   * 
   * @return float The voltage on the X-axis.
   * 
   * @details Function to get the Raw voltage on the X-axis of the joystick.
   */
  float HandleJOYstick::GetRawVRX()
  {
    return _VRX.GetVoltage();
  }

  /**
   * @brief Function to get the Raw voltage on the Y-axis.
   * 
   * @return float The voltage on the Y-axis.
   * 
   * @details Function to get the raw voltage on the Y-axis.
   */
  float HandleJOYstick::GetRawVRY()
  {
    return _VRY.GetVoltage();
  }

  /**
   * @brief Function to get the state of the switch.
   * 
   * @return int the state of the switch !note that one is not pressed and zero is pressed.
   * 
   * @details Function to get the state of the switch. 
   */
  int HandleJOYstick::getSW()
  {
    return _SW.PIN_GetLevel();
  }

  /**
   * @brief Function to get the converted values of the joystick connections.
   * 
   * @return JOY_Data_t The struct containg the data.
   * 
   * @details Function that takes in the raw voltage of the joystick pins and convert it to -VR_Range to VR_Range. 
   * It returns the struct JOY_Data_t that contains the values. 
   */
  JOY_Data_t HandleJOYstick::GetConverted()
  {
    JOY_Data_t JOYD;

    float VRY = _VRY.GetVoltage();
    float VRX = _VRX.GetVoltage();
    JOYD.SW = !_SW.PIN_GetLevel();

    if (VRX >= (ZeroVRX))
    {
      VRX = (VRX - ZeroVRX) * (VR_Range) / (VR_MaxVoltage - ZeroVRX);
    }
    else
    {
      VRX = (VRX) * (VR_Range) / (ZeroVRX)-VR_Range;
    }

    if (VRY >= (ZeroVRY))
    {
      VRY = (VRY - ZeroVRY) * (VR_Range) / (VR_MaxVoltage - ZeroVRY);
    }
    else
    {
      VRY = (VRY) * (VR_Range) / (ZeroVRY)-VR_Range;
    }

    if ((VRX < VR_Hysteresisch) && (VRX > -VR_Hysteresisch))
    {
      VRX = 0;
    }

    if ((VRY < VR_Hysteresisch) && (VRY > -VR_Hysteresisch))
    {
      VRY = 0;
    }
    JOYD.VRX = VRX;
    JOYD.VRY = VRY;

    return JOYD;
  }
}
