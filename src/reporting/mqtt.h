#pragma once
#ifndef _MQTT_H_
#define _MQTT_H_

void mqttInit();
void mqttNotifyAttackOccurred(String attackerIpAddress);
void mqttResetAttackState();
void mqttNotify(String message);

#endif