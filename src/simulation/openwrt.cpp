#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "user_config.h"
#include "reporting/reporting.h"

#ifdef ESP32
#include "SPIFFS.h"
#endif

AsyncWebServer openWrtServer(OPENWRT_PORT);

void rootRedirect(AsyncWebServerRequest *request)
{
  AsyncWebServerResponse *response = request->beginResponse(200);
  request->redirect("/cgi-bin/luci");
  request->send(response);
}

void loginRedirect(AsyncWebServerRequest *request)
{
  notifyAttackOccurred(request->client()->remoteIP().toString().c_str());

  AsyncWebServerResponse *response = request->beginResponse(403);
  request->redirect("/cgi-bin/luci/login");
}

void missingResourceRedirect(AsyncWebServerRequest *request)
{
  //THIS /en resource is not downloaded as well on real Openwrt.
  AsyncWebServerResponse *response = request->beginResponse(403);
  request->send(response);
}

void notFound(AsyncWebServerRequest *request)
{
  //TODO: Original 404 page contains URL as well. Need to match it.
  notifyAttackOccurred(request->client()->remoteIP().toString().c_str());

  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/owrt/html/404.html", "text/html");
  response->setCode(404);
  request->send(response);
}

void serveOpenWRT()
{
  openWrtServer.serveStatic("/cgi-bin/luci", SPIFFS, "/owrt/html/index.html");
  openWrtServer.serveStatic("/cgi-bin/luci/login", SPIFFS, "/owrt/html/login.html");

  openWrtServer.serveStatic("/luci-static/bootstrap/", SPIFFS, "/owrt/css/");
  openWrtServer.serveStatic("/luci-static/resources/", SPIFFS, "/owrt/js/");

  openWrtServer.on("/", HTTP_GET, rootRedirect);
  openWrtServer.on("/cgi-bin/luci", HTTP_POST, loginRedirect);
  openWrtServer.on("/cgi-bin/luci/admin/translations/en", HTTP_ANY, missingResourceRedirect);
  openWrtServer.onNotFound(notFound);

  openWrtServer.begin();
}