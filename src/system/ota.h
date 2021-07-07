#pragma once
#ifndef _OTA_H_
#define _OTA_H_

#include <ArduinoOTA.h>

#include "reporting/reporting.h"
#include "user_config.h"

class OTA {
public:
  void Setup();
  void Loop();
};

#endif
