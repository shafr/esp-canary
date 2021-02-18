#include <ArduinoOTA.h>
#include "reporting/reporting.h"
#include "user_config.h"

void configureOTA()
{
  ArduinoOTA.onStart([]() {
    notify("[INFO]: Upgrade start");
  });

  ArduinoOTA.onEnd([]() {
    notify("[INFO]: Upgrade finish");
  });

  ArduinoOTA.onError([](ota_error_t error) {
    notify("[ERROR]: Error during OTA Upgrade!: "); //TODO - send error
    Serial.println(error);

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

void LoopOta(){
  ArduinoOTA.handle();
}