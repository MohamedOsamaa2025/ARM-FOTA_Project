#ifndef WIFI_INTERFACE_H
#define WIFI_INTERFACE_H

#include "../include/WiFi_config.h"
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

void WiFi_voidInit(void);
u8 u8ValidateCmd(u8* buffer, u16 bufferSize);
void WiFi_voidConnectToWiFi(const u8* ssid, const u8* password);
void WiFi_voidServerConnect(const u8* ip, const u8* port);
void WiFi_voidSendHttpRequest(const u8* request);
// void WiFi_voidReceiveResponse(u8* buffer, u16 bufferSize);

void WiFi_voidDisConnectToWiFi(const u8* ssid, const u8* password);
void delay_us(u32 us);

#endif /* WIFI_INTERFACE_H */
