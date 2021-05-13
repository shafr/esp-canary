#include "ota.h"

void OTA::Setup()
{
  ArduinoOTA.onStart([]() {
    notifier.notify(F("[INFO]: Upgrade start"));
  });

  ArduinoOTA.onEnd([]() {
    notifier.notify(F("[INFO]: Upgrade finish"));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    notifier.notify(F("[ERROR]: Error during OTA Upgrade!: ")); 
    Serial.println(error); //TODO - send error

    ESP.restart();
  });

  ArduinoOTA.setHostname(HOST_NAME);
  
  #ifdef OTA_PORT
    ArduinoOTA.setPort(OTA_PORT);
  #endif
  
  // #ifdef OTA_PASS 
  //   ArduinoOTA.setPassword(OTA_PASS);
  // #endif
  
  ArduinoOTA.setRebootOnSuccess(true);
  ArduinoOTA.begin();
}

void OTA::Loop(){
  ArduinoOTA.handle();
}