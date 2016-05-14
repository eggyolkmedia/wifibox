#include <box.h>

void initializeBox() { }

const String handleMessage(Message& msg) {  
  const String cmd = msg.nextStr();
  if (cmd == REQ_STATUS) {
    return RES_OK;
  } else if (cmd == REQ_ECHO) {
    const String response = msg.nextStr();
    return String(RES_OK) + " " + response;
  }  
}

