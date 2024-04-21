#ifndef SMART_KOS_H
#define SMART_KOS_H
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <FS.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define PIN_INDICATOR D0
#define PIN_IR_SENDER D2

// ESP8266WebServer server(80);

///////////////////////// Config /////////////////////////
// IPAddress host_local_IP();
// IPAddress host_subnet();
// IPAddress host_gateway();
// int PIN_INDICATOR();
// int PIN_LED();

///////////////////////// Helper /////////////////////////
String HelpLoadFileString(const char * path);
File HelpLoadFile(const char * path);

///////////////////////// Web Controller /////////////////////////
void WebRun();
void WebServerRun();
void reqPageLogin();
void reqLogin();
void reqPing();
void reqConfig();

/////////////////////////// WiFi ///////////////////////////////////
void WifiScan();
void WifiHosted();
bool WifiConnect(const char* a_ssid, const char* a_password);

/////////////////////////// Sensor ////////////////////////////////
void RemoteStart();
void RemoteSend(String type);



#endif
