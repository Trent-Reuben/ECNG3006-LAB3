#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "freertos/semphr.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"
#include "sys/time.h"

#define GPIO_OUTPUT_IO  2

//This program make use of 2 tasks with a defined priority hence the following are defined

#define PRIORITY_MID    2
#define PRIORITY_LOW    1

static void gpio_on(void* arg);
static void active_wait();
static void status_msg(void* arg);

#endif