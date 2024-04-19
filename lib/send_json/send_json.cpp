#include "send_json.h"
#include "websocket_conn.h"
#include <ArduinoJson.h>
#include <string.h>
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

void sendStatusJson(const char* type, const char* id, const char* battery, const char* macAddress, const char* location, const char* speed, 
const char* accelerationX, const char* accelerationY, const char* accelerationZ) {

    String jsonString = "{\"";
    jsonString += type;
    jsonString += "\":{\"id\":\"";
    jsonString += id;
    jsonString += "\",\"battery\":\"";
    jsonString += battery;
    jsonString += "\",\"MAC\":\"";
    jsonString += macAddress;

    // 如果提供了位置信息，则将位置信息添加到 JSON 字符串中
    if (location != nullptr) {
        jsonString += "\",\"location\":\"";
        jsonString += location;
    }

    // 如果提供了速度信息，则将速度信息添加到 JSON 字符串中
    if (speed != nullptr) {
        jsonString += "\",\"speed\":\"";
        jsonString += speed;
    }

    // 如果提供了加速度信息，则将加速度信息添加到 JSON 字符串中
    if (accelerationX != nullptr && accelerationY != nullptr && accelerationZ != nullptr) {
        jsonString += "\",\"accelerationX\":\"";
        jsonString += accelerationX;
        jsonString += "\",\"accelerationY\":\"";
        jsonString += accelerationY;
        jsonString += "\",\"accelerationZ\":\"";
        jsonString += accelerationZ;
    }

    jsonString += "\"}}";

    // 检查 WebSocket 是否连接，并发送 JSON 字符串
    if (webSocket.isConnected()) { 
        webSocket.sendTXT(jsonString); 
    }  
}

void sendAccJson(const char* type, const char* id,float xValue, float yValue, float zValue) {
    
    JsonDocument doc;
    JsonObject gpsObj = doc[type].to<JsonObject>();
    gpsObj["id"] = id;
    gpsObj["accx"] = xValue;
    gpsObj["accy"] = yValue;
    gpsObj["accz"] = zValue;

    // 将 JSON 对象序列化为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 发送 JSON 字符串到 WebSocket 服务器
    if (webSocket.isConnected()) { webSocket.sendTXT(jsonString); }
}

void sendDisJson(const char* type, const char* id0,const char* id1, float Distance) {
    
    JsonDocument doc;
    JsonObject gpsObj = doc[type].to<JsonObject>();
    gpsObj["id0"] = id0;
    gpsObj["id1"] = id1;
    gpsObj["distance"] = Distance;

    // 将 JSON 对象序列化为字符串
    String jsonString;
    serializeJson(doc, jsonString);

    // 发送 JSON 字符串到 WebSocket 服务器
    if (webSocket.isConnected()) { webSocket.sendTXT(jsonString); }
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
    webSocket.sendTXT(jsonString.c_str());
}

