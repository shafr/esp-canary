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

#include "reporting.h"

#include "AsyncTelegram.h"


class TelegramNotifier : public NotificationSender 
{
public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(Message attackMessage);
    void ResetAttackState();
};
#endif