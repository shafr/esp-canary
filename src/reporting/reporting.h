#pragma once
#ifndef _REPORTING_H_
#define _REPORTING_H_

#include "Arduino.h"
#include "notifier.h"
#include "../user_config.h"

class Notifier : public NotificationSender
{
public:
    void Init();
    void Notify(String message);
    void NotifyAttackOccurred(String source, String feature, String attackerIp);
    void ResetAttackState();
    void notifyLoop();
    void printf_P();

private:
    void sendNotify(String message);
    void sendNotifyAttackOccurred(String source, String feature, String attackerIp);
};

extern Notifier notifier;

#endif