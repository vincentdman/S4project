/**
 * @file HandleSPI.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HANDLESPI_H
#define HANDLESPI_H

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"


extern "C"
{
    class HandleSPI
    {
    public:
        HandleSPI(spi_host_device_t Host);
        ~HandleSPI();
        esp_err_t SPI_Send(spi_transaction_t *transaction);
    private:
        esp_err_t SPI_Initialize();
        esp_err_t SPI_AddBus();

        const spi_host_device_t SPI_Host;

        spi_bus_config_t SPI_Config =
        {
            .mosi_io_num = GPIO_NUM_12,
            .miso_io_num = GPIO_NUM_13,
            .sclk_io_num = GPIO_NUM_14,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 0,
            .flags = SPICOMMON_BUSFLAG_MASTER | SPICOMMON_BUSFLAG_SCLK | SPICOMMON_BUSFLAG_MISO | SPICOMMON_BUSFLAG_MOSI,
            .intr_flags = ESP_INTR_FLAG_INTRDISABLED
        };
        spi_device_handle_t SPI_DeviceHandle;

        spi_device_interface_config_t SPI_DeviceConfig = 
        {
        .mode=0,      //SPI mode 0
        .clock_speed_hz= 4000000u,                   //Clock out at 26 MHz                   
        .spics_io_num = GPIO_NUM_4,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        //.pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
        };
        constexpr static const char *TAG = "SPI";
       
    };

}
#endif
