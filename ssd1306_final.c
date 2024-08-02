#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "hal/gpio_types.h"
#include "hal/i2c_types.h"
#include "hal/i2c_types.h"
#include "portmacro.h"
#include "soc/gpio_num.h"
#include "ssd1306.h"
#include "driver/gpio.h"

//semaphore mutex handle
SemaphoreHandle_t xMutex;

//task handles (add or reduce as you like)
TaskHandle_t handle1 = NULL;
TaskHandle_t handle2 = NULL;
TaskHandle_t handle3 = NULL;
TaskHandle_t handle4 = NULL;
TaskHandle_t handle5 = NULL;
TaskHandle_t handle6 = NULL;
TaskHandle_t menu_str = NULL;
TaskHandle_t menu_rtr = NULL;


static const char *TAG = "my_tag";

void task_1(void *arg) {
	if (xSemaphoreTake(xMutex, portMAX_DELAY))
	{
    ESP_LOGI(TAG, "Task 1 is running");
    i2c_driver_delete(I2C_NUM_0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        SSD1306_t dev;
        i2c_master_init(&dev, 21, 22, 27);
        ssd1306_clear_screen(&dev, false);
        ssd1306_init(&dev, 128, 64);
        ssd1306_contrast(&dev, 0xff);
    xSemaphoreGive(xMutex);
    while (1) {
		ESP_LOGI(TAG,"Task 1 is sill running");
		ssd1306_display_text(&dev, 0, "Task 1", 10,false);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Task yield
    }
    }
}

void task_2(void *arg) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        ESP_LOGI(TAG, "Task 2 is running");
        i2c_driver_delete(I2C_NUM_0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        SSD1306_t dev;
        i2c_master_init(&dev, 21, 22, 27);
        ssd1306_clear_screen(&dev, false);
        ssd1306_init(&dev, 128, 64);
        ssd1306_contrast(&dev, 0xff);
        xSemaphoreGive(xMutex);
        while (1) {
			ESP_LOGI(TAG,"Task 2 is sill running");
			ssd1306_display_text(&dev, 0, "Task 2", 10,false);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Task yield
        }
        
    }
}

void task_3(void *arg) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        ESP_LOGI(TAG, "Task 3 is running");
        i2c_driver_delete(I2C_NUM_0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        SSD1306_t dev;
        i2c_master_init(&dev, 21, 22, 27);
        ssd1306_clear_screen(&dev, false);
        ssd1306_init(&dev, 128, 64);
        ssd1306_contrast(&dev, 0xff);
        xSemaphoreGive(xMutex);
        while (1) {
			ESP_LOGI(TAG,"Task 3 is sill running");
			ssd1306_display_text(&dev, 0, "Task 3", 10,false);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Task yield
        }
        
    }
}

void task_4(void *arg) {
    if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        ESP_LOGI(TAG, "Task 4 is running");
        i2c_driver_delete(I2C_NUM_0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        SSD1306_t dev;
        i2c_master_init(&dev, 21, 22, 27);
        ssd1306_clear_screen(&dev, false);
        ssd1306_init(&dev, 128, 64);
        ssd1306_contrast(&dev, 0xff);
        xSemaphoreGive(xMutex);
        while (1) {
			ESP_LOGI(TAG,"Task 4 is sill running");
			ssd1306_display_text(&dev, 0, "Task 4", 10,false);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Task yield
        }
        xSemaphoreGive(xMutex);
    }
}

void task_5(void *arg)
{
    ESP_LOGI(TAG, "Task 5 is running");
    while (1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS); // Add delay to avoid watchdog timer trigger
    }
}

void task_6(void *arg)
{
    ESP_LOGI(TAG, "Task 6 is running");
    while (1)
    {   
        vTaskDelay(100 / portTICK_PERIOD_MS); // Add delay to avoid watchdog timer trigger
    }
}

void menu_return(void *arg)
{
	if(xSemaphoreTake(xMutex, portMAX_DELAY))
	{
	 ESP_LOGI(TAG, "Menu rtr is running");
     i2c_driver_delete(I2C_NUM_0);
     vTaskDelay(1000/portTICK_PERIOD_MS);
     SSD1306_t dev;
     i2c_master_init(&dev, 21, 22, 27);
     ssd1306_clear_screen(&dev, false);
     ssd1306_init(&dev, 128, 64);
     ssd1306_contrast(&dev, 0xff);
     xSemaphoreGive(xMutex);	
     while(1)
     {
        ssd1306_display_text(&dev, 0, "Gpio x for Option 1", 20, false);
        ssd1306_display_text(&dev, 1, "Gpio y for Option 2", 20, false);
        ssd1306_display_text(&dev, 2, "Gpuo z for Option 3", 20, false);
        ssd1306_display_text(&dev, 3, "Gpio a for Option 4", 20, false); 
	 }
	}
}

