#include "smart_kos.h"
IPAddress host_local_IP(192,168,1,1);
IPAddress host_subnet(255,255,255,0);
IPAddress host_gateway(192,168,1,1);

int PIN_INDICATOR = D0;
int PIN_LED = D1;
const char *host_ssid = "Secret Wifi";
const char *host_password = 0; 

void WifiScan(){
  Serial.println("-------------------------------------");
  Serial.println("scan start");
  Serial.println("-------------------------------------");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("-------------------------------------");
}

bool WifiConnect(const char* a_ssid, const char* a_password){
  // WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  // delay(1000);
  // WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(a_ssid, a_password);
  delay(100);

  int count = 0;
  while (WiFi.status() == WL_IDLE_STATUS) {
    digitalWrite(PIN_INDICATOR, LOW);
    delay(500);
    digitalWrite(PIN_INDICATOR, HIGH);
    delay(500);
    Serial.print(".");
    count++;
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  return WiFi.status() == WL_CONNECTED;
}

void WifiHosted(){
  WiFi.softAPConfig(host_local_IP, host_gateway, host_subnet);
  WiFi.softAP(host_ssid, host_password);       //Memulai membuat acces point
  Serial.print("Access Point \"");
  Serial.print(host_ssid);
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP()); 
}