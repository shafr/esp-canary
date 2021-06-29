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

void ConnectToWifi()
{
  Serial.printf("Connecting to %s ", WIFI_SERVER_AP_NAME);
  WiFi.begin(WIFI_SERVER_AP_NAME, WIFI_SERVER_AP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin())
  {
    Serial.println("[ERROR], SPIFFS Initialize was not OK");
  }
}

int period = 1000;
unsigned long time_now = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();

  configureOTA();

  initReporting();

  // syncNtpTime();

  #ifdef TOMCAT_PORT
    serveTomcat();
  #endif

  time_now = millis();
}

void loop()
{
  LoopOTA();
  notifyLoop();

    if (millis() < time_now + period)
  {
    return;
  }

  time_now = millis();

  static uint32_t myfree;
  static uint16_t mymax;
  static uint8_t myfrag;
  ESP.getHeapStats(&myfree, &mymax, &myfrag);

  Serial.printf("(%i) -> free: %5d - max: %5d - frag: %3d%% <- \n", millis(), myfree, mymax, myfrag);
}