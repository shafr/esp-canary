#include <NTPClient.h>
#include <WiFiUdp.h>

#include "user_config.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const String weekDays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const String months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

String getFmtDate() {
  unsigned long epochTime = timeClient.getEpochTime();
  String weekDay = weekDays[timeClient.getDay()];
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int day = ptm->tm_mday;
  int monthNum = ptm->tm_mon + 1;
  String month = months[monthNum - 1];
  int year = ptm->tm_year + 1900;
  int hour = timeClient.getHours();
  int min = timeClient.getMinutes();
  int sec = timeClient.getSeconds();

  char fullDateString[100]; // TODO - calc size
  // TODO - correct format ?
  // TODO - Use other than GMT format
  sprintf(fullDateString, "%s, %02d %s %02d %02d:%02d:%02d GMT",
          weekDay.c_str(), day, month.c_str(), year, hour, min, sec);

  return String(fullDateString);
}

void syncNtpTime() {
  Serial.println(F("[INFO] Syncing time"));
  timeClient.begin();
  timeClient.setTimeOffset(NTP_TIME_OFFSET);
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  Serial.println(F("[INFO] Current Date:"));
  Serial.println(getFmtDate());
}
