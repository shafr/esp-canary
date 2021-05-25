#include "mqtt.h"
const char* strState;
AsyncMqttClient mqttClient;

void MqttNotifier::Notify(String message)
{
  mqttClient.publish("security/canary/info", 2, true, message.c_str());
}

//TODO - subscribe to reset / configure commands in topic ?

void setAttackState(bool state)
{
  strState = "False";
  if (state) 
  {
    strState = "True";
  }
  mqttClient.publish("security/canary/attackinprogress", 2, state, strState);
}

void MqttNotifier::NotifyAttackOccurred(String source, String feature, String attackerIp)
{
  setAttackState(true);  
  mqttClient.publish("security/canary/attackerip", 2, true, attackerIp.c_str());
}

void MqttNotifier::ResetAttackState()
{
  setAttackState(false);
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println(F("[INFO]: Connected to MQTT."));
  Serial.print(F("[INFO]: Session present: "));
  Serial.println(sessionPresent);
  //Reset the status
  setAttackState(false);
  Serial.print(F("[INFO]: MQTT attack status Reset"));
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println(F("[DEBUG]: Disconnected from MQTT."));
}

void setMqttHost()
{
  uint8_t mqttHost[4];
  stringToIntArray(MQTT_HOST, '.', mqttHost, 4, 10);

  Serial.printf("[INFO]: MQTT Parsed Host: %u.%u.%u.%u \r\n", mqttHost[0], mqttHost[1], mqttHost[2], mqttHost[3]);

  mqttClient.setServer(IPAddress(mqttHost), MQTT_PORT);
  mqttClient.setWill("security/canary/will", 2, false);
  mqttClient.setClientId(MQTT_CLIENT_ID);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);
  Serial.println("[INFO]: MQTT Host Set");
}

void MqttNotifier::Init()
{
  Serial.println(F("[INFO] Configuring MQTT Mmodule"));
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  setMqttHost();

  mqttClient.connect();

  Serial.println(F("[INFO] Mqtt module config complete"));
}
