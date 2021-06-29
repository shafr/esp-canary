#include "Arduino.h"
#include <AsyncMqttClient.h>

#include "user_config.h"
#include "../system/util.h"

AsyncMqttClient mqttClient;

void mqttNotify(String message){
  mqttClient.publish("/security/honeypot/info", 2, true, message.c_str());
} 

//TODO - subscribe to reset / configure commands in topic ?

void mqttNotifyAttackOccurred(String attackerIpAddress){
  mqttClient.publish("/security/honeypot/attackinprogress", 2, true, "True");
  mqttClient.publish("/security/honeypot/attackerip", 2, true, attackerIpAddress.c_str());
}

void mqttResetAttackState(){
    mqttClient.publish("/security/honeypot/attackinprogress", 2, false, "False");
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("[INFO]: Connected to MQTT.");
  Serial.print("[INFO]: Session present: ");
  Serial.println(sessionPresent);
  
  mqttResetAttackState();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("[DEBUG]: Disconnected from MQTT.");
}

void setMqttHost(){
  uint8_t mqttHost[4];
  stringToIntArray(MQTT_HOST, '.', mqttHost, 4, 10);

  Serial.printf("[INFO]: MQTT Parsed Host: %u.%u.%u.%u", mqttHost[0], mqttHost[1], mqttHost[2], mqttHost[3]);

  mqttClient.setServer(IPAddress(mqttHost), MQTT_PORT);
  mqttClient.setWill("/security/honeypot/will", 2, false);
  mqttClient.setClientId(MQTT_CLIENT_ID);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);
}

void mqttInit(){
  Serial.println("[INFO] Configuring MQTT Mmodule");
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  setMqttHost();
  
  mqttClient.connect();
  Serial.println("[INFO] Mqtt module config complete");
}
