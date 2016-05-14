#include "box.h"
#include "constants.h"

#define PIN_OUT 2

void initializeBox() {
  pinMode(PIN_OUT, OUTPUT);
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

