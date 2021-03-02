#include "Arduino.h"
#include "../user_config.h"

boolean messagesAvailable = false;

String notifyMessage = "";
String attackerIpAddress = "";

#if MQTT_ENABLED
#include "mqtt.h"
#endif

#if EMAIL_ENABLED
#include "email.h"
#endif

#include "consolelog.h"

ConsoleLogger consoleLog;

void initReporting()
{
#if MQTT_ENABLED
    mqttInit();
#endif

#if EMAIL_ENABLED
    emailInit();
#endif
}

void notify(String message)
{
    messagesAvailable = true;
    notifyMessage = message;
}

void notifyAttackOccurred(String attackerIp)
{
    messagesAvailable = true;
    attackerIpAddress = attackerIp;
}

void sendNotify(String message)
{
    consoleLog.Notify(message);

#if MQTT_ENABLED
    mqttNotify(message);
#endif
#if EMAIL_ENABLED
    sendMail(String("Notification").c_str(), message.c_str());
#endif
}
void sendNotifyAttackOccurred(String attackerIpAddress)
{
    consoleLog.NotifyAttackOccured(attackerIpAddress);

#if MQTT_ENABLED
    mqttNotifyAttackOccurred(attackerIpAddress);
#endif
#if EMAIL_ENABLED
    sendMail("Attack had occurred!", attackerIpAddress.c_str());
#endif
}
void resetAttackState()
{
    consoleLog.ResetAttackState();
#if MQTT_ENABLED
    mqttResetAttackState();
#endif
}

void notifyLoop()
{
    if (!messagesAvailable)
    {
        return;
    }

    if (notifyMessage.length() > 0)
    {
        sendNotify(notifyMessage);
        notifyMessage = "";
        messagesAvailable = false;
    }

    if (attackerIpAddress.length() > 0)
    {
        sendNotifyAttackOccurred(attackerIpAddress);
        attackerIpAddress = "";
        messagesAvailable = false;
    }
}