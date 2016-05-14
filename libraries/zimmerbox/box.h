#ifndef __BOX_H_
#define __BOX_H_

#include "message.h"
#include "response.h"

#define REQ_STATUS "STATUS"
#define REQ_ID "ID"
#define REQ_SET "SET"  // "SET <OUTPUT> <VALUE> --> "OK <OUTPUT> <VALUE>"
#define REQ_SEND "SEND"
#define REQ_ECHO "ECHO" // "ECHO <VALUE>" --> "OK <VALUE>"

void logMsg(const String& message);
void initializeBox();

bool isSupportedCmd(const String& cmd);
const Response handleStatusRequest();
const Response handleRequest(const String& cmd, Message& args);

#endif

