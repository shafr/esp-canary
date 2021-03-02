#pragma once
#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

#include <Arduino.h>
#include "notifier.h"

class ConsoleLogger : public Notifier
{
public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(String attackerIpAddress);
    void ResetAttackState();
};
#endif