#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "message.h"
#include "response.h"
#include "box.h"
#include "config.h"
#include "codes.h"

#define COMM_INIT_DELAY 1000
#define COMM_TIMEOUT 2500
#define COMM_CONNECT_DELAY 100

WiFiServer server(PORT);

Response processRequest(const String& str);

// TODO MOVE TO LIBRARY
void logMsg(const String& message) {
#ifdef DEBUG
  Serial.print(message);
#endif
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  initializeBox();
  delay(COMM_INIT_DELAY);

  logMsg(String("\n\nConnecting to ") + SSID);  
  WiFi.begin(SSID, PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(COMM_CONNECT_DELAY);    
  }  
  logMsg("WiFi connected");
  
  // Start the server
  server.begin();
  logMsg(String("Server started at ") + WiFi.localIP().toString());
}

void loop() {
  // NETWORKING
  // TODO FIGURE OUT WHETHRE THIS IS BLOCKING
  WiFiClient client = server.available();
  if (!client) return; // TODO CONTINUE LOOPING
  
  int timeout = COMM_TIMEOUT; // TODO LESS BUSY WAIT?
  logMsg("New client");
  while(!client.available() && --timeout>0) {
    delay(1);
  }
  if (timeout <= 0) {
    logMsg("TIMEOUT");
    client.flush();
    return;
  }
  
  // GET MSG
  // TODO FIGURE OUT WHY DOESN'T WORK DIRECTLY
  String str = client.readStringUntil(0);  
  client.flush();
  logMsg(String("Got message [") + str + "]");
  
  // SEND REPLY
  client.print(processRequest(str).toString());
  delay(1);
  logMsg("Client disonnected");
}

Response processRequest(const String& str) {
  Message msg(str);
  const String cmd = msg.nextStr();
  if (cmd == REQ_STATUS) {
    return handleStatusRequest();
  } else if (isSupportedCmd(cmd)) {
    return handleRequest(cmd, msg); // One token already read
  } else {
    return Response::err(ERR_INVALID_CMD).addStr("Invalid command:").addStr(cmd);
  }
}

