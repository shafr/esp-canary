#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "user_config.h"

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