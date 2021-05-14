#pragma once
#ifndef _PING_H_
#define _PING_H_
#if defined(ESP8266) && PING_ENABLED

#include "Arduino.h"
#include <Netdump.h>
#include <StreamString.h>
#include "reporting/reporting.h"

using namespace NetCapture;

class PingWatcher
{
public:
  void setup();
  void loop();
};

#endif
#endif