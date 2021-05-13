#include "telegram.h"

AsyncTelegram bot;
TBMessage msgGroup;
//For cases when Telegram is not working - we should stop sending notifications there, 
//until issue is resolved (certificate, etc..)
boolean initOK = false;

void TelegramNotifier::Init()
{
    bot.setClock(CLOCK_TZ);

    bot.setUpdateTime(TELEGRAM_POLLING_TIME_MS);
    bot.setTelegramToken(TELEGRAM_BOT_TOKEN);

    Serial.println(F("\nTest Telegram connection... "));
    if (bot.begin()){
        initOK = true;
        msgGroup.chatId = BOT_CHAT_ID;
        Serial.println(F("Telegram connection is OK!"));
        notifier.notify("ESP started. \r\nIP: " + WiFi.localIP().toString() + "\r\nName " + bot.userName);
    } else{
        initOK = false;
        Serial.println(F("Telegram connection is NOK!"));
        notifier.notify(F("Cannot init Telegram notifications"));
    }
}

void TelegramNotifier::Notify(String message)
{
    if (!initOK){
        return;
    }
    bot.sendMessage(msgGroup, message);
}

void TelegramNotifier::NotifyAttackOccurred(String attackerIpAddress)
{
        if (!initOK){
        return;
    }
    bot.sendMessage(msgGroup, "Attack was performed from: " + attackerIpAddress);
}

void TelegramNotifier::ResetAttackState()
{
    TelegramNotifier::Notify(F("Reseting attack state"));
}
