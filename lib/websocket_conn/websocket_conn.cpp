#include "websocket_conn.h"
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

void websocket_setup(const char* ssid, const char* password, const char* server, uint16_t port) {
    WiFiMulti.addAP(ssid, password);
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }
    Serial.println("Connected to WiFi");
    webSocket.begin(server, port, "/common");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(2000);
}

void websocket_loop() {
    webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    // Handle WebSocket events
    switch(type) {
		case WStype_DISCONNECTED:
		
			break;
		case WStype_CONNECTED:
			// send message to server when Connected
			webSocket.sendTXT("{\"Signup\":{\"id\":\"30\"}}");
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
