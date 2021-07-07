#include <Arduino.h>

#ifdef ESP32
  #include <WiFi.h>
  #include <FS.h>
  #include <LITTLEFS.h>
  #define LittleFS LITTLEFS
#endif

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <LittleFS.h>
#endif

#include "user_config.h"
#include "system/util.h"
#include "simulation/tomcat.h"
#include "reporting/reporting.h"
#include "system/ntp.h"
#include "system/ota.h"

#if defined(ESP8266) && PING_ENABLED
#include "simulation/ping.h"
#endif

Notifier notifier;

OTA ota;

#if TOMCAT_ENABLED
  TomcatSimu tomcatSimu;
#endif

#if defined(ESP8266) && PING_ENABLED
  PingWatcher pingWatcher;
#endif

void ConnectToWifi()
{
  Serial.printf("Connecting to %s ", WIFI_SERVER_AP_NAME);
  WiFi.begin(WIFI_SERVER_AP_NAME, WIFI_SERVER_AP_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F(""));
  Serial.println(F("Connected!"));

  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());

  if (!LittleFS.begin()) {
    Serial.println(F("[ERROR], LittleFS Initialize was not OK"));
  } else {
    Serial.println(F("[INFO],  LittleFS Initialize was OK"));
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();

  ota.Setup();

  notifier.Init();

  notifier.Notify("Build version: " + String(VERSION));
  // syncNtpTime();

  #if TOMCAT_ENABLED
    tomcatSimu.Serve();
  #endif

  #if defined(ESP8266) && PING_ENABLED
    pingWatcher.setup();
  #endif
}

void loop() {
  ota.Loop();

  #if defined(ESP8266) && PING_ENABLED
    pingWatcher.loop();
  #endif

  notifier.notifyLoop();
}
