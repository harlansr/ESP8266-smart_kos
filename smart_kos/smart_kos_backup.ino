// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <WiFiClientSecure.h> 
// #include <ESP8266WebServer.h>
// #include <ESP8266HTTPClient.h>
// #include <ArduinoJson.h>
// #include <EEPROM.h>
// #include <FS.h>

// #include "smart_kos.h"


// WiFiClient wifiClient;
// ESP8266WebServer server(80);
// // WiFiClientSecure wiFiClientSecure;
// int PIN_INDICATOR = D0;
// int PIN_LED = D1;

// // WiFi Server
// IPAddress host_local_IP(192,168,1,1);
// IPAddress host_subnet(255,255,255,0);
// IPAddress host_gateway(192,168,1,1);
// const char *host_ssid = "Secret Wifi";
// const char *host_password = 0; 

// // WIFI Client
// String hostname = "SmartKos V0.1";
// const char* host = "https://reqres.in";

// ///////////////////////////////////////////////////////////////////
// /////////////////////////// ROOM CONFIG ///////////////////////////
// ///////////////////////////////////////////////////////////////////
// int room_temp = 26; 
// int room_temp_sleep = -1;

// void setup(void)
// { 
//   delay(1000);
//   Serial.begin(115200);
//   pinMode(PIN_INDICATOR, OUTPUT);
//   pinMode(PIN_LED, OUTPUT);
//   WiFi.hostname("SmartKos V0.1");

//   // String status = stringLoad(11);
//   // String ssid = stringLoad(11);
//   // String password = stringLoad(12);
  
//   // if( status == "" || !WifiConnect(stringToConstChar(ssid), stringToConstChar(password))){
//   //   WifiHosted();
//   // }else{
//   //   Serial.print("Connect to Wifi..");
//   // }

//   WifiHosted();
// //  WifiConnect("Jaringan Kamar", "harlan123");
//   WebServerRun();

// //  delay(3000);
// //  bool success = SPIFFS.begin();
// //  if(success){
// //    Serial.println("File system success");
// //  }else{
// //    Serial.println("File system failed");
// //  }
// }

// void loop() {
//   // sendRequest();
//   server.handleClient();
//   delay(1000);
//   // String ssid = stringLoad(0);
//   // Serial.print("SSID : ");
//   // Serial.println(ssid);
//   // WifiScan();
// }

// void switchPin(int pin){
//   if(digitalRead(pin) == HIGH){
//     digitalWrite(PIN_INDICATOR, LOW);
//   }else{
//     digitalWrite(PIN_INDICATOR, HIGH);
//   }
// }

// //////////////////////////////////////////////////////////////////////////
// ////////////////////////////// WiFi ////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////

// void WifiScan(){
//   Serial.println("-------------------------------------");
//   Serial.println("scan start");
//   Serial.println("-------------------------------------");

//   // WiFi.scanNetworks will return the number of networks found
//   int n = WiFi.scanNetworks();
//   Serial.println("scan done");
//   if (n == 0) {
//     Serial.println("no networks found");
//   } else {
//     Serial.print(n);
//     Serial.println(" networks found");
//     for (int i = 0; i < n; ++i) {
//       // Print SSID and RSSI for each network found
//       Serial.print(i + 1);
//       Serial.print(": ");
//       Serial.print(WiFi.SSID(i));
//       Serial.print(" (");
//       Serial.print(WiFi.RSSI(i));
//       Serial.print(")");
//       Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
//       delay(10);
//     }
//   }
//   Serial.println("-------------------------------------");
// }

// bool WifiConnect(const char* a_ssid, const char* a_password){
//   // WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
//   // delay(1000);
//   // WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
//   WiFi.begin(a_ssid, a_password);
//   delay(100);

//   int count = 0;
//   while (WiFi.status() == WL_IDLE_STATUS) {
//     digitalWrite(PIN_INDICATOR, LOW);
//     delay(500);
//     digitalWrite(PIN_INDICATOR, HIGH);
//     delay(500);
//     Serial.print(".");
//     count++;
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println(WiFi.localIP());
//   return WiFi.status() == WL_CONNECTED;
// }

