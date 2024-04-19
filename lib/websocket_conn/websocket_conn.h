#ifndef WEBSOCKET_CONN_H
#define WEBSOCKET_CONN_H

#include "WebSocketsClient.h"

extern WebSocketsClient webSocket;

void websocket_setup(const char* ssid, const char* password, const char* server, uint16_t port);
void websocket_loop();
void sendAccJson(const char* type, float xValue, float yValue, float zValue);
#endif // WEBSOCKET_CONN_H
