/*Lab3
Name: TrentReuben
I.D.:  816015091

Verification Test: Verifying the system meets the specified requirements

Requirements: 
1. A task turns the GPIO pin on
2. A task turn the GPIO pin off
3. The GPIO pin should be managed using a semaphore/mutex. 
4. The third task will print a status message only for each iteration of change in GPIO.
5. Each task should have it's own priority level in the following order (1.gpio_on; 2. status message 3.gpio_off; 4.status message)

Specification:
- The system will run as defined by the order 1.gpio_on; 2. status message 3.gpio_off; 4.status message

Purpose: To test the system to ensure it meets the requirements and specification

Test Input: Conifgured GPIO2 pin, call gpio_on, call status_msg, call gpio_off

Expected: LED light turns on, status message is diplayed, LED light turns off, status message displayed

Test Results: LED light turns on, status message is diplayed, LED light turns off, status message displayed

Test Result Evidence: lab3_verificationtest.out

*/

#include "main.h"

static const char *TAG = "main";

SemaphoreHandle_t xMutex = NULL;

void app_main(void)
{

	//Create mutex type semaphore
    xMutex = xSemaphoreCreateMutex();
	
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

    printf("\n");

    //Check the semaphore was created successfully before creating the tasks
	if( xMutex != NULL)
    {
		//Create instance of the task to turn set the gpio high
		xTaskCreate(gpio_on, "gpio_on", 2048, NULL, PRIORITY_SUPER, NULL);

        //Create instance of the task to display the status
        xTaskCreate(status_msg, "status_msg", 2048, NULL, PRIORITY_HIGH, NULL);

		//Create instance of the task to turn set the gpio low
		xTaskCreate(gpio_off, "gpio_off", 2048, NULL, PRIORITY_MID, NULL);

        //Create instance of the task to display the status
        xTaskCreate(status_msg, "status_msg", 2048, NULL, PRIORITY_LOW, NULL);
	} 
   
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
                gpio_set_level(GPIO_OUTPUT_IO,0);
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
                gpio_set_level(GPIO_OUTPUT_IO,1);
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