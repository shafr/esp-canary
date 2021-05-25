#pragma once
#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include "Arduino.h"

class NotificationSender {
public:
   virtual void Init();
   virtual void Notify(String message);
   virtual void NotifyAttackOccurred(String source, String feature, String attackerIp);
   virtual void ResetAttackState();
};


#endif