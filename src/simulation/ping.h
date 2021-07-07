#pragma once
#ifndef _PING_H_
#define _PING_H_

#include "Arduino.h"
#include "reporting/reporting.h"
#include <Netdump.h>
#include <StreamString.h>

using NetCapture::Netdump;
using NetCapture::Packet;

class PingWatcher {
 public:
  void setup();
  void loop();
};

#endif
