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

void ConsoleLogger::NotifyAttackOccurred(String attackerIpAddress)
{
    Serial.println("[NOTIFICATION]: Attack occured from: " + attackerIpAddress);
}

void ConsoleLogger::ResetAttackState()
{
    Serial.println("Resetting attack state");
}
