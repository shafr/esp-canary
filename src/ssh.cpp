#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include "util.h"
#include "user_config.h"
#include "mqtt.h"

static void handleNewClient(void* arg, AsyncClient* client) {
	Serial.printf("\n new client has been connected to server, ip: %s", client->remoteIP().toString().c_str());

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