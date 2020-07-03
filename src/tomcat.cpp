#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"

AsyncWebServer tomcatServer(TOMCAT_PORT);
int loginCount = 0;

void redirectToLoginPage(AsyncWebServerRequest *request)
{
  notifyAttackOccured(request->client()->remoteIP().toString().c_str());
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

      AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/401.html", "text/html");
      response->setCode(401);
      request->send(response);
    }

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/500.html", "text/html");
    response->setCode(500);
    request->send(response);
  });

  tomcatServer.on("/examples/", HTTP_ANY, redirectToLoginPage);

  tomcatServer.on("/manager/html", HTTP_ANY, redirectToLoginPage);

  tomcatServer.on("/manager/status", HTTP_ANY, redirectToLoginPage);

  tomcatServer.onNotFound([](AsyncWebServerRequest *request) {
    notifyAttackOccured(request->client()->remoteIP().toString().c_str());

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/404.html", "text/html");
    response->setCode(404);
    request->send(response);
  });

  tomcatServer.begin();
}