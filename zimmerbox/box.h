#ifndef __BOX_H_
#define __BOX_H_

#include "libs/message.h"

void logMsg(const String& message);
void initializeBox();
const String handleMessage(Message& msg);

#endif

