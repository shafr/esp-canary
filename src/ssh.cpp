#include <Arduino.h>

#ifdef ESP32
  #include <AsyncTCP.h>
#endif

#ifdef ESP8266
  #include <ESPAsyncTCP.h>
#endif

#include "util.h"
#include "user_config.h"
#include "mqtt.h"

static void handleNewClient(void* arg, AsyncClient* client) {
  String attackerIp = client->remoteIP().toString().c_str();
  notifyAttackOccured(attackerIp);

  String reply = "SSH-2.0-OpenSSH_7.4p1 Debian-10+deb9u7";

  client->add(reply.c_str(), strlen(reply.c_str()));
  client->send();
}

void serveSSH()
{
  AsyncServer* sshServer = new AsyncServer(22);

  sshServer->onClient(&handleNewClient, sshServer);
  sshServer->begin();

}