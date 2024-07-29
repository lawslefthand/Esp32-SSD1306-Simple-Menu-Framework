#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/semphr.h"
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
TaskHandle_t menu = NULL;

static const char *TAG= "my_tag";


void task_1(void *arg)
{
	
	ESP_LOGI(TAG,"Task 1 is running");
	SSD1306_t dev;
    i2c_master_init(&dev, 21, 22, 27);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
	while(1)
	{
		//insert looping code here (you can use any kind of loop but task has to have 1 infinite loop)
	 ssd1306_display_text(&dev, 0, "Add your text",11 , false);
	}
}

//example protected resource task 1
void task_2(void *arg)
{
	if (xSemaphoreTake(xMutex, portMAX_DELAY))
	{
	ESP_LOGI(TAG,"Task 2 is running");
	SSD1306_t dev;
    i2c_master_init(&dev, 21, 22, 27);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
   ssd1306_contrast(&dev, 0xff);
	while(1)
	{
	 ssd1306_display_text(&dev, 0, "Add your text",11 , false);	
	}
	}
}
 
//example protected resource task 2     
void task_3(void *arg)
{   
	if (xSemaphoreTake(xMutex, portMAX_DELAY))
	{
    ESP_LOGI(TAG,"Task 3 is running");
    SSD1306_t dev;
    i2c_master_init(&dev, 21, 22, 27);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
    while(1)
	{
	  ssd1306_display_text(&dev, 0, "Add your text",11 , false);
	}
	}
}

void task_4(void *arg) 
{    
   ESP_LOGI(TAG,"Task 4 is running");
   SSD1306_t dev;
   i2c_master_init(&dev, 21, 22, 27);
   ssd1306_init(&dev, 128, 64);
   ssd1306_clear_screen(&dev, false);
   ssd1306_contrast(&dev, 0xff);
   while(1)
	{
	  ssd1306_display_text(&dev, 0, "Add your text",11 , false);
	}
}

void task_5(void *arg)
{
   ESP_LOGI(TAG,"Task 5 is running");
   SSD1306_t dev;
   i2c_master_init(&dev, 21, 22, 27);
   ssd1306_init(&dev, 128, 64);
   ssd1306_clear_screen(&dev, false);
   ssd1306_contrast(&dev, 0xff);
   while(1)
	{
		
	}
}

void task_6(void *arg)
{
   
   ESP_LOGI(TAG,"Task 6 is running");
   SSD1306_t dev;
   i2c_master_init(&dev, 21, 22, 27);
   ssd1306_init(&dev, 128, 64);
   ssd1306_clear_screen(&dev, false);
   ssd1306_contrast(&dev, 0xff);
   
   while(1)
	{
	ssd1306_display_text_x3(&dev, 0, "Generic", 4, false);	
	}
}

//main menu init task (this task HAS to keep running)
void menu_init(void *arg)
{
  ESP_LOGI(TAG,"Menu is running");
  
  SSD1306_t dev;
  i2c_master_init(&dev, 21, 22, 27);
  ssd1306_init(&dev, 128, 64);
  ssd1306_clear_screen(&dev, false);
  ssd1306_contrast(&dev, 0xff);
  
  //change page,length and text in any way you like
  ssd1306_display_text_x3(&dev, 0, "Menu", 4, false);
  ssd1306_display_text_x3(&dev, 3, "Option 1", 8, false);
  ssd1306_display_text_x3(&dev, 4, "Option 2", 8, false);
  ssd1306_display_text_x3(&dev, 5, "Option 3", 8, false);
  ssd1306_display_text_x3(&dev, 6, "Option 4", 8, false);
   
   while(1)
  {
   
   
   //example input gpios (you can use any gpio of your choice)  
   int gpio_36 = gpio_get_level(36);
   int gpio_35 = gpio_get_level(35);
   int gpio_34 = gpio_get_level(34);
   int gpio_39 = gpio_get_level(39);
   
    printf("GPIO 36: %d\n", gpio_36);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("GPIO 35: %d\n", gpio_35);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("GPIO 34: %d\n", gpio_34);
    vTaskDelay(100 / portTICK_PERIOD_MS); 
    printf("GPIO 39: %d\n", gpio_39);
    vTaskDelay(100 / portTICK_PERIOD_MS); 

   
   if (gpio_39 == 1)
    {
       xTaskCreate(&task_1, "Task 1",4092, NULL, 5, &handle1);
        
        //deleting any presently running tasks
        vTaskDelete(handle2);
        vTaskDelete(handle3);
        vTaskDelete(handle4);
        vTaskDelete(handle5);
        vTaskDelete(handle6);
       
        //resetting handles back to null after deletion
        handle2 = NULL;
        handle3 = NULL;
        handle4 = NULL;
        handle5 = NULL;
        handle6 = NULL;
        
    }
    
     
   else if (gpio_36 == 1)
    
    {
       
        xTaskCreate(&task_2, "Task2", 4092, NULL, 5, &handle2);
        vTaskDelete(handle1);
        vTaskDelete(handle5);
        vTaskDelete(handle4);
        vTaskDelete(handle3);
        vTaskDelete(handle6);
        
       

        handle1 = NULL;
        handle3 = NULL;
        handle4 = NULL;
        handle5 = NULL;
        handle6 = NULL;
       
    }
    
   else if (gpio_35 == 1)
    {
        xTaskCreate(&task_3, "Task 3", 4092, NULL, 5, &handle3);
        vTaskDelete(handle1);
        vTaskDelete(handle5);
        vTaskDelete(handle4);
        vTaskDelete(handle2);
        vTaskDelete(handle6);
        

        handle2 = NULL;
        handle1 = NULL;
        handle4 = NULL;
        handle5 = NULL;
        handle6 = NULL;
        
    }
    
   else if (gpio_34 == 1)
    {
        xTaskCreate(&task_4, "Task 4", 4092, NULL, 5, &handle4);
        vTaskDelete(handle1);
        vTaskDelete(handle5);
        vTaskDelete(handle2);
        vTaskDelete(handle3);
        vTaskDelete(handle6);

        handle2 = NULL;
        handle3 = NULL;
        handle1 = NULL;
        handle5 = NULL;
        handle6 = NULL;
    }
   
   //add or remove tasks by your choice
   
   /*  
   else if (gpio_34 == 1)
    {
        xTaskCreate(&task_5, "Task 5", 4092, NULL, 5, &handle5);
        vTaskDelete(handle1);
        vTaskDelete(handle2);
        vTaskDelete(handle4);
        vTaskDelete(handle3);
        vTaskDelete(handle6);

        handle2 = NULL;
        handle3 = NULL;
        handle4 = NULL;
        handle1 = NULL;
        handle6 = NULL;
    }*/
    
   /*else if (gpio_34 == 1)
    {
        xTaskCreate(&task_6, "Task 6", 4092, NULL, 5, &handle6);
        vTaskDelete(handle1);
        vTaskDelete(handle5);
        vTaskDelete(handle4);
        vTaskDelete(handle3);
        vTaskDelete(handle2);

        handle2 = NULL;
        handle3 = NULL;
        handle4 = NULL;
        handle5 = NULL;
        handle1 = NULL;
    }
    
}*/
     vTaskDelay(pdMS_TO_TICKS(100));
}
}

  


void app_main()
{
 
 xMutex = xSemaphoreCreateMutex();
 xSemaphoreGive(xMutex);
 xTaskCreate(&menu_init, "Main menu task",4092, NULL, 4,&menu);
 
}    
    

