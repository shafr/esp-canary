#pragma once
#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

#include <Arduino.h>
#include "reporting/notifier.h"

class ConsoleLogger : public NotificationSender {
 public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(Message attackMessage);
    void ResetAttackState();
};
#endif
