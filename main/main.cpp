/**
 * @file main.cpp
 * @author Vincent de Man
 * @brief Main application for S4 Project (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @details main.cpp main code for project S4  
 */
#include "main.h"
//ESP_ERROR_CHECK(Error);
extern "C" void app_main(void)
{
  HandlePIN ChipSelect(GPIO_NUM_4);
  HandlePIN Clockspi(GPIO_NUM_14);
  Clockspi.PIN_High();
  HandleSPI testspi(SPI2_HOST);
  ESP_LOGI(TAG, "Started!\n");
  esp_err_t Error = ESP_OK;
  while (1)
  {

    spi_transaction_t read =
        {
            .flags = SPI_TRANS_USE_RXDATA,
            .cmd = 0,           //0x03 | 0x37,
            .addr = 0b11011000, //0x2c,
            .length = 8,
            .rxlength = 8,
            .tx_buffer = nullptr,
            .rx_buffer = nullptr,
        };

    spi_transaction_t write =
        {
            .flags = SPI_TRANS_USE_TXDATA,
            .cmd = 0,           //0x03 | 0x37,
            .addr = 0b01011000, //0x2c,
            .length = 8,
            .rxlength = 8,
            .tx_buffer = nullptr,
            .rx_buffer = nullptr,
        };

    write.tx_data[0] = 0b10111110;

    testspi.SPI_Send(&write);

    testspi.SPI_Send(&read);

    //ESP_LOGI(TAG,"Data is: %d\n", read.rx_data[0]);
    ESP_LOGI(TAG, "\nWritten %d\nRead %d\n", write.tx_data[0], read.rx_data[0]);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };
}

//TODO things to implement:
//TODO private stuff should have underscores
//TODO hal sensor adc class
//TODO lcd class lcd_commands.h update (maybe flags)
//TODO lcd class pinout_t remove i2c ports (not necesarry )
//TODO SD card library

//TODO things to learn:
//TODO constexpr
//TODO rule of three / five
//TODO static functions
//TODO enum class strongly typed
//TODO move semantics
//TODO perfect forwarding and reference collapsing
//}
