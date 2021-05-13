#pragma once
#ifndef _REPORTING_H_
#define _REPORTING_H_

#include "Arduino.h"
#include "../user_config.h"

class Notify
{
public:
    void notifyAttackOccurred(String attackerIpAddress);
    void notify(String message);
    void resetAttackState();
    void initReporting();
    void notifyLoop();
    void printf_P();

private:
    void sendNotify(String message);
    void sendNotifyAttackOccurred(String attackerIpAddress);
};

extern Notify notifier;

#endif