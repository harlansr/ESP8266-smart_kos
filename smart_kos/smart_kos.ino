// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <WiFiClientSecure.h> 
// #include <ESP8266WebServer.h>
// #include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
// #include <EEPROM.h>
// #include <FS.h>

#include "smart_kos.h"

void setup(void)
{ 
  delay(1000);
  Serial.begin(115200);
  RemoteStart();
  SPIFFS.begin();
  // pinMode(D0, OUTPUT);
  // pinMode(PIN_LED, OUTPUT);
  WiFi.hostname(WIFI_HOSTNAME);

  // String status = stringLoad(11);
  // String ssid = stringLoad(11);
  // String password = stringLoad(12);
  
  // if( status == "" || !WifiConnect(stringToConstChar(ssid), stringToConstChar(password))){
  //   WifiHosted();
  // }else{
  //   Serial.print("Connect to Wifi..");
  // }

  // WifiHosted();
//  WifiConnect("Jaringan Kamar", "harlan123");
  // WebServerRun();
}

void loop() {
  // WebRun();
  // sendRequest();
  // delay(1000);
  // String ssid = stringLoad(0);
  // Serial.print("SSID : ");
  // Serial.println(ssid);
  // WifiScan();

  RemoteSend("off");
  delay(5000);
  RemoteSend("on");
  delay(5000);

  // digitalWrite(D0, LOW);
  // delay(200);
  // digitalWrite(D0, HIGH);
  // digitalWrite(D0, LOW);
  // delay(200);
  // digitalWrite(D0, HIGH);
}

// void switchPin(int pin){
//   if(digitalRead(pin) == HIGH){
//     digitalWrite(PIN_INDICATOR, LOW);
//   }else{
//     digitalWrite(PIN_INDICATOR, HIGH);
//   }
// }


