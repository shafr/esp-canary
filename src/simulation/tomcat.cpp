#include "tomcat.h"

AsyncWebServer tomcatServer(TOMCAT_PORT);
int loginCount = 0;

#define TEXT_HTML "text/html"

void tomcatAttackNotify(String feature, AsyncWebServerRequest *request){
  Message m;
  m.source = F("TOMCAT");
  m.feature = feature;
  m.attackerIp = request->client()->remoteIP().toString().c_str();
  notifier.NotifyAttackOccurred(m);
}

void handleAuth(AsyncWebServerRequest *request)
{
  tomcatAttackNotify(F("Handle Auth"), request);

  if (!request->authenticate("tomcat", "tomcat"))
  {
    if (loginCount < 2)
    {
      loginCount++;
      return request->requestAuthentication();
    }

    loginCount = 0;

    AsyncWebServerResponse *response = request->beginResponse(LittleFS, F("/tomcat_9/401.html"), TEXT_HTML);
    response->setCode(401);
    request->send(response);
    return;
  }

  AsyncWebServerResponse *response = request->beginResponse(LittleFS, F("/tomcat_9/500.html"), TEXT_HTML);
  response->setCode(500);
  request->send(response);
}

void redirectToLoginPage(AsyncWebServerRequest *request)
{
  tomcatAttackNotify(F("Redirect login"), request);
  request->redirect(F("/"));
}

void handleOptionsRequest(AsyncWebServerRequest *request)
{
  tomcatAttackNotify(F("Options Request"), request);

  AsyncWebServerResponse *response = request->beginResponse(200);
  response->addHeader(F("Allow"), F("GET, HEAD, POST, OPTIONS"));
  response->setContentLength(0);

  response->addHeader(F("Date"), getFmtDate());
  request->send(response);
}

void handle404Request(AsyncWebServerRequest *request)
{
  tomcatAttackNotify(F("404"), request);

  AsyncWebServerResponse *response = request->beginResponse(LittleFS, F("/tomcat_9/404.html"), TEXT_HTML);
  response->setCode(404);
  request->send(response);
}

void handleRootRequest(AsyncWebServerRequest *request)
{
  tomcatAttackNotify(F("/ request"), request);

  AsyncWebServerResponse *response = request->beginResponse(LittleFS, F("/tomcat_9/index.html"), TEXT_HTML);
  response->setCode(200);
  request->send(response);
}

void TomcatSimu::Serve()
{
  //TODO - check what is their default .setCacheControl("max-age=31536000");
  tomcatServer.serveStatic("/", LittleFS, "/tomcat_9/");

  tomcatServer.on("/", HTTP_GET, handleRootRequest);
  tomcatServer.on("/", HTTP_POST, handleAuth);
  tomcatServer.on("/", HTTP_OPTIONS, handleOptionsRequest);

  tomcatServer.on("/examples/", HTTP_ANY, handleAuth);
  tomcatServer.on("/manager/html", HTTP_ANY, handleAuth);
  tomcatServer.on("/manager/status", HTTP_ANY, handleAuth);
  tomcatServer.on("/host-manager/html", HTTP_ANY, handleAuth);

  tomcatServer.onNotFound(handle404Request);

  tomcatServer.begin();
}