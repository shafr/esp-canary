#include "consolelog.h"

#define NOTIFICATION_PREFIX "[NOTIFICATION]: "

void ConsoleLogger::Init()
{
    Serial.println("[NOTIFICATION]: Console logger INIT");
}

void ConsoleLogger::Notify(String message)
{
    Serial.println("[NOTIFICATION]: " + message);
}

void ConsoleLogger::NotifyAttackOccurred(String source, String feature, String attackerIp)
{
    Serial.println("[NOTIFICATION]: Attack occured from: " + attackerIp);
}

void ConsoleLogger::ResetAttackState()
{
    Serial.println("Resetting attack state");
}
