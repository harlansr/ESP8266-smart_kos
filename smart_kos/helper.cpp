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
