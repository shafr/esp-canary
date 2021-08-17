#include "reporting/telegram.h"

BearSSL::WiFiClientSecure wiFiSecureClient;
BearSSL::Session   bearSslSession;
BearSSL::X509List  certificate(telegram_cert);
AsyncTelegram2 bot(wiFiSecureClient);

boolean initOK = false;

void TelegramNotifier::Init() {
  configTime(CLOCK_TZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  wiFiSecureClient.setSession(&bearSslSession);
  wiFiSecureClient.setTrustAnchors(&certificate);
  wiFiSecureClient.setBufferSizes(1024, 1024);

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
