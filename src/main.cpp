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


WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

const char* ssid = "YOUR_WIFI_SSID"; // 替换为你的WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // 替换为你的WiFi密码
const char* websocket_server = "ws://example.com:80"; // 替换为你的WebSocket服务器地址

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
		
			break;
		case WStype_CONNECTED:
			// send message to server when Connected
			webSocket.sendTXT("Connected");
			break;
		case WStype_TEXT:
			// send message to server
			webSocket.sendTXT(payload);
			break;
		case WStype_BIN:
			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
	}

}
void sendJson(unsigned char type,unsigned char data0) {
  // 创建JSON对象
  JsonDocument doc;
  doc[type] = data0;
  //doc["time"] = 1351824120;
  //doc["data"][0] = 48.756080;
  //doc["data"][1] = 2.302038;
  // 将JSON对象序列化为字符串
  String jsonString;
  serializeJson(doc, jsonString);
  // 发送JSON字符串到WebSocket服务器
  webSocket.sendTXT(jsonString);
}

// 任务1执行的函数
void task1(void *pvParameters) {
    while (1) {
        
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒
    }
}

// 任务2执行的函数
void task2(void *pvParameters) {
    while (1) {
      
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
    WiFiMulti.addAP("SSID", "passpasspass");

	//WiFi.disconnect();
	while(WiFiMulti.run() != WL_CONNECTED) {
		delay(100);
	}

	// server address, port and URL
	webSocket.begin("192.168.0.123", 81, "/");

	// event handler
	webSocket.onEvent(webSocketEvent);

	// use HTTP Basic Authorization this is optional remove if not needed
	webSocket.setAuthorization("user", "Password");

	// try ever 5000 again if connection has failed
	webSocket.setReconnectInterval(5000);

  app_main();
}

void loop(){
  webSocket.loop();
}
