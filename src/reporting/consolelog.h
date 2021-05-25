#pragma once
#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

#include <Arduino.h>
#include "notifier.h"

class ConsoleLogger : public NotificationSender
{
public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(String source, String feature, String attackerIp);
    void ResetAttackState();
};
#endif