#include "tomcat.h"

AsyncWebServer tomcatServer(TOMCAT_PORT);
int loginCount = 0;

#define TEXT_HTML "text/html"

void handleAuth(AsyncWebServerRequest *request)
{
  if (!request->authenticate("tomcat", "tomcat"))
  {
    if (loginCount < 2)
    {
      loginCount++;
      return request->requestAuthentication();
    }

    loginCount = 0;

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, F("/tomcat_9/401.html"), TEXT_HTML);
    response->setCode(401);
    request->send(response);
    return;
  }

  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, F("/tomcat_9/500.html"), TEXT_HTML);
  response->setCode(500);
  request->send(response);
}

void redirectToLoginPage(AsyncWebServerRequest *request)
{
  notifyAttackOccurred(request->client()->remoteIP().toString().c_str());
  request->redirect(F("/"));
}

void handleOptionsRequest(AsyncWebServerRequest *request)
{
  AsyncWebServerResponse *response = request->beginResponse(200);
  response->addHeader(F("Allow"), F("GET, HEAD, POST, OPTIONS"));
  response->setContentLength(0);

  response->addHeader(F("Date"), getFmtDate());

  request->send(response);
}

void handle404Request(AsyncWebServerRequest *request)
{
  notifyAttackOccurred(request->client()->remoteIP().toString().c_str());

  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, F("/tomcat_9/404.html"), TEXT_HTML);
  response->setCode(404);
  request->send(response);
}

void handleRootRequest(AsyncWebServerRequest *request)
{
  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, F("/tomcat_9/index.html"), TEXT_HTML);
  response->setCode(200);
  request->send(response);
}

void TomcatSimu::Serve()
{
  //TODO - check what is their default .setCacheControl("max-age=31536000");
  tomcatServer.serveStatic("/", SPIFFS, "/tomcat_9/").setDefaultFile("index.html");

  tomcatServer.on("/", HTTP_POST, handleAuth);

  tomcatServer.on("/examples/", HTTP_ANY, handleAuth);

  tomcatServer.on("/manager/html", HTTP_ANY, handleAuth);

  tomcatServer.on("/manager/status", HTTP_ANY, handleAuth);

  tomcatServer.on("/", HTTP_GET, handleRootRequest);

  tomcatServer.on("/", HTTP_OPTIONS, handleOptionsRequest);

  tomcatServer.onNotFound(handle404Request);

  tomcatServer.begin();
}