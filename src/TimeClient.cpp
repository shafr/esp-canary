#include <NTPClient.h>
#include <WiFiUdp.h>
#include "user_config.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void syncNtpTime()
{
  timeClient.begin();
  timeClient.setTimeOffset(NTP_TIME_OFFSET);
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }
}