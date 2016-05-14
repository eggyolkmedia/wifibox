#ifndef __BOX_H_
#define __BOX_H_

#include "message.h"

#define REQ_STATUS "STATUS"
#define REQ_ID "ID"
#define REQ_SET "SET"  // "SET <OUTPUT> <VALUE> --> "OK <OUTPUT> <VALUE>"
#define REQ_SEND "SEND"
#define REQ_ECHO "ECHO" // "ECHO <VALUE>" --> "OK <VALUE>"

#define RES_OK "OK" 
#define RES_ERR "ERR"


void logMsg(const String& message);
void initializeBox();
const String handleMessage(Message& msg);

#endif

