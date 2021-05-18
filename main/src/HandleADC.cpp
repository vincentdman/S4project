/**
 * @file HandleADC.cpp
 * @author Vincent de Man
 * @brief Handle adc source file (.cpp)
 * @version 0.1
 * @date 2021-05-15
 * @class HandleADC class to make use of the adc much more easier. 
 * @copyright Copyright (c) 2021
 * @details Handle adc class to utalize the adc of the esp32 easy
 */

#include <driver/adc.h>
#include "HandleADC.h"
#include "esp_err.h"

extern "C"
{   

    /**
     * @brief Construct a new HandleADC::HandleADC object.
     * 
     * @param PIN The pin number for adc.
     * @param Resolution The sampling resolution.
     * @param attentuation The attentuation of the adc.
     * 
     * @details Function that converts the given adc pin to the correct adc channel so it is easier to use for the user. 
     */
    HandleADC::HandleADC(gpio_num_t PIN, adc_bits_width_t Resolution, adc_atten_t attentuation)
        : _resolution(Resolution), _attentuation(attentuation)
    {
        switch (PIN)
        {
        case GPIO_NUM_0:
            _channel2 = ADC2_CHANNEL_1;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
         case GPIO_NUM_2:
            _channel2 = ADC2_CHANNEL_2;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
         case GPIO_NUM_4:
            _channel2 = ADC2_CHANNEL_0;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
        case GPIO_NUM_12:
            _channel2 = ADC2_CHANNEL_5;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break;  
        case GPIO_NUM_13:
            _channel2 = ADC2_CHANNEL_4;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
        case GPIO_NUM_14:
            _channel2 = ADC2_CHANNEL_6;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break;             
        case GPIO_NUM_15:
            _channel2 = ADC2_CHANNEL_3;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break;  
        case GPIO_NUM_25:
            _channel2 = ADC2_CHANNEL_8;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break;
        case GPIO_NUM_26:
            _channel2 = ADC2_CHANNEL_9;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
        case GPIO_NUM_27:
            _channel2 = ADC2_CHANNEL_7;
            SwapInitialize = &HandleADC::ADC_InitChannel2;
            SwapGetResolution = &HandleADC::ADC_GetConversion2;
            break; 
        case GPIO_NUM_32:
            _channel1 = ADC1_CHANNEL_4;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_33:
            _channel1 = ADC1_CHANNEL_5;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_34:
            _channel1 = ADC1_CHANNEL_6;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_35:
            _channel1 = ADC1_CHANNEL_7;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_36:
            _channel1 = ADC1_CHANNEL_0;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_37:
            _channel1 = ADC1_CHANNEL_1;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_38:
            _channel1 = ADC1_CHANNEL_2;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;
        case GPIO_NUM_39:
            _channel1 = ADC1_CHANNEL_3;
            SwapInitialize = &HandleADC::ADC_InitChannel1;
            SwapGetResolution = &HandleADC::ADC_GetConversion1;
            break;   
        
        default:
        ESP_LOGE(TAG,"BIG ERROR No valid ADC pin");
        vTaskDelay(10000/portTICK_PERIOD_MS);
        abort();
            break;
        }

        SetAttentuation();
        ADC_Initialize();
    }

    /**
     * @brief Construct a new HandleADC::HandleADC object
     * 
     * @param channel The desired ADC channel from adc1.
     * @param Resolution The desired sampling resolution.
     * @param attentuation The attentuation level. 
     * 
     * @details Constructor for ADC channel 1 to configure it for uses as adc. 
     */
    HandleADC::HandleADC(adc1_channel_t channel, adc_bits_width_t Resolution, adc_atten_t attentuation)
        : _channel1(channel), _resolution(Resolution), _attentuation(attentuation)
    {

        SwapInitialize = &HandleADC::ADC_InitChannel1;
        SwapGetResolution = &HandleADC::ADC_GetConversion1;
        SetAttentuation();
        ADC_Initialize();
    }

    /**
     * @brief Construct a new HandleADC::HandleADC object
     * 
     * @param channel The desired adc channel from adc2.
     * @param Resolution The desired sampling resolution.
     * @param attentuation The desired attentuation. 
     * 
     * @details Constructor for ADC channel 2 to configure it for uses as adc.
     */
    HandleADC::HandleADC(adc2_channel_t channel, adc_bits_width_t Resolution, adc_atten_t attentuation)
        : _channel2(channel), _resolution(Resolution), _attentuation(attentuation)
    {

        SwapInitialize = &HandleADC::ADC_InitChannel2;
        SwapGetResolution = &HandleADC::ADC_GetConversion2;
        SetAttentuation();
        ADC_Initialize();
    }

    /**
     * @brief Function to initialize the object for the correct attentuation. 
     * 
     * @details Function to initialize the object for the correct attentuation. 
     * It uses the std::function template to switch between functions.
     * This happens only once at creation of the object.  
     */
    void HandleADC::SetAttentuation()
    {

        if (_attentuation == ADC_ATTEN_DB_0)
        {
            SwapGetAttentuation = &HandleADC::ADC_GetVoltage0;
        }
        else if (_attentuation == ADC_ATTEN_DB_2_5)
        {
            SwapGetAttentuation = &HandleADC::ADC_GetVoltage2_5;
        }
        else if (_attentuation == ADC_ATTEN_DB_6)
        {
            SwapGetAttentuation = &HandleADC::ADC_GetVoltage6;
        }
        else if (_attentuation == ADC_ATTEN_DB_11)
        {
            SwapGetAttentuation = &HandleADC::ADC_GetVoltage11;
        }
        else
        {
            ESP_LOGE(TAG, "no valid attentuation! \n");
            abort();
        }
    }

    /**
     * @brief Function to initialize the adc for use. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to initialize the adc for use will be called by the constructor
     */
    esp_err_t HandleADC::ADC_Initialize()
    {
        return SwapInitialize(this);
    }

    /**
     * @brief Function to initialize the channel for ADC1.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to initialize the channel for adc1 will be switched between ADC_InitChannel2 when needed. 
     */
    esp_err_t HandleADC::ADC_InitChannel1()
    {
        esp_err_t Error = ESP_OK;
        Error |= adc1_config_width(_resolution);
        Error |= adc1_config_channel_atten(_channel1, _attentuation);
        return Error;
    }

    /**
     * @brief Function to initialize the channel for ADC2. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to initialize the channel for ADC2. 
     */
    esp_err_t HandleADC::ADC_InitChannel2()
    {
        esp_err_t Error = ESP_OK;
        Error |= adc2_config_channel_atten(_channel2, _attentuation);
        return Error;
    }

    /**
     * @brief Function to get raw conversion result. 
     * 
     * @return int Raw conversion result. 
     * 
     * @details Function to get the raw conversion result. 
     */
    int HandleADC::ADC_GetRawConversion() 
    {
        return SwapGetResolution(this);
    }

    /**
     * @brief Function to get the Voltage on the adc pin.
     * 
     * @return float the voltage in volt.
     * 
     * @details Function to directely get the measured voltage on the adc pin. 
     */
    float HandleADC::GetVoltage() 
    {
        return SwapGetAttentuation(this);
    }

    /**
     * @brief Function to get the voltage for attentuation 0db.
     * 
     * @return float the voltage in volt.
     * 
     * @details Function to get the voltage for attentuation 0db.
     */
    float HandleADC::ADC_GetVoltage0()
    {
        int Raw = ADC_GetRawConversion();
        float result = Raw / (pow(2, (_resolution + 9)) - 1) * 0.8;
        return result;
    }

    /**
     * @brief Function to get the voltage for attentuation 2.5db.
     * 
     * @return float The measured voltage.
     * 
     * @details Function to get the voltage for attentuation 2.5db.
     */
    float HandleADC::ADC_GetVoltage2_5()
    {
        int Raw = ADC_GetRawConversion();
        float result = Raw / (pow(2, (_resolution + 9)) - 1) * 1.1;
        return result;
    }

    /**
     * @brief Function to get the voltage for attentuation 6db.
     * 
     * @return float The measured voltage. 
     * 
     * @details Function to get the voltage for attentuation 6db.
     */
    float HandleADC::ADC_GetVoltage6()
    {
        int Raw = ADC_GetRawConversion();
        float result = Raw / (pow(2, (_resolution + 9)) - 1) * 1.35;
        return result;
    }

    /**
     * @brief Function to get the voltage for attentuation 11db.
     * 
     * @return float the measured voltage.
     * 
     * @details Function to get the voltage for attentuation 11db.
     */
    float HandleADC::ADC_GetVoltage11()
    {
        int Raw = ADC_GetRawConversion();
        float result = Raw / (pow(2, (_resolution + 9)) - 1) * 2.6;
        return result;
    }

    /**
     * @brief Function to get the raw measurment for adc1.
     * 
     * @return int The raw measurment. 
     * 
     * @details Function to get the raw measurment for adc1.
     */
    int HandleADC::ADC_GetConversion1() 
    {
        return adc1_get_raw(_channel1);
    }

    /**
     * @brief Function to get the raw measurment for adc2.
     * 
     * @return int The raw measurement. 
     * 
     * @details Function to get the raw measurment for adc2.
     */
    int HandleADC::ADC_GetConversion2() 
    {
        int val;
        if(ESP_OK != adc2_get_raw(_channel2, _resolution, &val))
        {
            ESP_LOGE(TAG,"This ADC channel is probaly used by wifi :( \n");
        }
        return val;
    }

    /**
     * @brief Function to multi sample the adc.
     * 
     * @param NumOfSamples The number of samples to take.
     * @return float The returned voltage in volt.
     * 
     * @details Function to multi sample the adc by taking loads of samples and returning the average. 
     */
    float HandleADC::MultiSampleVoltage(const int NumOfSamples) 
    {
        float Result = 0.0; 
        for (int i =0; i < NumOfSamples; ++i)
        {
            Result += GetVoltage(); 
        }
        return (Result / NumOfSamples);
    }

}