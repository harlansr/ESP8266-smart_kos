#include "smart_kos.h"

String HelpLoadFileString(const char * path){
  File file = SPIFFS.open("/login.html", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "";
  }

  String htmlString;
  while (file.available()) {
    htmlString += file.readString();
  }
  file.close();
  return htmlString;
}

File HelpLoadFile(const char * path){
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Gagal membuka file index.html");
    return File();
  }
//  server.streamFile(file, "text/html");
  file.close();
  return file;
}
