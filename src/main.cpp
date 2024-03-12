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
#include <NMEAGPS.h>
NMEAGPS gps;
gps_fix fix;

// 定义ESP32的Serial2引脚
#define RX_PIN 16
#define TX_PIN 17


// 任务1执行的函数
// 任务1执行的函数
void task1(void *pvParameters) {
  
    Serial.println("Task 1 started.");
    while (true) {
        while (Serial2.available() > 0) {
            if (gps.decode( Serial2.read() )) {
                Serial.println("GPS data decoded.");
                if (gps.available()) {
                    fix = gps.read();
                    if (fix.valid.location) {
                        Serial.print("Location: ");
                        Serial.print(fix.latitude(), 6);
                        Serial.print(", ");
                        Serial.println(fix.longitude(), 6);
                    } else {
                        Serial.println("Location data is not valid.");
                    }
                } else {
                    Serial.println("No GPS data available.");
                }
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 增加延迟以减少日志量
    }
   
}


// 任务2执行的函数
void task2(void *pvParameters) {
    while (1) {
        sendStatusJson("Status","30","70","A0:20:13:34:E3");
        vTaskDelay(10000 / portTICK_PERIOD_MS); // 延迟1秒20怕
     //   Serial.println("Conn WSServer");
    }
}

void app_main(void) {
    // 创建任务1
    
    xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
    // 创建任务2
    xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
}

void setup(){
    websocket_setup("HuaweiMate13","506506506","47.99.133.66",8080);
    Serial.begin(115200); // 开启与电脑的串行通信
    Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // 开启与GPS模块的串行通信
    app_main();
}

void loop(){
   websocket_loop();
}