// void WifiHosted(){
//   WiFi.softAPConfig(host_local_IP, host_gateway, host_subnet);
//   WiFi.softAP(host_ssid, host_password);       //Memulai membuat acces point
//   Serial.print("Access Point \"");
//   Serial.print(host_ssid);
//   Serial.println("\" started");
//   Serial.print("IP address:\t");
//   Serial.println(WiFi.softAPIP()); 
// }

// //////////////////////////////////////////////////////////////////////////
// ////////////////////////////// WEB CLIENT //////////////////////////////
// //////////////////////////////////////////////////////////////////////////
// void sendRequest(){
//   HTTPClient http;
//   // WiFiClientSecure httpsClient;
//   String ADCData, station, digital0, getData, Link;
//   // GET Data
//   getData = "?page=1";
//   // Link = "https://reqres.in/api/users"+getData;
//   // Link = "http://reqres.in/api/users?page=1";
//   Link = "http://192.168.137.1:3035/api/website/v1/user/all";

//   http.begin(wifiClient, Link);
//   int httpCode = http.GET();
//   String payload = http.getString();

//   // Serial.println(httpCode);
//   // Serial.println(payload);
//   JsonDocument callback = processResponse(payload);
//   String status = callback["status"];
//   Serial.print(httpCode);
//   Serial.print(" | ");
//   Serial.println(status);
//   http.end();

//   // if(httpCode == 200){
//   //   digitalWrite(PIN_INDICATOR, LOW);
//   // }else{
//   //   digitalWrite(PIN_INDICATOR, HIGH);
//   // }
// }

// JsonDocument processResponse(String jsonResponse) {
//   JsonDocument jsonBuffer;
//   DeserializationError error = deserializeJson(jsonBuffer, jsonResponse);
//   if (error) {
//     // Serial.print("Parsing failed: ");
//     // Serial.println(error.c_str());
//     // return jsonBuffer;
//   }
//   return jsonBuffer;
// }
// //////////////////////////////////////////////////////////////////////////
// ////////////////////////////// WEB SERVER //////////////////////////////
// //////////////////////////////////////////////////////////////////////////
// void WebServerRun(){
//   // server.on("/a", HTTP_GET, [](AsyncWebServerRequest *request){});
//   server.on("/", HTTP_GET, reqPageLogin);
//   server.on("/login", HTTP_POST, reqLogin);
//   server.on("/ping", HTTP_GET, reqPing);
//   server.on("/config", HTTP_POST, reqConfig);
//   server.begin();
//   Serial.println("Server started");
// }

// DynamicJsonDocument postBodyRead(){
//   String body = server.arg("plain");
//   if (body.startsWith("{")) {
//     DynamicJsonDocument jsonBuffer(1024);
//     DeserializationError error = deserializeJson(jsonBuffer, body);
//     if (error) {
//       DynamicJsonDocument responseBuffer(256);
//       responseBuffer["status"] = "failed";
//       responseBuffer["message"] = "Failed to parse JSON";
//       String jsonResponse;
//       serializeJson(responseBuffer, jsonResponse);
//       server.send(500, "application/json", jsonResponse);
//     }
//     return jsonBuffer;
//   } else {
//     DynamicJsonDocument jsonBuffer(256);
//     for (int i = 0; i < server.args(); i++) {
//       jsonBuffer[server.argName(i)] = server.arg(i);
//     }
//     return jsonBuffer;
//   }
// }

// void reqPageLogin(){
//   String html = HelpLoadFileString("/login.html");

//   if(server.arg("ssid_m") != "1"){
//     String html_select_ssid = "";
//     int n = WiFi.scanNetworks();
//     if (n != 0){
//       html_select_ssid += "<select name='ssid' id='ssid'>";
//       for (int i = 0; i < n; ++i) {
//         int wifi_no = i + 1;
//         String wifi_ssid = WiFi.SSID(i);
//         int wifi_signal = WiFi.RSSI(i);
//         bool wifi_locked = !(WiFi.encryptionType(i) == ENC_TYPE_NONE);
//         html_select_ssid += "<option value='"+wifi_ssid+"'>"+wifi_ssid+(wifi_locked ? " *":"")+"</option>";
//       }
//       html_select_ssid += "</select>";
//     }
//     html.replace("[ssid_m-checked]", "");
//     html.replace("[ssid_m-value]", "1");
//     html.replace("[input_ssid]", html_select_ssid);
//   }else{
//     html.replace("[ssid_m-checked]", "checked");
//     html.replace("[ssid_m-value]", "0");
//     html.replace("[input_ssid]", "<input type='text' name='ssid'>");
//   }
//   server.send(200, "text/html", html);
// }

