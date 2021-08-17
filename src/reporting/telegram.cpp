#include "reporting/telegram.h"

#ifdef ESP8266
BearSSL::WiFiClientSecure wiFiSecureClient;
BearSSL::Session   bearSslSession;
BearSSL::X509List  certificate(telegram_cert);
#endif

// Using SSL=true get's flash memory to 103%
#define USE_CLIENTSSL false  

#ifdef ESP32
  #if USE_CLIENTSSL
    #include <SSLClient.h>  
    #include "tg_certificate.h"
    WiFiClient base_client;
    SSLClient wiFiSecureClient(base_client, TAs, (size_t)TAs_NUM, A0, 1, SSLClient::SSL_ERROR);
  #else
    #include <WiFiClientSecure.h>
    WiFiClientSecure wiFiSecureClient;  
  #endif
#endif


AsyncTelegram2 bot(wiFiSecureClient);
boolean initOK = false;

void TelegramNotifier::Init() {
#ifdef ESP8266
  configTime(CLOCK_TZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  wiFiSecureClient.setSession(&bearSslSession);
  wiFiSecureClient.setTrustAnchors(&certificate);
  wiFiSecureClient.setBufferSizes(1024, 1024);
#endif  

#ifdef ESP32
configTzTime(CLOCK_TZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  #if !USE_CLIENTSSL
    wiFiSecureClient.setCACert(telegram_cert);
  #endif
#endif
  bot.setUpdateTime(TELEGRAM_POLLING_TIME_MS);
  bot.setTelegramToken(TELEGRAM_BOT_TOKEN);

  Serial.println(F("\nTest Telegram connection... "));
  if (bot.begin()) {
    initOK = true;
    Serial.println(F("Telegram connection is OK!"));
    notifier.Notify("ESP started. \r\nIP: " + WiFi.localIP().toString() +
                    "\r\nName " + bot.getBotName());
  } else {
    initOK = false;
    Serial.println(F("Telegram connection is NOK!"));
    notifier.Notify(F("Cannot init Telegram notifications"));
  }
}

void TelegramNotifier::Notify(String message) {
  if (!initOK) {
    return;
  }
  bot.sendTo(BOT_CHAT_ID, message);
}

void TelegramNotifier::NotifyAttackOccurred(Message attackMessage) {
  if (!initOK) {
    return;
  }

  String message = "[ " + attackMessage.source + " ] " + "[ " +
                   attackMessage.feature + " ] " + attackMessage.attackerIp;
  bot.sendTo(BOT_CHAT_ID, message);
}

void TelegramNotifier::ResetAttackState() {
  TelegramNotifier::Notify(F("Reseting attack state"));
}
