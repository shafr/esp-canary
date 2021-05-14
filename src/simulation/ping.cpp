#if defined(ESP8266) && PING_ENABLED

#include "ping.h"

Netdump netDump;

StreamString streamString;

void findIPInsideICMPRequest()
{
    const String s = streamString.readString();

    if (s.isEmpty())
    {
        return;
    }

    const int indexOfPingRequest = s.indexOf(F("ping request"));

    if (indexOfPingRequest == -1)
    {
        return;
    }

    int end_search_index = indexOfPingRequest;
    while (end_search_index > 0)
    {
        // looking for P in ICMP
        if (s.charAt(end_search_index) == 'P')
        {
            break;
        }
        end_search_index--;
    }

    if (end_search_index == -1)
    {
        return;
    }

    String scanResult = s.substring(end_search_index + 1, indexOfPingRequest);
    Serial.println(F("Found string"));
    
    notifier.notify(F("[PING]: Ping request"));
    notifier.notifyAttackOccurred(scanResult);
}

void PingWatcher::setup()
{
    netDump.printDump(streamString, Packet::PacketDetail::CHAR,
                      [](Packet n) {
                          return (n.isICMP());
                      });
}

void PingWatcher::loop()
{
    if (!streamString.isEmpty())
    {
        findIPInsideICMPRequest();
    }
}
#endif