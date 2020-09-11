#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"

#ifdef ESP32
    #include "SPIFFS.h"
#endif

#define OPENWRT_PORT 81

AsyncWebServer openwrtServer(OPENWRT_PORT);

//TODO headers

void serveOpenWrt()
{
    openwrtServer.on("/luci", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/openwrt/cgi_bin/luci");
    });

    openwrtServer.on("/luci", HTTP_POST, [](AsyncWebServerRequest *request) {
        notifyAttackOccured(request->client()->remoteIP().toString().c_str());

      AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/openwrt/cgi_bin/luci", "text/html");
      response->setCode(403);
      request->send(response);
    });

    openwrtServer.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/html", "<h1>Not Found</h1>The requested URL /" + request->url() + " was not found on this server.");
    });

    openwrtServer.begin();
}
