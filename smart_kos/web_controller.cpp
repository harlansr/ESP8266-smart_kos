#include "smart_kos.h"

ESP8266WebServer server(80);
int room_temp = 26; 
int room_temp_sleep = -1;


void WebRun(){
  server.handleClient();
}

void WebServerRun(){
  // server.on("/a", HTTP_GET, [](AsyncWebServerRequest *request){});
  server.on("/", HTTP_GET, reqPageLogin);
  server.on("/login", HTTP_POST, reqLogin);
  server.on("/ping", HTTP_GET, reqPing);
  server.on("/config", HTTP_POST, reqConfig);
  server.begin();
  Serial.println("Server started");
}

DynamicJsonDocument postBodyRead(){
  String body = server.arg("plain");
  if (body.startsWith("{")) {
    DynamicJsonDocument jsonBuffer(1024);
    DeserializationError error = deserializeJson(jsonBuffer, body);
    if (error) {
      DynamicJsonDocument responseBuffer(256);
      responseBuffer["status"] = "failed";
      responseBuffer["message"] = "Failed to parse JSON";
      String jsonResponse;
      serializeJson(responseBuffer, jsonResponse);
      server.send(500, "application/json", jsonResponse);
    }
    return jsonBuffer;
  } else {
    DynamicJsonDocument jsonBuffer(256);
    for (int i = 0; i < server.args(); i++) {
      jsonBuffer[server.argName(i)] = server.arg(i);
    }
    return jsonBuffer;
  }
}

void reqPageLogin(){
  String html = HelpLoadFileString("/login.html");

  if(server.arg("ssid_m") != "1"){
    String html_select_ssid = "";
    int n = WiFi.scanNetworks();
    if (n != 0){
      html_select_ssid += "<select name='ssid' id='ssid'>";
      for (int i = 0; i < n; ++i) {
        int wifi_no = i + 1;
        String wifi_ssid = WiFi.SSID(i);
        int wifi_signal = WiFi.RSSI(i);
        bool wifi_locked = !(WiFi.encryptionType(i) == ENC_TYPE_NONE);
        html_select_ssid += "<option value='"+wifi_ssid+"'>"+wifi_ssid+(wifi_locked ? " *":"")+"</option>";
      }
      html_select_ssid += "</select>";
    }
    html.replace("[ssid_m-checked]", "");
    html.replace("[ssid_m-value]", "1");
    html.replace("[input_ssid]", html_select_ssid);
  }else{
    html.replace("[ssid_m-checked]", "checked");
    html.replace("[ssid_m-value]", "0");
    html.replace("[input_ssid]", "<input type='text' name='ssid'>");
  }
  server.send(200, "text/html", html);
}

void reqPageLoginSuccess(){
  File file = HelpLoadFile("/login_success.html");
  server.streamFile(file, "text/html");
}

void reqLogin(){
  DynamicJsonDocument jsonBuffer(256);
  jsonBuffer = postBodyRead();
  const char* b_ssid = jsonBuffer["ssid"];
  const char* b_password = jsonBuffer["password"];

  DynamicJsonDocument responseBuffer(256);
  if(WifiConnect(b_ssid, b_password)){
    responseBuffer["status"] = "success";
    responseBuffer["message"] = "Login success!!";
    String jsonResponse;
    serializeJson(responseBuffer, jsonResponse);
    server.send(200, "application/json", jsonResponse);
    WiFi.softAPdisconnect(true);
  }else{
    responseBuffer["status"] = "failed";
    responseBuffer["message"] = "Login failed";
    String jsonResponse;
    serializeJson(responseBuffer, jsonResponse);
    server.send(200, "application/json", jsonResponse);
  }
}

void reqPing() {
  server.send(200, "text/plain", "Hello from NodeMCU!");
}

void reqConfig(){
  DynamicJsonDocument webBody(256);
  webBody = postBodyRead();
  int resTemp = webBody["temp"];
  int resTempSleep = webBody["temp_sleep"];
  String name = webBody["name"];
  if(resTemp != 0){
    Serial.print("Temp: ");
    Serial.println(resTemp);
    room_temp = resTemp;
  }
  if(resTempSleep != 0){
    Serial.print("Temp Sleep: ");
    Serial.println(resTempSleep);
    room_temp_sleep = resTempSleep;
  }
  if(name != "null" && name != ""){
    Serial.print("Name: ");
    Serial.println(name);
  }

  DynamicJsonDocument responseBuffer(256);
  responseBuffer["status"] = "success";
  String jsonResponse;
  serializeJson(responseBuffer, jsonResponse);
  server.send(200, "application/json", jsonResponse);
}

