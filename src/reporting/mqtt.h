#pragma once
#ifndef _MQTT_H_
#define _MQTT_H_

#include <Arduino.h>
#include <AsyncMqttClient.h>

#include "user_config.h"
#include "../system/util.h"
#include "notifier.h"

class MqttNotifier : public NotificationSender 
{
public:
    void Init();
    void NotifyAttackOccurred(String source, String feature, String attackerIp);
    void ResetAttackState();
    void Notify(String message);
};
#endif