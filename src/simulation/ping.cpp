#include "ping.h"

Netdump netDump;

StreamString streamString;

//TODO - use pointers or char[] for local things
String globalSearchString;

void findIPInsideICMPRequest()
{
    const String s = globalSearchString;
    const int indexOfPingRequest = s.indexOf(F("ping request"));

    if (indexOfPingRequest == -1)
    {
        return;
    }

    int end_search_index = indexOfPingRequest;
    while (end_search_index > 0)
    {
        // looking for attacker IP only
        if (s.charAt(end_search_index) == '>')
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

    notifier.notify(F("[PING]: Ping ICMP request"));
    notifier.notifyAttackOccurred(scanResult);
}

// ARP  who has 192.168.134.138 tell 192.168.134.80
void findIpInsideArpRequest()
{
    const String s = globalSearchString;
    const String arpSearchString = F("ARP  who has");
    const String tellString = F("tell");
    int startIndex = s.indexOf(arpSearchString);

    if (startIndex == -1)
    {
        return;
    }

    startIndex = s.indexOf(tellString, startIndex);

    const int endIndex = s.indexOf('\n', startIndex + tellString.length());

    String scanResult = s.substring(startIndex + tellString.length() + 1, endIndex);

    notifier.notify(F("[PING]: Ping ARP request"));
    notifier.notifyAttackOccurred(scanResult);
}

void PingWatcher::setup()
{
    netDump.printDump(streamString, Packet::PacketDetail::CHAR,
                      [](Packet n) {
                          return (n.isICMP() || n.isARP());
                      });
}

void PingWatcher::loop()
{
    if (!streamString.isEmpty())
    {
        globalSearchString = streamString.readString();

        //Not sure if that is necessary
        if (globalSearchString.isEmpty())
        {
            Serial.println("!!!!!!!!!!!! Empty String!");
            return;
        }

        findIPInsideICMPRequest();
        findIpInsideArpRequest();
    }
}