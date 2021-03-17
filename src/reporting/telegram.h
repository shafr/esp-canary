#pragma once
#ifndef _TELEGRAM_H_
#define _TELEGRAM_H_

#include <Arduino.h>
#include "user_config.h"

#ifdef ESP32
  #include <WiFi.h>
#endif

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


class TelegramNotifier  {
public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(String attackerIpAddress);
    void ResetAttackState();
};
#endif