#include "reporting.h"

boolean messagesAvailable = false;

String notifyMessage = "";
String attackerIpAddress = "";

std::vector<String> messages;
std::vector<Message> attackMessages;

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
    messages.push_back(message);
}

void Notifier::NotifyAttackOccurred(Message attackMessage)
{
    attackMessages.push_back(attackMessage);
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
void Notifier::sendNotifyAttackOccurred(Message attackMessage)
{
    consoleLog.NotifyAttackOccurred(attackMessage);

#if MQTT_ENABLED
    mqttNotifier.NotifyAttackOccurred(attackMessage);
#endif
#if EMAIL_ENABLED
    emailNotifier.NotifyAttackOccurred(attackMessage);
#endif
#if TELEGRAM_ENABLED
    telegramNotifier.NotifyAttackOccurred(attackMessage);
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
    if (messages.empty() && attackMessages.empty())
    {
        return;
    }

    for (unsigned int z = 0; z < messages.size(); z++)
    {
        sendNotify(messages.at(z));
    }

    messages.clear();

    for (unsigned int z = 0; z < attackMessages.size(); z++)
    {
        sendNotifyAttackOccurred(attackMessages.at(z));
    }

    attackMessages.clear();
}