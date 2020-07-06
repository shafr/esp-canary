#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"

#define OPENWRT_PORT 81

AsyncWebServer openwrtServer(OPENWRT_PORT);

void serveOpenWrt()
{
    //TODO headers
    openwrtServer.on("/luci", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/openwrt/luci");
    });


    openwrtServer.on("/luci", HTTP_POST, [](AsyncWebServerRequest *request) {
        String attackerIp = IPAddressToString(request->client()->getRemoteAddress());
        notifyAttackOccured(attackerIp);

        //return HTTP403 forbidden


        request->redirect("/500.html");

    });

    openwrtServer.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/html", "<h1>Not Found</h1>The requested URL /" + request->url() + " was not found on this server.");
    });

    openwrtServer.begin();
}
