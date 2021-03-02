#pragma once
#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

#include <Arduino.h>

class ConsoleLogger
{
public:
    void NotifyAttackOccurred(String attackerIpAddress);
    void ResetAttackState();
    void Notify(String message);
};
#endif