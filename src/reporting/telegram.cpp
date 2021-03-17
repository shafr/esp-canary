#include "telegram.h"

// WiFiClient secured_client;
WiFiClientSecure secured_client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, secured_client);

void TelegramNotifier::Init()
{
    const uint8_t fingerprint[20] = { 0xF2, 0xAD, 0x29, 0x9C, 0x34, 0x48, 0xDD, 0x8D, 0xF4, 0xCF, 0x52, 0x32, 0xF6, 0x57, 0x33, 0x68, 0x2E, 0x81, 0xC1, 0x90} ;
    
    secured_client.setTrustAnchors(&cert);
    secured_client.setFingerprint(fingerprint);
    secured_client.setInsecure();
    
    configTime(0, 0, "cz.pool.ntp.org");
    
    Serial.println(F("[Telegram]: Setup is complete"));

    Notify("Telegram is OK!");
}

void TelegramNotifier::Notify(String message)
{
    configTime(0, 0, "cz.pool.ntp.org");
    Serial.println("Sending notify message " + message);
    bot.sendMessage(BOT_CHAT_ID, message, "");
}

void TelegramNotifier::NotifyAttackOccurred(String attackerIpAddress)
{
    configTime(0, 0, "cz.pool.ntp.org");
    Serial.println("Sending bot message " + attackerIpAddress);
    bot.sendMessage(BOT_CHAT_ID, attackerIpAddress, "");
}

void TelegramNotifier::ResetAttackState()
{
    TelegramNotifier::Notify(F("Reseting attack state"));
}
