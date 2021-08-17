#pragma once
#ifndef _TELEGRAM_H_
#define _TELEGRAM_H_

#include <Arduino.h>
#include "user_config.h"
#include <AsyncTelegram2.h>
#include "reporting/reporting.h"
#include <time.h>

#ifdef ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

class TelegramNotifier : public NotificationSender {
 public:
  void Init();
  void Notify(String message);
  void NotifyAttackOccurred(Message attackMessage);
  void ResetAttackState();
};
#endif
