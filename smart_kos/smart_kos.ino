#include <ArduinoJson.h>
#include "smart_kos.h"
#include "config.cpp"

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

  WifiHosted();
//  WifiConnect("Jaringan Kamar", "harlan123");
  WebServerRun();
}

void loop() {
  WebRun();
  // sendRequest();
  // delay(1000);
  // TEMP_CURRENT = 3;

  RemoteSend("off",0);
  delay(5000);
  RemoteSend("on",0);
  delay(5000);

  // digitalWrite(D0, LOW);
  // delay(200);
  // digitalWrite(D0, HIGH);
  // digitalWrite(D0, LOW);
  // delay(200);
  // digitalWrite(D0, HIGH);
}



