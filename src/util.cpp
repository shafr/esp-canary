#include "Arduino.h"
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include "user_config.h"

void stringToIntArray(const char* str, char sep, uint8_t* macArr, int maxBytes, int base) {
    for (int i = 0; i < maxBytes; i++) {
        macArr[i] = strtoul(str, NULL, 16);  
        str = strchr(str, sep);              
        if (str == NULL || *str == '\0') {
            break;                            
        }
        str++;                                
    }
}

void obfuscateHost(){
  WiFi.hostname(HOST_NAME);

  Serial.print("[OLD] ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  uint8_t newMACAddress[6]; 
  stringToIntArray(MAC, ':', newMACAddress, 6, 16);

  wifi_set_macaddr(STATION_IF, const_cast<uint8*>(newMACAddress));
  
  Serial.print("[NEW] ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

