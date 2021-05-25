#include "reporting.h"

boolean messagesAvailable = false;

String notifyMessage = "";
String attackerIpAddress = "";

#if MQTT_ENABLED
#include "mqtt.h"
MqttNotifier mqttNotifier;
#endif

#if EMAIL_ENABLED
#include "email.h"
EmailNotifier emailNotifier;
#endif

#if TELEGRAM_ENABLED
#include "telegram.h"
TelegramNotifier telegramNotifier;
#endif

#include "consolelog.h"
ConsoleLogger consoleLog;

void Notifier::Init()
{
#if MQTT_ENABLED
    mqttNotifier.Init();
#endif

#if EMAIL_ENABLED
    emailNotifier.Init();
#endif

#if TELEGRAM_ENABLED
    telegramNotifier.Init();
#endif

}

void Notifier::Notify(String message)
{
    messagesAvailable = true;
    notifyMessage = message;
}

void Notifier::NotifyAttackOccurred(String source, String feature, String attackerIp)
{
    messagesAvailable = true;
    attackerIpAddress = attackerIp;
}

void Notifier::sendNotify(String message)
{
    consoleLog.Notify(message);

#if MQTT_ENABLED
    mqttNotifier.Notify(message);
#endif
#if EMAIL_ENABLED
    emailNotifier.Notify(message);
#endif
#if TELEGRAM_ENABLED
    telegramNotifier.Notify(message);
#endif
}
void Notifier::sendNotifyAttackOccurred(String source, String feature, String attackerIp)
{
    consoleLog.NotifyAttackOccurred(source, feature, attackerIp);

#if MQTT_ENABLED
    mqttNotifier.NotifyAttackOccurred(source, feature, attackerIp);
#endif
#if EMAIL_ENABLED
    emailNotifier.NotifyAttackOccurred(source, feature, attackerIp);
#endif
#if TELEGRAM_ENABLED
    telegramNotifier.NotifyAttackOccurred(source, feature, attackerIp);
#endif
}
void Notifier::ResetAttackState()
{
    consoleLog.ResetAttackState();
#if MQTT_ENABLED
    mqttNotifier.ResetAttackState();
#endif
#if EMAIL_ENABLED
    emailNotifier.ResetAttackState();
#endif
#if TELEGRAM_ENABLED
    telegramNotifier.ResetAttackState();
#endif
}

void Notifier::notifyLoop()
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
        // sendNotifyAttackOccurred(source, feature, attackerIp);
        attackerIpAddress = "";
        messagesAvailable = false;
    }
}