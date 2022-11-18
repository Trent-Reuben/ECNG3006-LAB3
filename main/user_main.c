/*Lab3
Name: TrentReuben
I.D.:  816015091

Unit Test 3: Display of status message

Purpose:  Test to ensure the function displays the  current status of the gpio pin
Pre-Conditions: 3V to esp8266-01, working LED
Test Input: Conifgured GPIO2 pin, gpio pin set to 0, call 'status_msg' function
Expected: status of gpio pin is shown
Test Results: status of gpio pin displayed
Test Result Evidence: lab3_unit_test_3.out

*/

#include "main.h"

static const char *TAG = "main";

SemaphoreHandle_t xMutex = NULL;

void app_main(void)
{
	
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = (1ULL<<GPIO_OUTPUT_IO);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //stub to set gpio pin on
    printf("Turning LED ON...\n");
    gpio_set_level(GPIO_OUTPUT_IO,0);  
    vTaskDelay(1000 / portTICK_RATE_MS);
    //tasks to call status message
    xTaskCreate(status_msg, "status_msg", 2042, NULL, 1, NULL);
}

//this task display the status of the gpio pin
static void status_msg(void* arg)
{
    for(;;)
    {
        //display message for status
        ESP_LOGI(TAG,"GPIO_2 Pin STATUS: %d\n", gpio_get_level(GPIO_OUTPUT_IO));
        //1s delay
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}