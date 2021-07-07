#pragma once
#ifndef _TOMCAT_H_
#define _TOMCAT_H_

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "user_config.h"
#include "reporting/reporting.h"
#include "system/ntp.h"

#ifdef ESP8266
    #include <FS.h>
    #include <LittleFS.h>
#endif

#ifdef ESP32
    #include <FS.h>
    // #define SPIFFS LITTLEFS
    #include <LITTLEFS.h>
    #define LittleFS LITTLEFS
#endif

class TomcatSimu {
 public:
  void Serve();
};
#endif
