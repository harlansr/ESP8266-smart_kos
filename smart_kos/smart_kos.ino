#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <FS.h>

#include "smart_kos.h"


WiFiClient wifiClient;
// ESP8266WebServer server(80);
// WiFiClientSecure wiFiClientSecure;


// WiFi Server



// WIFI Client
String hostname = "SmartKos V0.1";
const char* host = "https://reqres.in";

///////////////////////////////////////////////////////////////////
/////////////////////////// ROOM CONFIG ///////////////////////////
///////////////////////////////////////////////////////////////////


void setup(void)
{ 
  delay(1000);
  Serial.begin(115200);
  RemoteStart();
  SPIFFS.begin();
  // pinMode(D0, OUTPUT);
  // pinMode(PIN_LED, OUTPUT);
  WiFi.hostname("SmartKos V0.1");

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
  WebServerRun();
  
  
}

void loop() {
  // sendRequest();
  WebRun();
  // delay(1000);
  // String ssid = stringLoad(0);
  // Serial.print("SSID : ");
  // Serial.println(ssid);
  // WifiScan();

  delay(2000);
  RemoteSend("off");
  // digitalWrite(D0, LOW);
  // delay(200);
  // digitalWrite(D0, HIGH);
  delay(2000);
  RemoteSend("on");
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

//////////////////////////////////////////////////////////////////////////
////////////////////////////// WiFi ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
////////////////////////////// WEB CLIENT //////////////////////////////
//////////////////////////////////////////////////////////////////////////
void sendRequest(){
  HTTPClient http;
  // WiFiClientSecure httpsClient;
  String ADCData, station, digital0, getData, Link;
  // GET Data
  getData = "?page=1";
  // Link = "https://reqres.in/api/users"+getData;
  // Link = "http://reqres.in/api/users?page=1";
  Link = "http://192.168.137.1:3035/api/website/v1/user/all";

  http.begin(wifiClient, Link);
  int httpCode = http.GET();
  String payload = http.getString();

  // Serial.println(httpCode);
  // Serial.println(payload);
  JsonDocument callback = processResponse(payload);
  String status = callback["status"];
  Serial.print(httpCode);
  Serial.print(" | ");
  Serial.println(status);
  http.end();

  // if(httpCode == 200){
  //   digitalWrite(PIN_INDICATOR, LOW);
  // }else{
  //   digitalWrite(PIN_INDICATOR, HIGH);
  // }
}

JsonDocument processResponse(String jsonResponse) {
  JsonDocument jsonBuffer;
  DeserializationError error = deserializeJson(jsonBuffer, jsonResponse);
  if (error) {
    // Serial.print("Parsing failed: ");
    // Serial.println(error.c_str());
    // return jsonBuffer;
  }
  return jsonBuffer;
}
//////////////////////////////////////////////////////////////////////////
////////////////////////////// WEB SERVER //////////////////////////////
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
////////////////////////////// Local Storage //////////////////////////////
//////////////////////////////////////////////////////////////////////////
void stringSave(int address, String data) {
  EEPROM.begin(data.length() + 1); // Panjang data + 1 untuk menyimpan null-terminator
  for (int i = 0; i < data.length(); ++i) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + data.length(), '\0'); // Menambahkan null-terminator
  EEPROM.commit(); // Menyimpan perubahan
  EEPROM.end(); // Selesai dengan EEPROM
}

// Fungsi untuk membaca string dari EEPROM
String stringLoad(int address) {
  EEPROM.begin(512); // Inisialisasi EEPROM
  String data = "";
  char character = EEPROM.read(address); // Membaca karakter pertama

  // Jika karakter pertama adalah null-terminator, kembalikan string kosong
  if (character == '\0') {
    EEPROM.end(); // Selesai dengan EEPROM
    return data;
  }

  // Jika tidak, lanjutkan membaca data dari EEPROM
  int i = 0;
  do {
    data += character;
    i++;
    character = EEPROM.read(address + i);
  } while (character != '\0');
  
  EEPROM.end(); // Selesai dengan EEPROM
  return data;
}

const char* stringToConstChar(String str) {
  char *buffer = new char[str.length() + 1];
  strcpy(buffer, str.c_str());
  return buffer;
}
