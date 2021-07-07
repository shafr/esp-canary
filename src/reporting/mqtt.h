#pragma once
#ifndef _MQTT_H_
#define _MQTT_H_

#include <Arduino.h>
#include <AsyncMqttClient.h>

#include "../system/util.h"
#include "../user_config.h"
#include "reporting/notifier.h"

class MqttNotifier : public NotificationSender {
 public:
  void Init();
  void NotifyAttackOccurred(Message attackMessage);
  void ResetAttackState();
  void Notify(String message);
};
#endif
