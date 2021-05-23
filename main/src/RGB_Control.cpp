/**
 * @file RGB_Control.cpp
 * @author Vincent de Man
 * @brief RGB led control class (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @class RGB_Control class to create a rgb led object.
 * @details Implementation of the handle rgb class. It uses the inherited handle gpio and pwm gpio functions. 
 */
#include "RGB_Control.h"

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
    RGB_Control::RGB_Control(const gpio_num_t _Red, const gpio_num_t _Green, const gpio_num_t _Blue)
        : Red(_Red), Green(_Green), Blue(_Blue)
    {
        InitializeGPIO_Output(_Red);
        InitializeGPIO_Output(_Green);
        InitializeGPIO_Output(_Blue);
    }

    /**
     * @brief Setblue function to make the rgb led shine blue
     * 
     * @details Set the rgb led to display only the colour blue. (red off, green of, blue on)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetBlue()
    {
        esp_err_t Error = ESP_OK; 
        Error |= SetHigh(Blue);
        Error |= SetLow(Red);
        Error |= SetLow(Green);
        return Error; 
    }

    /**
     * @brief SetGreen function to make the rgb led shine green
     * 
     * @details Set the rgb led to display the colour green. (red off, blue off, green on)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetGreen()
    {
        esp_err_t Error = ESP_OK;
        Error |= SetHigh(Green);
        Error |= SetLow(Red);
        Error |= SetLow(Blue);
        return Error; 
    }

    /**
     * @brief SetRed function to make the rgb led shine red
     * 
     * @details Set the rgb led to display the colour red. (red on, blue off, green off)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetRed()
    {
        esp_err_t Error = ESP_OK; 
        Error |= SetHigh(Red);
        Error |= SetLow(Green);
        Error |= SetLow(Blue);
        return Error;
    }

    /**
     * @brief Function to turn the led off.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to turn the led comletely off. 
     */
    esp_err_t RGB_Control::SetOff()
    {
        esp_err_t Error = ESP_OK; 
        Error |= SetLow(Red);
        Error |= SetLow(Green);
        Error |= SetLow(Blue);
        return Error;        
    }
    /**
     * @brief SetPurple function to make the rgb led shine purple   
     * 
     * @details Set the rgb led to display the colour purple. (red on, green off, blue on)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetPurple()
    {
        esp_err_t Error = ESP_OK;
        Error |= SetHigh(Red);
        Error |= SetLow(Green);
        Error |= SetHigh(Blue);
        return Error; 
    }

    /**
     * @brief SetWhite function to make the rgb led shine white
     * 
     * @details Set the rgb led to display the colour white. (green on, red on, blue on)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetWhite()
    {
        esp_err_t Error = ESP_OK;
        Error |= SetHigh(Red);
        Error |= SetHigh(Green);
        Error |= SetHigh(Blue);
        return Error;
    }

    /**
     * @brief SetYellow function to make the rgb led shine yellow
     * 
     * @details Set the rgb led to display the colour yellow. (red on, green on, blue off)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetYellow()
    {
        esp_err_t Error = ESP_OK;
        Error |= SetHigh(Red);
        Error |= SetHigh(Green);
        Error |= SetLow(Blue);
        return Error;
    }

    /**
     * @brief SetCyan function to make the rgb led shine cyan
     * 
     * @details Set the rgb led to display the colour cyan. (red off, green on, blue on)
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetCyan()
    {
        esp_err_t Error = ESP_OK;
        Error |= SetLow(Red);
        Error |= SetHigh(Green);
        Error |= SetHigh(Blue);
        return Error;
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
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetRGB(int SetR, int SetG, int SetB)
    {
        esp_err_t Error = ESP_OK;
        Error |= SetDuty(SetR, Red, RedChannel);
        Error |= SetDuty(SetG, Green, GreenChannel);
        Error |= SetDuty(SetB, Blue, BlueChannel);
        ESP_LOGD(TAG,"RGB values: red: %d green: %d blue: %d.\n",SetR,SetG,SetB);   
        return Error;
    }

    /**
     * @brief SetRGB_Red to change the intensity of the red led
     * 
     * @param SetR integer value 0-100 to set intensity of the red led
     * 
     * @details Function to only set the brightness of the red led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetR (set red). 
     * the function makes use of the SetDuty function.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetRGB_Red(int SetR)
    {
       return SetDuty(SetR, Red, RedChannel);
    }

    /**
     * @brief SetRGB_Green to change the intensity of the green led
     * 
     * @param SetG integer value 0-100 to set intensity of the green led
     * 
     * @details Function to only set the brightness of the green led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetG (set green). 
     * the function makes use of the SetDuty function.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetRGB_Green(int SetG)
    {
       return SetDuty(SetG, Green, GreenChannel);
    }

    /**
     * @brief SetRGB_Blue to change the intensity of the blue led
     * 
     * @param SetB integer value 0-100 to set intensity of the blue led
     * 
     * @details Function to only set the brightness of the blue led in the rgb led. 
     * input is a integer ranging from 0-100 with the name SetB (set blue). 
     * the function makes use of the SetDuty function
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t RGB_Control::SetRGB_Blue(int SetB)
    {
       return SetDuty(SetB, Blue, BlueChannel);
    }

    /**
     * @brief Function to change the pwm channel for the red led
     * 
     * @param Channel The new pwm channel for the red led from type ledc_channel_t
     * 
     * @details Function to change the pwm channel of the red led. the input type is ledc_channel_t.
     * There are 7 available channels to choose from. Default value channel 0
     * 
     */
    void RGB_Control::ChangeChannelRed(const ledc_channel_t Channel)
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
     * 
     */
    void RGB_Control::ChangeChannelBlue(const ledc_channel_t Channel)
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
    void RGB_Control::ChangeChannelGreen(const ledc_channel_t Channel)
    {
        GreenChannel = Channel;
    }
}