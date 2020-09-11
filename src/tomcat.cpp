#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"
#include "ntp.h"

#ifdef ESP32
  #include "SPIFFS.h"
#endif

AsyncWebServer tomcatServer(TOMCAT_PORT);
int loginCount = 0;

void handleAuth(AsyncWebServerRequest *request)
{
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
      return;
    }

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/500.html", "text/html");
    response->setCode(500);
    request->send(response);
}

void redirectToLoginPage(AsyncWebServerRequest *request)
{
  notifyAttackOccured(request->client()->remoteIP().toString().c_str());
  request->redirect("/");
}

void serveTomcat()
{
  tomcatServer.serveStatic("/", SPIFFS, "/tomcat_9/").setDefaultFile("index.html");

  tomcatServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/index.html", "text/html");
      response->setCode(200);
      request->send(response);
  });

  tomcatServer.on("/", HTTP_POST, handleAuth);

  tomcatServer.on("/", HTTP_OPTIONS, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(200);
    response->addHeader("Allow", "GET, HEAD, POST, OPTIONS");
    response->setContentLength(0);
    
    response->addHeader("Date", getFmtDate());

    request->send(response);
  });

  tomcatServer.on("/examples/", HTTP_ANY, handleAuth);

  tomcatServer.on("/manager/html", HTTP_ANY, handleAuth);

  tomcatServer.on("/manager/status", HTTP_ANY, handleAuth);

  tomcatServer.onNotFound([](AsyncWebServerRequest *request) {
    notifyAttackOccured(request->client()->remoteIP().toString().c_str());

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/tomcat_9/404.html", "text/html");
    response->setCode(404);
    request->send(response);
  });

  tomcatServer.begin();
}