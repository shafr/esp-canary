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

void ConsoleLogger::NotifyAttackOccurred(Message attackMessage)
{
    Serial.printf("[NOTIFICATION] %s - %s from IP %s", 
    attackMessage.source.c_str(), 
    attackMessage.feature.c_str(), 
    attackMessage.attackerIp.c_str());
}

void ConsoleLogger::ResetAttackState()
{
    Serial.println("Resetting attack state");
}
