#include "Arduino.h"
#include "user_config.h"

#ifdef ESP32
#include <ESPmDNS.h>
#include <WiFi.h>
#include <esp_wifi.h>
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif

void stringToIntArray(const char *inString, char separator, uint8_t *resArray,
                      int structSize, int base) {
  for (int i = 0; i < structSize; i++) {
    resArray[i] = strtoul(inString, NULL, base);
    inString = strchr(inString, separator);
    if (inString == NULL || *inString == '\0') {
      break;
    }
    inString++;
  }
}

String IPAddressToString(int ip) {
  char buf[16];

  sprintf(buf, "%d.%d.%d.%d", (ip)&0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF,
          (ip >> 24) & 0xFF);

  return String(buf);
}

void obfuscateHost() {
#ifdef ESP8266
  WiFi.hostname(HOST_NAME);
#endif

#ifdef ESP32
  WiFi.setHostname(HOST_NAME);
#endif

  Serial.print(F("[OLD] ESP8266 Board MAC Address:  "));
  Serial.println(WiFi.macAddress());

  uint8_t newMACAddress[6];
  stringToIntArray(MAC, ':', newMACAddress, 6, 16);

#ifdef ESP8266
  wifi_set_macaddr(STATION_IF, const_cast<uint8 *>(newMACAddress));
#endif

#ifdef ESP32
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);
#endif

  Serial.print(F("[NEW] ESP8266 Board MAC Address:  "));
  Serial.println(WiFi.macAddress());
}
