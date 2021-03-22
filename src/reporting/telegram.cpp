#include "telegram.h"

AsyncTelegram bot;

void TelegramNotifier::Init()
{
    bot.setClock("CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00");

    bot.setUpdateTime(2000);
    bot.setTelegramToken(TELEGRAM_BOT_TOKEN);

    Serial.print(F("\nTest Telegram connection... "));
    bot.begin() ? Serial.println(F("OK")) : Serial.println(F("NOK"));

    Serial.print(F("Bot name: @"));
    Serial.println(bot.userName);

    Notify("ESP started with IP: " + WiFi.localIP().toString());
}

void TelegramNotifier::Notify(String message)
{
    bot.sendToGroup(BOT_CHAT_ID, message);
}

void TelegramNotifier::NotifyAttackOccurred(String attackerIpAddress)
{
    bot.sendToGroup(BOT_CHAT_ID, "Attack was performed from: " + attackerIpAddress);
}

void TelegramNotifier::ResetAttackState()
{
    TelegramNotifier::Notify(F("Reseting attack state"));
}
