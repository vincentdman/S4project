/**
 * @file HandleSPI.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "HandleSPI.h"

extern "C"
{

    HandleSPI::HandleSPI(spi_host_device_t Host)
        : SPI_Host(Host)
    {
        esp_err_t Error = ESP_OK;
        Error |= SPI_Initialize();
        ESP_ERROR_CHECK(Error);
        Error |= SPI_AddBus();
        ESP_ERROR_CHECK(Error);
        if(Error != ESP_OK)
        {
            ESP_LOGE(TAG,"Error init");
        }
    }
    esp_err_t HandleSPI::SPI_Initialize()
    {
        ESP_LOGI(TAG, "Initialized SPI!");
        return spi_bus_initialize(SPI_Host, &SPI_Config, 0 );//SPI_DMA_CH_AUTO);
    }

    esp_err_t HandleSPI::SPI_AddBus()
    {
        return spi_bus_add_device(SPI_Host, &SPI_DeviceConfig, &SPI_DeviceHandle);
    }

    HandleSPI::~HandleSPI()
    {
        spi_bus_remove_device(SPI_DeviceHandle);
    }

    esp_err_t HandleSPI::SPI_Send(spi_transaction_t *transaction)
    {
        return spi_device_polling_transmit(SPI_DeviceHandle, transaction);
    }
}
