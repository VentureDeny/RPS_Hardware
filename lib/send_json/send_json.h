#ifndef SEND_JSON_H
#define SEND_JSON_H

void sendGPSJson(const char* type, const char* id, const char* position);
void sendStatusJson(const char* type, const char* id, const char* data, const char* macAddress, const char* location, const char* speed, 
const char* accelerationX, const char* accelerationY, const char* accelerationZ);
void sendRPSJson(const char* type, const char* id, const char* x, const char* y);
void sendSignupJson(const char* type, const char* id);
void sendAccJson(const char* type, const char* id,float xValue, float yValue, float zValue);
void sendDisJson(const char* type, const char* id,const char* id1, float Distance);
#endif // SEND_JSON_H
