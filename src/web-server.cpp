#include <Arduino.h>

#ifdef ESP32
  #include <WiFi.h>
  #include "SPIFFS.h"
#endif

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif

#include "user_config.h"
#include "util.h"
#include "tomcat.h"
#include "ssh.h"
#include "mqtt.h"
#include "ntp.h"
#include "ota.h"
#include <ArduinoOTA.h>

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


void setup()
{
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();

  configureOTA();
  configureMQTT();
  syncNtpTime();

  serveTomcat();
  serveSSH();

}

void loop()
{
  ArduinoOTA.handle();
}