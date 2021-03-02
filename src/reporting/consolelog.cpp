#include "consolelog.h"

void ConsoleLogger::NotifyAttackOccurred(String attackerIpAddress)
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
