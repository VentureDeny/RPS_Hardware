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
#include <SPI.h>
#include "DW1000Ranging.h"
#include <Wire.h>
#include "DW1000.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <String.h>
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
// connection pins
const uint8_t PIN_RST = 26; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin
float accx;
float accy;
float accz;
float speed = 0;
String location = "108.62,21.894";
void newBlink(DW1000Device* device) {
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}
void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  float dis = DW1000Ranging.getDistantDevice()->getRange();
  sendDisJson("Dis","EVA02","EVA01",dis);
}
void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}
void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}
void gps_task(void *pvParameters) {
    while (1) {
        while (Serial2.available() > 0) {
            char c = Serial2.read();Serial2.available() > 0;
            if (gps.encode(c)) {
                if (gps.location.isValid()) {
                    float latitude = gps.location.lat();
                    float longitude = gps.location.lng();
                    float speed = gps.speed.kmph();
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
void setupDW1000TAG(){
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    DW1000Ranging.useRangeFilter(true);
    //we start the module as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_SHORTDATA_FAST_ACCURACY,false);
    //DW1000Ranging.startAsTag("8D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY,false);
}
void setupDW1000Anchor(){
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    DW1000Ranging.useRangeFilter(true);
    //we start the module as an anchor
    DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_SHORTDATA_FAST_ACCURACY,false);
    //DW1000Ranging.startAsAnchor("72:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY,false);
}
void setupMPU6050(){
     if (!mpu.begin()) {
      Serial.println("Failed to find MPU6050 chip");
      while (1) {
        delay(10);
      }
    }
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
void task1(void *pvParameters) {
    Serial.println("Start xTask1");
    while (1) {
        char accxStr[10];
        char accyStr[10];
        char acczStr[10]; 
        char speedStr[10]; 
        char locationStr[15]; 
        dtostrf(accx, 5, 2, accxStr); 
        dtostrf(accy, 5, 2, accyStr); 
        dtostrf(accz, 5, 2, acczStr); 
        dtostrf(speed, 5, 2, speedStr); 
        sendStatusJson("Status","EVA02","16","82:17:5B:D5:A9:9A:E2:9C",location.c_str(),speedStr,accxStr,accyStr,acczStr);
        vTaskDelay(1500/portTICK_PERIOD_MS); // 延迟1秒20怕
    }
}
void MPU6050(void *pvParameters) {
    Serial.println("Start xTask2 MPU6050");
    unsigned long lastHighMotionTime = 0; // 用于追踪最后一次大幅度运动的时间
    unsigned long currentDelay = 500; // 初始化正常采集间隔为500ms
    while (1) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp); // 从MPU6050获取数据
        accx = a.acceleration.x;
        accy = a.acceleration.y;
        accz = a.acceleration.z;
        sendAccJson("Acc","EVA02",accx,accy,accz);
        if (accx > 2 || accy > 2) {
            lastHighMotionTime = millis(); 
            currentDelay = 100; 
        }
        if (millis() - lastHighMotionTime >= 5000) {
            currentDelay = 500;
        }
        vTaskDelay(currentDelay / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    Serial.println("Start xTaskManagement");
    xTaskCreate(gps_task, "gps_task", 8196, NULL, 1, NULL); // 创建GPS任务
    xTaskCreate(&task1, "Task 1", 8196, NULL, 1, NULL);
    xTaskCreate(&MPU6050, "MPU6050", 16392, NULL, 2, NULL);
    //xTaskCreate(&DW1000Task, "DW1000Task", 8196, NULL, 1, NULL);
}

void setup(){
    websocket_setup("HuaweiMate13","506506506","47.99.133.66",8080);
    Serial.begin(115200); // 初始化用于调试的串口0
    Serial2.begin(9600);
    //setupDW1000TAG();
    setupDW1000Anchor();
    setupMPU6050();
    app_main();
}

void loop(){
   websocket_loop();
   DW1000Ranging.loop();
}

