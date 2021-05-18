/**
 * @file HandleADC.h
 * @author your name (you@domain.com)
 * @brief Header file for HandleADC (.h)
 * @version 0.1
 * @date 2021-05-15
 * 
 * @copyright Copyright (c) 2021
 * @details Header file for HandleADC usus the adc driver from espressif. 
 */

#ifndef HandleADC_h
#define HandleADC_h

#include "esp_err.h"
#include <functional>
#include "esp_log.h"
#include <iostream>
#include <cmath>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C"{

    class HandleADC{
        public:
            HandleADC(const gpio_num_t PIN, const adc_bits_width_t Resolution = ADC_WIDTH_BIT_12, const adc_atten_t attentuation = ADC_ATTEN_DB_11);
            HandleADC(const adc1_channel_t channel, const adc_bits_width_t Resolution, const adc_atten_t attentuation); 
            HandleADC(const adc2_channel_t channel, const adc_bits_width_t Resolution, const adc_atten_t attentuation); 

            int ADC_GetRawConversion(); 
            float GetVoltage();
            float MultiSampleVoltage(const int NumOfSamples);
           

        private:
            std::function<esp_err_t(HandleADC *)> SwapInitialize;
            std::function<int(HandleADC *)> SwapGetResolution;
            std::function<float(HandleADC *)> SwapGetAttentuation;

            esp_err_t ADC_Initialize();
            esp_err_t ADC_InitChannel1();
            esp_err_t ADC_InitChannel2();
            int ADC_GetConversion1() ;
            int ADC_GetConversion2() ;
            float ADC_GetVoltage0();
            float ADC_GetVoltage2_5();
            float ADC_GetVoltage6();
            float ADC_GetVoltage11();

            void SetAttentuation();

            adc1_channel_t _channel1;
            adc2_channel_t _channel2;
            const adc_bits_width_t _resolution;
            const adc_atten_t _attentuation; 

            constexpr static const char* TAG = "ADC";
    };

}



#endif