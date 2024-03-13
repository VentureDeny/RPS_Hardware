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
#include <TinyGPSPlus.h>
TinyGPSPlus gps;

void gps_task(void *pvParameters) {
    //Serial.println("Start gps_task");
    while (1) {
        //Serial.println("Start gps_task");
        while (Serial2.available() > 0) {
            //Serial.println("Start gps_task2");
            char c = Serial2.read();Serial2.available() > 0;
            if (gps.encode(c)) {
                if (gps.location.isValid()) {
                    float latitude = gps.location.lat();
                    float longitude = gps.location.lng();
                    // 根据需要调用sendStatusJson或其他函数来处理GPS数据
                    // 例如: sendStatusJson("GPS", String(latitude, 6), String(longitude, 6), "A0:20:13:34:E3");
                    Serial.print("Latitude= ");
                    Serial.print(latitude, 6);
                    Serial.print(" Longitude= ");
                    Serial.println(longitude, 6);
                }
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 每秒读取一次
    }
}



void task1(void *pvParameters) {
    //Serial.println("Start xTask1");
    while (1) {
        sendStatusJson("Status","EVANGELION_01_TESTTYPE","30","A0:20:13:34:E3");
        vTaskDelay(3000/portTICK_PERIOD_MS); // 延迟1秒20怕
    }
   
}


// 任务2执行的函数
void task2(void *pvParameters) {
    //Serial.println("Start xTask2");
    while (1) {
        sendStatusJson("Status","EVANGELION_02_TESTTYPE","70","A0:20:13:34:E3");
        vTaskDelay(3000/portTICK_PERIOD_MS); // 延迟1秒20怕
    }
}

void app_main(void) {
    Serial.println("Start xTaskManagement");
    xTaskCreate(gps_task, "gps_task", 2048, NULL, 1, NULL); // 创建GPS任务
    xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
}

void setup(){
    websocket_setup("IoT2.4","qwertyuiop123","47.99.133.66",8080);
    Serial.begin(115200); // 初始化用于调试的串口0
    Serial.println("Start Init Uart");
  // 使用Arduino的方式初始化串口2
    Serial2.begin(9600);
    app_main();
}

void loop(){
   websocket_loop();
}

