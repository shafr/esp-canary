#pragma once
#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include "Arduino.h"

struct Message {
  String source;
  String feature;
  String attackerIp;
};

class NotificationSender {
 public:
  virtual void Init();
  virtual void Notify(String message);
  virtual void NotifyAttackOccurred(Message attackMessage);
  virtual void ResetAttackState();
};

#endif