//main menu init task (this task HAS to keep running)
void menu_init(void *arg)
{
	ESP_LOGI(TAG, "Menu is running");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    SSD1306_t dev;
    i2c_master_init(&dev, 21, 22, 27);
    ssd1306_clear_screen(&dev, false);
    ssd1306_init(&dev, 128, 64);
    ssd1306_contrast(&dev, 0xff);
    ssd1306_display_text(&dev, 0, "Gpio x for Option 1", 20, false);
    ssd1306_display_text(&dev, 1, "Gpio y for Option 2", 20, false);
    ssd1306_display_text(&dev, 2, "Gpuo z for Option 3", 20, false);
    ssd1306_display_text(&dev, 3, "Gpio a for Option 4", 20, false); 
	 
    while (1)
    {
        ESP_LOGI(TAG, "Menu is still running");
        //example input gpios (you can use any gpio of your choice)  
        int gpio_36 = gpio_get_level(36);
        int gpio_35 = gpio_get_level(35);
        int gpio_34 = gpio_get_level(34);
        int gpio_39 = gpio_get_level(39);
        int gpio_32 = gpio_get_level(32);

        printf("GPIO 36: %d\n", gpio_36);
        vTaskDelay(400 / portTICK_PERIOD_MS);
        printf("GPIO 35: %d\n", gpio_35);
        vTaskDelay(400 / portTICK_PERIOD_MS);
        printf("GPIO 34: %d\n", gpio_34);
        vTaskDelay(400 / portTICK_PERIOD_MS); 
        printf("GPIO 39: %d\n", gpio_39);
        vTaskDelay(400 / portTICK_PERIOD_MS); 

         if (gpio_39 == 1 && handle1 == NULL) {
            xTaskCreatePinnedToCore(&task_1, "Task 1", 4096, NULL, 5, &handle1, 1);
            if (handle2) vTaskDelete(handle2);
            if (handle3) vTaskDelete(handle3);
            if (handle4) vTaskDelete(handle4);
            if (handle5) vTaskDelete(handle5);
            if (handle6) vTaskDelete(handle6);
            if (menu_rtr) vTaskDelete(handle6);
        menu_rtr = handle2 = handle3 = handle4 = handle5 = handle6 = NULL;
        } else if (gpio_36 == 1 && handle2 == NULL) {
            xTaskCreatePinnedToCore(&task_2, "Task 2", 4096, NULL, 5, &handle2, 1);
            if (handle1) vTaskDelete(handle1);
            if (handle3) vTaskDelete(handle3);
            if (handle4) vTaskDelete(handle4);
            if (handle5) vTaskDelete(handle5);
            if (handle6) vTaskDelete(handle6);
            if (menu_rtr) vTaskDelete(handle6);
          menu_rtr =  handle1 = handle3 = handle4 = handle5 = handle6 = NULL;
        } else if (gpio_35 == 1 && handle3 == NULL) {
            xTaskCreatePinnedToCore(&task_3, "Task 3", 4096, NULL, 5, &handle3, 1);
            if (handle1) vTaskDelete(handle1);
            if (handle2) vTaskDelete(handle2);
            if (handle4) vTaskDelete(handle4);
            if (handle5) vTaskDelete(handle5);
            if (handle6) vTaskDelete(handle6);
            if (menu_rtr) vTaskDelete(handle6);
        menu_rtr = handle1 = handle2 = handle4 = handle5 = handle6 = NULL;
        } else if (gpio_34 == 1 && handle4 == NULL) {
            xTaskCreatePinnedToCore(&task_4, "Task 4", 4096, NULL, 5, &handle4, 1);
            if (handle1) vTaskDelete(handle1);
            if (handle2) vTaskDelete(handle2);
            if (handle3) vTaskDelete(handle3);
            if (handle5) vTaskDelete(handle5);
            if (handle6) vTaskDelete(handle6);
            if (menu_rtr) vTaskDelete(handle6);
         menu_rtr =  handle1 = handle2 = handle3 = handle5 = handle6 = NULL;
        } else if (gpio_32 == 1 && menu_rtr == NULL) {
			xTaskCreatePinnedToCore(&menu_return, "Menu return", 4096, NULL, 5, &menu_rtr, 1);
            if (handle1) vTaskDelete(handle1);
            if (handle2) vTaskDelete(handle2);
            if (handle3) vTaskDelete(handle3);
            if (handle5) vTaskDelete(handle5);
            if (handle6) vTaskDelete(handle6);
           handle1 = handle2 = handle3 = handle5 = handle6 = NULL;
		}

        vTaskDelay(pdMS_TO_TICKS(100));
    }
     vTaskDelay(pdMS_TO_TICKS(100)); 
}




void app_main()
{
	//gpio configuration
    gpio_set_direction(35, GPIO_MODE_INPUT);
    gpio_set_direction(36, GPIO_MODE_INPUT);
    gpio_set_direction(39, GPIO_MODE_INPUT);
    gpio_set_direction(35, GPIO_MODE_INPUT);
    gpio_config_t io_conf;
    io_conf.intr_type= GPIO_INTR_DISABLE;
    io_conf.mode=GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<< GPIO_NUM_32);
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    
    xMutex = xSemaphoreCreateMutex();
    xSemaphoreGive(xMutex);
    xTaskCreatePinnedToCore(&menu_init, "Main menu task", 4092 * 2, NULL, 6, &menu_str, 0);
}
