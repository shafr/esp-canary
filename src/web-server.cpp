#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include "user_config.h"

void ConnectToWifi()
{
  Serial.begin(115200);
  Serial.println();

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

  if (!SPIFFS.exists("/index2.html"))
  {
    Serial.println("[ERROR], file cannot be found !!!");
  }
}

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  ConnectToWifi();

  server.serveStatic("/", SPIFFS, "/tomcat_9/").setDefaultFile("index.html");

  server
      .serveStatic("/pass", SPIFFS, "/tomcat_9/")
      .setDefaultFile("index.html")
      .setAuthentication("user", "pass");

  server.onNotFound(notFound);

  server.begin();
}

void loop()
{
}