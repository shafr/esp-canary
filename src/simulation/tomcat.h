#pragma once
#ifndef _TOMCAT_H_
#define _TOMCAT_H_

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "user_config.h"
#include "reporting/reporting.h"
#include "system/ntp.h"

class TomcatSimu
{
public:
    void Serve();
};
#endif