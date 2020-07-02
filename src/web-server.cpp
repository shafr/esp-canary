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
}

AsyncWebServer server(TOMCAT_PORT);
int loginCount = 0;

void serveTomcat()
{
  server.serveStatic("/", SPIFFS, "/tomcat_9/").setDefaultFile("index.html");

  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!request->authenticate("tomcat", "tomcat"))
    {
      if (loginCount < 2)
      {
        loginCount++;
        return request->requestAuthentication();
      }

      loginCount=0;
      request->redirect("/401.html");
    }

    //TODO - ups, someone is here!

    request->redirect("/500.html");
  });

  server.on("/examples/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("/login");
  });

  server.on("/manager/html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("/login");
  });

  server.on("/manager/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("/login");
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect("/404.html");
  });

  server.begin();
}

void setup()
{
  ConnectToWifi();
  serveTomcat();
}

void loop() {}