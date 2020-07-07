#include <ArduinoOTA.h>
#include "mqtt.h"
#include "user_config.h"

void configureOTA()
{
  ArduinoOTA.onStart([]() {
    notifyMqtt("[INFO]: Upgrade start");
  });

  ArduinoOTA.onEnd([]() {
    notifyMqtt("[INFO]: Upgrade finish");
  });

  ArduinoOTA.onError([](ota_error_t error) {
    notifyMqtt("[ERROR]: Error during OTA Upgrade!: "); //TODO - send error
    Serial.println(error);

    ESP.restart();
  });

  ArduinoOTA.setHostname(HOST_NAME);
  // ArduinoOTA.setPassword();
  ArduinoOTA.setRebootOnSuccess(true);
  ArduinoOTA.begin();
}
