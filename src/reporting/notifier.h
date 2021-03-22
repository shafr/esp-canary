#include "Arduino.h"

class Notifier {
public:
   virtual void Init();
   virtual void Notify(String message);
   virtual void NotifyAttackOccurred(String attackerIpAddress);
   virtual void ResetAttackState();
};