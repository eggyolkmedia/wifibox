#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "libs/message.h"
#include "constants.h"

#define COMM_INIT_DELAY 1000
#define COMM_TIMEOUT 2500
#define COMM_CONNECT_DELAY 100

#define PRINT_TO_SERIAL true
#define PIN_OUT 2

#define PORT 1
#define SSID "ssid"
#define PASS "pass"

WiFiServer server(PORT);

// TODO MOVE TO LIBRARY
void print(const String& message) {
#ifdef PRINT_TO_SERIAL
  Serial.print(message);
#endif
}

void println(const String& message) {
#ifdef PRINT_TO_SERIAL
  Serial.println(message);
#endif
}

void setup() {
#ifdef PRINT_TO_SERIAL
  Serial.begin(9600);
#endif

  delay(COMM_INIT_DELAY);
  pinMode(PIN_OUT, OUTPUT);  

  print(String("\n\nConnecting to ") + SSID);  
  WiFi.begin(SSID, PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(COMM_CONNECT_DELAY);
    print(".");
  }
  println("");
  println("WiFi connected");
  
  // Start the server
  server.begin();
  println(String("Server started at ") + WiFi.localIP().toString());
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
  println("New client");
  while(!client.available() && --timeout>0) {
    delay(1);
  }
  if (timeout <= 0) {
    println("TIMEOUT");
    client.flush();
    return;
  }
  
  // Read the first line of the request
  // TODO FIGURE OUT WHY DOESN'T WORK DIRECTLY
  String str = client.readStringUntil(0);
  Message msg(str);
  client.flush();
  println(String("Got message [") + msg.getMessage() + "]");

  const String response = handleMessage(msg);
    
  // Send the response to the client
  client.print(response);
  delay(1);
  println("Client disonnected");
}

const String handleMessage(Message& msg) {  
  const String cmd = msg.nextStr();
  if (cmd == REQ_STATUS) {
    return RES_OK;
  } else if (cmd == REQ_SET) {
    int output = msg.nextInt();
    int value = msg.nextInt() ? HIGH : LOW;

    digitalWrite(PIN_OUT, value);
    return RES_OK;
  } else {
    return String(RES_ERR) + " 1 unknown command " + cmd;
  }
}

