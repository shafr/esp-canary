#include <Arduino.h>

#ifdef ESP32
  #include <WiFi.h>
  #include "SPIFFS.h"
#endif

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif

#include "user_config.h"
#include "system/util.h"
#include "simulation/tomcat.h"
#include "reporting/reporting.h"
#include "system/ntp.h"

#include "system/ota.h"
OTA ota;

#if TOMCAT_ENABLED
  TomcatSimu tomcatSimu;
#endif

void ConnectToWifi()
{
  Serial.printf("Connecting to %s ", WIFI_SERVER_AP_NAME);
  WiFi.begin(WIFI_SERVER_AP_NAME, WIFI_SERVER_AP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F(""));
  Serial.println(F("Connected!"));

  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin())
  {
    Serial.println(F("[ERROR], SPIFFS Initialize was not OK"));
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();

  ota.Setup();

  initReporting();

  // syncNtpTime();

  #if TOMCAT_ENABLED
    tomcatSimu.Serve();
  #endif

}

void loop()
{
  ota.Loop();
  notifyLoop();
}