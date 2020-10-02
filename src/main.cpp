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

#if TOMCAT_ENABLED
  #include "simulation/tomcat.h"
#endif

#if OPENWRT_ENABLED
  #include "simulation/openwrt.h"
#endif

#include "reporting/reporting.h"
#include "system/ntp.h"
#include "system/ota.h"
#include <ArduinoOTA.h>

void ConnectToWifi()
{
  #if WIFI_CLIENT 
    Serial.printf("Connecting to %s ", WIFI_SERVER_AP_NAME);
    WiFi.begin(WIFI_SERVER_AP_NAME, WIFI_SERVER_AP_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  #else
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WIFI_SERVER_AP_NAME, WIFI_SERVER_AP_PASSWORD);
    // IPAddress myIP = WiFi.softAPIP();
  #endif

  Serial.println("");
  Serial.println("Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin())
  {
    Serial.println("[ERROR], SPIFFS Initialize was not OK");
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();

  configureOTA();

  initReporting();

  // syncNtpTime();

  #if TOMCAT_ENABLED
    serveTomcat();
  #endif

  #if OPENWRT_ENABLED
    serveOpenWRT();
  #endif
}

void loop()
{
  ArduinoOTA.handle();
}