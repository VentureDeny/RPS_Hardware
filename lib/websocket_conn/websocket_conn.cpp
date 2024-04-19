#include "websocket_conn.h"
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    Serial.printf("WebSocket event: %d\n", type);
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("[WebSocket] Disconnected!");
            break;
        case WStype_CONNECTED:
            Serial.println("[WebSocket] Connected!");
            webSocket.sendTXT("{\"Signup\":{\"id\":\"EVA02\"}}");
            break;
        case WStype_TEXT:
            if (payload) {
                Serial.printf("[WebSocket] Received text: %s\n", payload);
                webSocket.sendTXT(payload);  // Consider checking if this is safe to do
            }
            break;
        case WStype_ERROR:
            Serial.println("[WebSocket] Error!");
            break;
        default:
            break;
    }
}


void websocket_setup(const char* ssid, const char* password, const char* server, uint16_t port) {
    WiFiMulti.addAP(ssid, password);
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }
    Serial.println("Connected to WiFi");
    webSocket.begin(server, port, "/common");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(1500);
}

void websocket_loop() {
    webSocket.loop();
}


