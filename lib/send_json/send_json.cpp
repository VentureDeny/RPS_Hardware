#include "send_json.h"
#include "websocket_conn.h"
#include <ArduinoJson.h>

void sendGPSJson(const char* type, const char* id, const char* position) {
    // Implementation...
    JsonDocument doc;
    JsonObject gpsObj = doc[type].to<JsonObject>();
    gpsObj["id"] = id;
    gpsObj["location"] = position;

    // 将 JSON 对象序列化为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 发送 JSON 字符串到 WebSocket 服务器
    webSocket.sendTXT(jsonString);
}

void sendStatusJson(const char* type, const char* id, const char* battery, const char* macAddress) {
    // Implementation...
    JsonDocument doc;
    JsonObject statusObj = doc[type].to<JsonObject>();
    statusObj["id"] = id;
    statusObj["battery"] = battery;
    statusObj["MAC"] = macAddress;

    // 将 JSON 对象序列化为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 发送 JSON 字符串到 WebSocket 服务器
    webSocket.sendTXT(jsonString);
}

void sendRPSJson(const char* type, const char* id, const char* x, const char* y) {
    // Implementation...
    JsonDocument doc;
    JsonObject rpsObj = doc[type].to<JsonObject>();
    rpsObj["id"] = id;
    rpsObj["x"] = x;
    rpsObj["y"] = y;

    // 将 JSON 对象序列化为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 发送 JSON 字符串到 WebSocket 服务器
    webSocket.sendTXT(jsonString);
}
