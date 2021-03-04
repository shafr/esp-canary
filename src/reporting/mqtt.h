#pragma once
#ifndef _MQTT_H_
#define _MQTT_H_

#include <Arduino.h>
#include <AsyncMqttClient.h>

#include "user_config.h"
#include "../system/util.h"

class MqttNotifier
{
public:
    void Init();
    void NotifyAttackOccurred(String attackerIpAddress);
    void ResetAttackState();
    void Notify(String message);
};
#endif