#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "message.h"
#include "constants.h"
#include "box.h"

#define COMM_INIT_DELAY 1000
#define COMM_TIMEOUT 2500
#define COMM_CONNECT_DELAY 100

#define PRINT_TO_SERIAL true

#define PORT 1
#define SSID "ssid"
#define PASS "pass"

WiFiServer server(PORT);

// TODO MOVE TO LIBRARY
void logMsg(const String& message) {
#ifdef PRINT_TO_SERIAL
  Serial.print(message);
#endif
}

void setup() {
#ifdef PRINT_TO_SERIAL
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
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  int timeout = COMM_TIMEOUT;
  // TODO replace with less busy wait
  logMsg("New client");
  while(!client.available() && --timeout>0) {
    delay(1);
  }
  if (timeout <= 0) {
    logMsg("TIMEOUT");
    client.flush();
    return;
  }
  
  // Read the first line of the request
  // TODO FIGURE OUT WHY DOESN'T WORK DIRECTLY
  String str = client.readStringUntil(0);
  Message msg(str);
  client.flush();
  logMsg(String("Got message [") + msg.getMessage() + "]");

  const String response = handleMessage(msg);
    
  // Send the response to the client
  client.print(response);
  delay(1);
  logMsg("Client disonnected");
}

