/*Lab2
Name: TrentReuben
I.D.:  816015091

Question 1: 
Create an example application with three tasks that are created in app_main. 
Two tasks should share a single GPIO pin. The GPIO pin should be managed using a semaphore/mutex.  

One task will turn the GPIO pin on, actively wait for 0.5 seconds, and task-delay for 1 second. : see gpio_on
The other will turn the GPIO pin off, actively wait for 0.5 seconds, and task-delay for 1 second. see gpio_off

The third task will print a status message only, and task-delay for 1 second. : see function status_msg

Each task should have it's own priority level : see line app_main

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

    //create task to turn gpio pin on
    xTaskCreate(gpio_on, "gpio_on", 2042, NULL, PRIORITY_MID, NULL);
    vTaskDelay(3000 / portTICK_RATE_MS);

    //create task to display status message
    xTaskCreate(status_msg,"status_msg", 2042, NULL, PRIORITY_LOW, NULL);
    vTaskDelay(3000 / portTICK_RATE_MS);

    for(;;);
}

//This task set the gpio high, active delays for 0.5s and then task delays for 1s
static void gpio_on(void* arg)
{
    for (;;)
    {
        //Try to take semaphore.
        while(true)
        {
            if(xSemaphoreTake(xMutex, (TickType_t) 10) == pdTRUE)
            {
                //if mutex is obtained display the foll. message
                ESP_LOGI("Task: gpio_on", "Setting GPIO2 high. \n");
                gpio_set_level(GPIO_OUTPUT_IO,0);
                break;
            }else
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