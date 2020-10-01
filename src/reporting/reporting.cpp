#include "Arduino.h"
#include "../user_config.h"
#include "mqtt.h"

void initReporting()
{
#if MQTT_ENABLED
    mqttInit();
#endif
}
void notify(String message)
{
#if MQTT_ENABLED
    mqttNotify(message);
#endif
}
void notifyAttackOccurred(String attackerIpAddress)
{
#if MQTT_ENABLED
    mqttNotifyAttackOccurred(attackerIpAddress);
#endif
}
void resetAttackState()
{
#if MQTT_ENABLED
    mqttResetAttackState();
#endif
}
