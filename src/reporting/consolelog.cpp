#include "consolelog.h"

void ConsoleLogger::NotifyAttackOccured(String attackerIpAddress)
{
    Serial.println("[NOTIFICATION]: Attack occured from: " + attackerIpAddress);
}

void ConsoleLogger::ResetAttackState()
{
    Serial.println("Resetting attack state");
}

void ConsoleLogger::Notify(String message)
{
    Serial.println("[NOTIFICATION]: " + message);
}
