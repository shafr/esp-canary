#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncMqttClient.h>

#include "user_config.h"

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

void stringToIntArray(const char* str, char sep, uint8_t* macArr, int maxBytes, int base) {
    for (int i = 0; i < maxBytes; i++) {
        macArr[i] = strtoul(str, NULL, 16);  
        str = strchr(str, sep);              
        if (str == NULL || *str == '\0') {
            break;                            
        }
        str++;                                
    }
}

void obfuscateHost(){
  WiFi.hostname(HOST_NAME);

  Serial.print("[OLD] ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  uint8_t newMACAddress[6]; 
  stringToIntArray(MAC, ':', newMACAddress, 6, 16);

  wifi_set_macaddr(STATION_IF, const_cast<uint8*>(newMACAddress));
  
  Serial.print("[NEW] ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
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
  Serial.begin(115200);
  Serial.println();

  obfuscateHost();
  ConnectToWifi();
  serveTomcat();
}

void loop()
{

}