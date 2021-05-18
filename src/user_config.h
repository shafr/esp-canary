#ifndef user_config_h
#define user_config_h


#define VERSION "1.2.1"

//===========================================================================
//============================= WIFI Configuration ==========================
//===========================================================================

// WIFI endpoint name where you would connect
#ifndef WIFI_SERVER_AP_NAME
  #define WIFI_SERVER_AP_NAME "WFT"
#endif

// WIFI endpoint password where you would connect
#ifndef WIFI_SERVER_AP_PASSWORD
  #define WIFI_SERVER_AP_PASSWORD "1234567890"
#endif

//===========================================================================
//============================= ESP HOST OBFUSCATION ========================
//===========================================================================

// ESP Server Host name. This is how it would appear on your router or if you would ping it.
// (also used for OTA)
#define HOST_NAME "ds214"

// New Mac address for your ESP device.
#define MAC "00:11:32:85:ac:16"

//===========================================================================
//============================= OTHER CONFIGURATION= ========================
//===========================================================================

//Remember to change port in platformio.ini as well
#define OTA_PORT 56056
// #define OTA_PASS "H0We8Adu0SYGFUNTt25C7yuJ"

//NTP offset in seconds- currently set to UTC +2H
#define NTP_TIME_OFFSET 7200


//===========================================================================
//============================= SIMULATION CONFIGURATION ====================
//===========================================================================

// Tomcat-server simulation. 
#define TOMCAT_ENABLED true
// Port for Tomcat simulation. 
#define TOMCAT_PORT 80

// Ping simulation. 
#define PING_ENABLED true

//===========================================================================
//============================= REPORTING-NOTIFICATIONS======================
//===========================================================================

// =========== MQTT ===========================
#define MQTT_ENABLED false
#define MQTT_HOST "192.168.1.1"
#define MQTT_TOPIC "security/canary"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESPCanary"
#define MQTT_USER "Canary"
#define MQTT_PASSWORD "NDCU74EJoh2N69GRhMfc"

// =========== EMAIL ===========================
#define EMAIL_ENABLED false
#define SMTP_HOST "smtp.google.com"
#define SMTP_PORT 465 
#define AUTHOR_EMAIL "sender@gmail.com"
#define AUTHOR_PASSWORD "sender_password"
#define EMAIL_TARGET_RECEPIENT "recepient@gmail.com"

// =========== TELEGRAM=========================
//Enable telegram notifications:
#define TELEGRAM_ENABLED false

// This value you would get from @BotFather when you create new bot.
#define TELEGRAM_BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// If the chat is a group, the chat id is negative. If it is a single person, then positive.
#define BOT_CHAT_ID -123456789

// To ensure certificate validation, WiFiClientSecure needs time updated.
//To choose correct time zone, Follow this link https://sites.google.com/a/usapiens.com/opnode/time-zones
#define CLOCK_TZ "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00"

// How ofter fetch data from telegram server
#define TELEGRAM_POLLING_TIME_MS 5000

#endif
