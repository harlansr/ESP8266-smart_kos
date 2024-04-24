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

#define PIN_INDICATOR   D0
#define PIN_IR_SENDER   D2
#define WIFI_HOSTNAME   "SmartKos V0.1"
#define WIFI_SSID       "Secret Wifi"
#define WIFI_PASSWORD   0

#define HOST_LOCAL_IP   (192,168,1,1)
#define HOST_SUBNET     (255,255,255,0)
#define HOST_GATEWAY    (192,168,1,1)

// #define TEMP_CURRENT    0
///////////////////////// helper.cpp /////////////////////////
String HelpLoadFileString(const char * path);
File HelpLoadFile(const char * path);

///////////////////////// web_controller.cpp /////////////////////////
void WebRun();
void WebServerRun();
void reqPageLogin();
void reqLogin();
void reqPing();
void reqConfig();

/////////////////////////// wifi.cpp ///////////////////////////////////
void WifiScan();
void WifiHosted();
bool WifiConnect(const char* a_ssid, const char* a_password);

/////////////////////////// sensor.cpp ////////////////////////////////
void RemoteStart();
void RemoteSend(String type, int temp);

/////////////////////////// web_client.cpp ////////////////////////////
void sendRequest();
JsonDocument processResponse(String jsonResponse);

#endif
