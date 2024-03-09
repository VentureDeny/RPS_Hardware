#ifndef SEND_JSON_H
#define SEND_JSON_H

void sendGPSJson(const char* type, const char* id, const char* position);
void sendStatusJson(const char* type, const char* id, const char* battery, const char* macAddress);
void sendRPSJson(const char* type, const char* id, const char* x, const char* y);

#endif // SEND_JSON_H
