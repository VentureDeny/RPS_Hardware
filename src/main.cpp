#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

// 任务1执行的函数
void task1(void *pvParameters) {
    while (1) {
        printf("Hello ");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒
    }
}

// 任务2执行的函数
void task2(void *pvParameters) {
    while (1) {
        printf("World!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒
    }
}

void app_main(void) {
    // 创建任务1
    xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
    // 创建任务2
    xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
}

void setup(){
  app_main();
}

void loop(){
  
}
