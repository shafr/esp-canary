#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"

AsyncWebServer tomcatServer(TOMCAT_PORT);
int loginCount = 0;

void redirectToLoginPage(AsyncWebServerRequest *request) {
  String attackerIp = IPAddressToString(request->client()->getLocalAddress());
  notifyAttackOccured(attackerIp);

  request->redirect("/login");
}

void serveTomcat()
{
  tomcatServer.serveStatic("/", SPIFFS, "/tomcat_9/").setDefaultFile("index.html");

  tomcatServer.on("/login", HTTP_ANY, [](AsyncWebServerRequest *request) {
    if (!request->authenticate("tomcat", "tomcat"))
    {
      if (loginCount < 2)
      {
        loginCount++;
        return request->requestAuthentication();
      }

      loginCount = 0;
      request->redirect("/401.html");
    }

    request->redirect("/500.html");
  });

  tomcatServer.on("/examples/", HTTP_ANY, redirectToLoginPage);

  tomcatServer.on("/manager/html", HTTP_ANY, redirectToLoginPage);

  tomcatServer.on("/manager/status", HTTP_ANY, redirectToLoginPage);

  tomcatServer.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect("/404.html");
  });


  tomcatServer.begin();
}