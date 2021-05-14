#include "mqtt.h"

AsyncMqttClient mqttClient;

void MqttNotifier::Notify(String message)
{
  mqttClient.publish("security/canary/info", 2, true, message.c_str());
}

//TODO - subscribe to reset / configure commands in topic ?

void MqttNotifier::NotifyAttackOccurred(String attackerIpAddress)
{
  mqttClient.publish("security/canary/attackinprogress", 2, true, "True");
  mqttClient.publish("security/canary/attackerip", 2, true, attackerIpAddress.c_str());
}

void MqttNotifier::ResetAttackState()
{
  mqttClient.publish("security/canary/attackinprogress", 2, false, "False");
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println(F("[INFO]: Connected to MQTT."));
  Serial.print(F("[INFO]: Session present: "));
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println(F("[DEBUG]: Disconnected from MQTT."));
}

void setMqttHost()
{
  uint8_t mqttHost[4];
  stringToIntArray(MQTT_HOST, '.', mqttHost, 4, 10);

  Serial.printf("[INFO]: MQTT Parsed Host: %u.%u.%u.%u", mqttHost[0], mqttHost[1], mqttHost[2], mqttHost[3]);

  mqttClient.setServer(IPAddress(mqttHost), MQTT_PORT);
  mqttClient.setWill("security/canary/will", 2, false);
  mqttClient.setClientId(MQTT_CLIENT_ID);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);
}

void MqttNotifier::Init()
{
  Serial.println(F("[INFO] Configuring MQTT Mmodule"));
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  setMqttHost();

  mqttClient.connect();

  MqttNotifier::ResetAttackState();

  Serial.println(F("[INFO] Mqtt module config complete"));
}
