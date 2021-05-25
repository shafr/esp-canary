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

    String attackerIP = s.substring(end_search_index + 1, indexOfPingRequest);

    Message m;
    m.source = F("PING");
    m.feature = F("ICMP");
    m.attackerIp = attackerIP;

    notifier.NotifyAttackOccurred(m);
}

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

    const String attackerIP = s.substring(startIndex + tellString.length() + 1, endIndex-1);

    //Ignoring requests from Router
    if (attackerIP.equals(WiFi.gatewayIP().toString()))
    {
        return;
    }

    //Each ARP <someone> -> <this> request is followed by <this> -> <someone> request  
    if (attackerIP.equals(WiFi.localIP().toString()))
    {
        return;
    }

    #if defined(MQTT_HOST)
    if (attackerIP.equals(String(MQTT_HOST)))
    {
        return;
    } 
    #endif

    Message m;
    m.source = F("PING");
    m.feature = F("ARP");
    m.attackerIp = attackerIP;
    notifier.NotifyAttackOccurred(m);
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

        findIPInsideICMPRequest();
        findIpInsideArpRequest();
    }
}