// void reqPageLoginSuccess(){
//   File file = HelpLoadFile("/login_success.html");
//   server.streamFile(file, "text/html");
// }

// void reqLogin(){
//   DynamicJsonDocument jsonBuffer(256);
//   jsonBuffer = postBodyRead();
//   const char* b_ssid = jsonBuffer["ssid"];
//   const char* b_password = jsonBuffer["password"];

//   DynamicJsonDocument responseBuffer(256);
//   if(WifiConnect(b_ssid, b_password)){
//     responseBuffer["status"] = "success";
//     responseBuffer["message"] = "Login success!!";
//     String jsonResponse;
//     serializeJson(responseBuffer, jsonResponse);
//     server.send(200, "application/json", jsonResponse);
//     WiFi.softAPdisconnect(true);
//   }else{
//     responseBuffer["status"] = "failed";
//     responseBuffer["message"] = "Login failed";
//     String jsonResponse;
//     serializeJson(responseBuffer, jsonResponse);
//     server.send(200, "application/json", jsonResponse);
//   }
// }

// void reqPing() {
//   server.send(200, "text/plain", "Hello from NodeMCU!");
// }

// void reqConfig(){
//   DynamicJsonDocument webBody(256);
//   webBody = postBodyRead();
//   int resTemp = webBody["temp"];
//   int resTempSleep = webBody["temp_sleep"];
//   String name = webBody["name"];
//   if(resTemp != 0){
//     Serial.print("Temp: ");
//     Serial.println(resTemp);
//     room_temp = resTemp;
//   }
//   if(resTempSleep != 0){
//     Serial.print("Temp Sleep: ");
//     Serial.println(resTempSleep);
//     room_temp_sleep = resTempSleep;
//   }
//   if(name != "null" && name != ""){
//     Serial.print("Name: ");
//     Serial.println(name);
//   }

//   DynamicJsonDocument responseBuffer(256);
//   responseBuffer["status"] = "success";
//   String jsonResponse;
//   serializeJson(responseBuffer, jsonResponse);
//   server.send(200, "application/json", jsonResponse);
// }

// //////////////////////////////////////////////////////////////////////////
// ////////////////////////////// Local Storage //////////////////////////////
// //////////////////////////////////////////////////////////////////////////
// void stringSave(int address, String data) {
//   EEPROM.begin(data.length() + 1); // Panjang data + 1 untuk menyimpan null-terminator
//   for (int i = 0; i < data.length(); ++i) {
//     EEPROM.write(address + i, data[i]);
//   }
//   EEPROM.write(address + data.length(), '\0'); // Menambahkan null-terminator
//   EEPROM.commit(); // Menyimpan perubahan
//   EEPROM.end(); // Selesai dengan EEPROM
// }

// // Fungsi untuk membaca string dari EEPROM
// String stringLoad(int address) {
//   EEPROM.begin(512); // Inisialisasi EEPROM
//   String data = "";
//   char character = EEPROM.read(address); // Membaca karakter pertama

//   // Jika karakter pertama adalah null-terminator, kembalikan string kosong
//   if (character == '\0') {
//     EEPROM.end(); // Selesai dengan EEPROM
//     return data;
//   }

//   // Jika tidak, lanjutkan membaca data dari EEPROM
//   int i = 0;
//   do {
//     data += character;
//     i++;
//     character = EEPROM.read(address + i);
//   } while (character != '\0');
  
//   EEPROM.end(); // Selesai dengan EEPROM
//   return data;
// }

// const char* stringToConstChar(String str) {
//   char *buffer = new char[str.length() + 1];
//   strcpy(buffer, str.c_str());
//   return buffer;
// }
