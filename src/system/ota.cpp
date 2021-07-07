#include "system/ota.h"

void OTA::Setup() {
  ArduinoOTA.onStart([]() { notifier.Notify(F("[OTA]: Upgrade start")); });

  ArduinoOTA.onEnd([]() { notifier.Notify(F("[OTA]: Upgrade finish")); });

  ArduinoOTA.onError([](ota_error_t error) {
    notifier.Notify(F("[OTA][ERROR]: Error during OTA Upgrade!: "));
    Serial.println(error);  // TODO(DIMI) - send error

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

void OTA::Loop() { ArduinoOTA.handle(); }
