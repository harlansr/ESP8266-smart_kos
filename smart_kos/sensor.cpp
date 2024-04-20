#include "smart_kos.h"

const uint16_t kIrLed = D2;
IRsend irsend(kIrLed);
uint16_t signal_on[211] = {9220, 4448,  570, 1630,  570, 1628,  572, 488,  570, 486,
                            570, 488,  570, 486,  572, 1628,  572, 1626,  548, 512,  
                            568, 490,  548, 508,  572, 486,  574, 1626,  570, 486,  
                            570, 486,  572, 1626,  572, 484,  548, 510,  570, 486,  
                            570, 486,  570, 486,  572, 1628,  544, 1652,  572, 1628,  
                            570, 488,  546, 510,  572, 486,  546, 512,  570, 488,  
                            546, 510,  546, 512,  570, 488,  546, 512,  544, 514,  
                            546, 510,  570, 486,  572, 488,  546, 1652,  572, 486,  
                            570, 488,  572, 486,  546, 512,  544, 512,  570, 488,  
                            544, 514,  568, 490,  546, 514,  566, 488,  544, 514,  
                            544, 512,  568, 488,  546, 510,  548, 510,  542, 516,  
                            546, 510,  568, 488,  546, 512,  544, 512,  544, 514,  
                            544, 514,  544, 514,  544, 512,  544, 514,  544, 512,  
                            544, 512,  544, 512,  546, 510,  572, 484,  558, 500,  
                            544, 514,  546, 512,  546, 512,  542, 514,  546, 512,  
                            544, 514,  568, 490,  544, 512,  542, 1656,  570, 488,  
                            548, 510,  542, 516,  546, 510,  544, 512,  544, 514,  
                            544, 514,  544, 512,  546, 510,  544, 516,  544, 1654,  
                            544, 514,  544, 1654,  544, 512,  546, 512,  544, 512,  
                            546, 512,  548, 510,  544, 514,  542, 514,  546, 512,  
                            544, 1676,  524, 1652,  544, 1656,  544, 1654,  544, 512,  546};
uint16_t signal_off[211] = {9236, 4452,  574, 1626,  574, 1624,  574, 486,  570, 486,  
                            568, 488,  572, 486,  574, 1626,  572, 1626,  574, 482,  
                            570, 486,  572, 486,  548, 508,  576, 1624,  572, 486,  
                            570, 486,  574, 1624,  572, 486,  574, 484,  572, 484,  
                            572, 486,  574, 484,  572, 1628,  572, 1626,  600, 1600,  
                            570, 486,  572, 486,  570, 488,  572, 486,  548, 510,  
                            572, 486,  574, 484,  570, 488,  572, 486,  572, 486,  
                            570, 488,  546, 512,  544, 512,  570, 1630,  572, 484,  
                            572, 486,  572, 486,  572, 484,  546, 512,  570, 488,  
                            544, 512,  574, 484,  548, 510,  570, 488,  546, 512,  
                            572, 486,  572, 486,  568, 488,  572, 486,  546, 512,  
                            546, 510,  544, 514,  546, 510,  570, 488,  568, 488,  
                            572, 488,  544, 512,  568, 488,  546, 512,  572, 484,  
                            570, 486,  570, 488,  546, 512,  546, 512,  546, 512,  
                            544, 512,  570, 488,  570, 488,  542, 516,  544, 514,  
                            572, 486,  546, 510,  544, 512,  546, 512,  544, 514,  
                            570, 488,  544, 512,  568, 490,  544, 512,  546, 512,  
                            546, 512,  544, 514,  544, 514,  544, 514,  544, 1654,  
                            546, 512,  544, 1654,  544, 514,  570, 486,  544, 512,  
                            544, 512,  544, 514,  568, 490,  572, 486,  544, 514,  
                            546, 1654,  568, 1630,  544, 512,  570, 1630,  544, 514,  568};


uint8_t state_on[13] = {0xC3, 0x90, 0xE0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x05, 0x78};

void RemoteStart(){
  irsend.begin();
}
void RemoteSend(String type){
  if(type == "on"){
      irsend.sendRaw(signal_on, 211, 38);
      Serial.println("AC Hidup...");
  }else if(type == "off"){
      const uint16_t rawDataSize = sizeof(signal_off) / sizeof(uint16_t);
      uint16_t data[rawDataSize];
      for (int i = 0; i < rawDataSize; i++) {
        data[i] = signal_off[i];
      }
      irsend.sendRaw(data, rawDataSize, 38);
      Serial.println("AC Mati...");
  }
}