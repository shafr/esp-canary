#pragma once
#ifndef _MQTT_H_
#define _MQTT_H_

void configureMQTT();
void notifyAttackOccured(String attackerIpAddress);
void resetAttackState();

#endif