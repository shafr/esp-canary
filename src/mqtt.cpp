#include "Arduino.h"
#include <AsyncMqttClient.h>

#include "user_config.h"
#include "util.h"

AsyncMqttClient mqttClient;

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);
  mqttClient.publish("test/lol", 0, true, "test 1");
  Serial.println("Publishing at QoS 0");
  uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("Publishing at QoS 1, packetId: ");
  Serial.println(packetIdPub1);
  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("Publishing at QoS 2, packetId: ");
  Serial.println(packetIdPub2);
}

void onMqttDisconnect(bool sessionPresent) {
  Serial.println("Connected from MQTT.");
}

void configMqttNotifications(){
  Serial.println("Connecting to MQTT");
  mqttClient.onConnect(onMqttConnect);
//   mqttClient.onDisconnect(onMqttDisconnect);

  uint8_t mqttHost[4];
  stringToIntArray(MQTT_HOST, '.', mqttHost, 4, 10);

  Serial.printf("MQTT Parsed Host: %u.%u.%u.%u", mqttHost[0], mqttHost[1], mqttHost[2], mqttHost[3]);

  mqttClient.setServer(IPAddress(mqttHost), MQTT_PORT);
  
  mqttClient.connect();

  mqttClient.publish("/topic", 0, true, "Test");

}