#pragma once
#ifndef _REPORTING_H_
#define _REPORTING_H_

#include "Arduino.h"
#include <vector>

#include "../user_config.h"
#include "reporting/notifier.h"

class Notifier : public NotificationSender {
 public:
  void Init();
  void Notify(String message);
  void NotifyAttackOccurred(Message attackMessage);
  void ResetAttackState();
  void notifyLoop();
  void printf_P();

 private:
  void sendNotify(String message);
  void sendNotifyAttackOccurred(Message attackMessage);
};

extern Notifier notifier;

#endif
