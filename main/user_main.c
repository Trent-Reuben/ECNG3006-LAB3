/*Lab 3
Name: TrentReuben
I.D.:  816015091

Unit Test 2: Set GPIO2 pin low(turn LED OFF)

Purpose: Test to ensure the function sets the gpio pin low 
Pre-Conditions: 3V to esp8266-01, working LED
Test Input: Conifgured GPIO2 pin, gpio pin set to 1, call 'gpio_off' function
Expected: LED turns off 
Test Results: LED turned off 
Test Result Evidence: lab3_unit_test_2.out, lab3_unit_test_2.png

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

    //Create mutex type semaphore
    xMutex = xSemaphoreCreateMutex();
    //GIve semaphore
	xSemaphoreGive(xMutex);

    //stub to set gpio pin off
    printf("Setting gpio high...");
    gpio_set_level(GPIO_OUTPUT_IO,0);
    vTaskDelay(3000 / portTICK_RATE_MS);
    //create task to turn gpio pin on
    xTaskCreate(gpio_off, "gpio_off", 2042, NULL, 1, NULL);
    
    //for heap memory management
	for(;;);
}

//This task set the gpio low, active delays for 0.5s and then task delays for 1s
static void gpio_off(void* arg)
{
    for (;;)
    {
        //Try to take semaphore.
        while(true)
        {
            if(xSemaphoreTake(xMutex, (TickType_t) 10) == pdTRUE)
            {
                //if mutex is obtained display the foll. message
                ESP_LOGI("Task: gpio_off", "Setting GPIO2 low. \n");
                gpio_set_level(GPIO_OUTPUT_IO,1);
                //break for loop once semaphore is obtained
                break;
            }
            else
            {
                continue;
            }
        }

        //0.5s active delay
        active_wait();

        //the mutex must be given back
        xSemaphoreGive(xMutex);

        //1s delay
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

static void active_wait()
{
    //0.5s active delay
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);    
    int64_t time_start = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec; //time since last reset in us

    while(true)
    {
        gettimeofday(&tv_now, NULL);    
        int64_t time_now = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;

        //if 0.5s has elapsed
        if((time_now - time_start) >= 500000)
        {
            break;
        }
    }

    printf("0.5s active wait complete. \n" );
}
