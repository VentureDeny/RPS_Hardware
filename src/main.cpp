#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>
#include <send_json.h>
#include <websocket_conn.h>


// 任务1执行的函数
void task1(void *pvParameters) {
    while (1) {
       
        sendGPSJson("GPS","30","29.02,29.77");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒
        Serial.println("Conn WSServer");
    }
}

// 任务2执行的函数
void task2(void *pvParameters) {
    while (1) {
        sendStatusJson("Status","30","70","A0:20:13:34:E3");
        vTaskDelay(10000 / portTICK_PERIOD_MS); // 延迟1秒
        Serial.println("Conn WSServer");
    }
}

void app_main(void) {
    // 创建任务1
    
    xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
    // 创建任务2
    xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
}

void setup(){
    websocket_setup("IoT2.4","qwertyuiop123","192.168.0.197",8080);
    
    app_main();
}

void loop(){
   websocket_loop();
}
