/**
 * @file RGB_Control.cpp
 * @author Vincent de Man
 * @brief RGB led control class (.cpp)
 * @version 0.1
 * @date 2021-03-24
 * @copyright Copyright (c) 2021
 * @class RGB_Control class to create a rgb led object
 */
#include <iostream>
#include "RGB_Control.h"
#include "HandleGPIO.h"

extern "C"
{
    /**
     * @brief Construct a new rgb control::rgb control object by taking the rgb pins and initializing them
     * 
     * @param _Red Pin connected to the red anode of the led
     * @param _Green Pin connected to the green anode of the led
     * @param _Blue Pin connected to the blue anode of the led
     */
    RGB_Control::RGB_Control(gpio_num_t _Red, gpio_num_t _Green, gpio_num_t _Blue)
    {
        InitializeGPIO(_Red);
        InitializeGPIO(_Green);
        InitializeGPIO(_Blue);
        Red = _Red;
        Green = _Green;
        Blue = _Blue;
    }
    /**
     * @brief Setblue function to make the rgb led shine blue
     * 
     */
    void RGB_Control::SetBlue()
    {
        SetHigh(Blue);
        SetLow(Red);
        SetLow(Green);
    }
    /**
     * @brief SetGreen function to make the rgb led shine green
     * 
     */
    void RGB_Control::SetGreen()
    {
        SetHigh(Green);
        SetLow(Red);
        SetLow(Blue);
    }
    /**
     * @brief SetRed function to make the rgb led shine red
     * 
     */
    void RGB_Control::SetRed()
    {
        SetHigh(Red);
        SetLow(Green);
        SetLow(Blue);
    }
    /**
     * @brief SetPurple function to make the rgb led shine purple   
     * 
     */
    void RGB_Control::SetPurple()
    {
        SetHigh(Red);
        SetLow(Green);
        SetHigh(Blue);
    }
    /**
     * @brief SetWhite function to make the rgb led shine white
     * 
     */
    void RGB_Control::SetWhite()
    {
        SetHigh(Red);
        SetHigh(Green);
        SetHigh(Blue);
    }
    /**
     * @brief SetYellow function to make the rgb led shine yellow
     * 
     */
    void RGB_Control::SetYellow()
    {
        SetHigh(Red);
        SetHigh(Green);
        SetLow(Blue);
    }
    /**
     * @brief SetCyan function to make the rgb led shine cyan
     * 
     */
    void RGB_Control::SetCyan()
    {
        SetLow(Red);
        SetHigh(Green);
        SetHigh(Blue);
    }
    /**
     * @brief SetRGB function to set the rgb values for the led
     * 
     * @param SetR integer value 0-100 to set intensity of the red led
     * @param SetG integer value 0-100 to set intensity of the green led
     * @param SetB integer value 0-100 to set intensity of the blue led
     */
    void RGB_Control::SetRGB(int SetR, int SetG, int SetB)
    {
        SetDuty(SetR, Red, RedChannel);
        SetDuty(SetG, Green, GreenChannel);
        SetDuty(SetB, Blue, BlueChannel);
    }
    /**
     * @brief SetRGB_Red to change the intensity of the red led
     * 
     * @param SetR integer value 0-100 to set intensity of the red led
     */
    void RGB_Control::SetRGB_Red(int SetR)
    {
        SetDuty(SetR, Red, RedChannel);
    }
    /**
     * @brief SetRGB_Green to change the intensity of the green led
     * 
     * @param SetG integer value 0-100 to set intensity of the green led
     */
    void RGB_Control::SetRGB_Green(int SetG)
    {
        SetDuty(SetG, Green, GreenChannel);
    }
    /**
     * @brief SetRGB_Blue to change the intensity of the blue led
     * 
     * @param SetB integer value 0-100 to set intensity of the blue led
     */
    void RGB_Control::SetRGB_Blue(int SetB)
    {
        SetDuty(SetB, Blue, BlueChannel);
    }
    /**
     * @brief Function to change the pwm channel for the red led
     * 
     * @param Channel The new pwm channel for the red led
     */
    void RGB_Control::ChangeChannelRed(ledc_channel_t Channel)
    {
        RedChannel = Channel;
    }
    /**
     * @brief Function to change the pwm channel for the blue led
     * 
     * @param Channel The new pwm channel for the blue led
     */
    void RGB_Control::ChangeChannelBlue(ledc_channel_t Channel)
    {
        BlueChannel = Channel;
    }
    /**
     * @brief Function to change the pwm channel for the green led
     * 
     * @param Channel The new pwm channel for the green led
     */
    void RGB_Control::ChangeChannelGreen(ledc_channel_t Channel)
    {
        GreenChannel = Channel;
    }
}