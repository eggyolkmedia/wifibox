#include <box.h>

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
    if (output != 0) {
      return String(RES_ERR) + " 20 No such output [" + output + "]";
    }
    int value = msg.nextInt() ? HIGH : LOW;

    digitalWrite(PIN_OUT, value);
    return RES_OK;
  } else {
    return String(RES_ERR) + " 10 No such command [" + cmd + "]";
  }
}

