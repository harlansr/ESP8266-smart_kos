#include "smart_kos.h"

WiFiClient wifiClient;

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