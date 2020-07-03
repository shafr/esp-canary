#include "Arduino.h"
#include <AsyncMqttClient.h>

#include "user_config.h"
#include "util.h"

AsyncMqttClient mqttClient;

void notifyAttackOccured(String attackerIpAddress){
  Serial.println("Attack occured from: " + attackerIpAddress);

  mqttClient.publish("/security/attack/inprogress", 2, true, "True");
  mqttClient.publish("/security/attack/ip", 2, true, attackerIpAddress.c_str());
}

void resetAttackState(){
    Serial.println("Resetting attack state");
    mqttClient.publish("/security/attack/inprogress", 2, false, "False");
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  
  resetAttackState();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
}

void setMqttHost(){
  uint8_t mqttHost[4];
  stringToIntArray(MQTT_HOST, '.', mqttHost, 4, 10);

  Serial.printf("MQTT Parsed Host: %u.%u.%u.%u", mqttHost[0], mqttHost[1], mqttHost[2], mqttHost[3]);

  mqttClient.setServer(IPAddress(mqttHost), MQTT_PORT);
}

void configureMQTT(){
  Serial.println("Connecting to MQTT");
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  setMqttHost();
  
  mqttClient.connect();
}
