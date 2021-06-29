#include "Arduino.h"

void consoleLogNotifyAttackOccurred(String attackerIpAddress){
    Serial.println("[NOTIFICATION]: Attack occured from: " + attackerIpAddress);
}

void consoleLogResetAttackState(){
    Serial.println("Resetting attack state");
}

void consoleLogNotify(String message){
     Serial.println("[NOTIFICATION]: " +  message);
}