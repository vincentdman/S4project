/**
 * @file RGB_Control.cpp
 * @author Vincent de Man
 * @brief RGB led control class (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @class RGB_Control class to create a rgb led object
 * @details Implementation of the handle rgb class. It uses the inherited handle gpio and pwm gpio functions. 
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
     * 
     * @details Default constructor for a rgb led. It takes in the three pins connected to the led and initializes them with pull-down
     * resistor active and gpio mode output. 
     */
    RGB_Control::RGB_Control(gpio_num_t _Red, gpio_num_t _Green, gpio_num_t _Blue)
        : Red(_Red), Green(_Green), Blue(_Blue)
    {
        InitializeGPIO(_Red);
        InitializeGPIO(_Green);
        InitializeGPIO(_Blue);
    }

    /**
     * @brief Setblue function to make the rgb led shine blue
     * 
     * @details Set the rgb led to display only the colour blue. (red off, green of, blue on)
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
     * @details Set the rgb led to display the colour green. (red off, blue off, green on)
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
     * @details Set the rgb led to display the colour red. (red on, blue off, green off)
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
     * @details Set the rgb led to display the colour purple. (red on, green off, blue on)
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
     * @details Set the rgb led to display the colour white. (green on, red on, blue on)
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
     * @details Set the rgb led to display the colour yellow. (red on, green on, blue off)
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
     * @details Set the rgb led to display the colour cyan. (red off, green on, blue on)
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
     * 
     * @details Function to set the rgb value of the red. The inputs are SetR SetG & SetB
     * with these inputs the rgb value can be controlled. the input reaches from 0-100 with 100 100% duty cycle and 0 0% duty cycle. 
     * This will be done by changing the duty cycle of the channels connected to the led. 
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
     * 
     * @details Function to only set the brightness of the red led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetR (set red). 
     * the function makes use of the SetDuty function.
     */
    void RGB_Control::SetRGB_Red(int SetR)
    {
        SetDuty(SetR, Red, RedChannel);
    }

    /**
     * @brief SetRGB_Green to change the intensity of the green led
     * 
     * @param SetG integer value 0-100 to set intensity of the green led
     * 
     * @details Function to only set the brightness of the green led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetG (set green). 
     * the function makes use of the SetDuty function.
     */
    void RGB_Control::SetRGB_Green(int SetG)
    {
        SetDuty(SetG, Green, GreenChannel);
    }

    /**
     * @brief SetRGB_Blue to change the intensity of the blue led
     * 
     * @param SetB integer value 0-100 to set intensity of the blue led
     * 
     * @details Function to only set the brightness of the blue led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetB (set blue). 
     * the function makes use of the SetDuty function
     */
    void RGB_Control::SetRGB_Blue(int SetB)
    {
        SetDuty(SetB, Blue, BlueChannel);
    }

    /**
     * @brief Function to change the pwm channel for the red led
     * 
     * @param Channel The new pwm channel for the red led from type ledc_channel_t
     * 
     * @details Function to change the pwm channel of the red led. the input type is ledc_channel_t.
     * There are 7 available channels to choose from. Default value channel 0
     */
    void RGB_Control::ChangeChannelRed(ledc_channel_t Channel)
    {
        RedChannel = Channel;
    }

    /**
     * @brief Function to change the pwm channel for the blue led
     * 
     * @param Channel The new pwm channel for the blue led from type ledc_channel_t
     * 
     * @details Function to change the pwm channel of the blue led. the input type is ledc_channel_t.
     * There are 7 available channels to choose from. Default value channel 1
     */
    void RGB_Control::ChangeChannelBlue(ledc_channel_t Channel)
    {
        BlueChannel = Channel;
    }

    /**
     * @brief Function to change the pwm channel for the green led
     * 
     * @param Channel The new pwm channel for the green led from type ledc_channel_t
     * 
     * @details Function to change the pwm channel of the green led. the input type is ledc_channel_t.
     * There are 7 available channels to choose from. Default value channel 2
     */
    void RGB_Control::ChangeChannelGreen(ledc_channel_t Channel)
    {
        GreenChannel = Channel;
    }
}