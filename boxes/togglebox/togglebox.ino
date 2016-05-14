#include <box.h>
#include <codes.h>

#define PIN_OUT 2

void initializeBox() {
  pinMode(PIN_OUT, OUTPUT);
}

bool isSupportedCmd(const String& cmd) {
  return cmd == REQ_SET;
}
const Response handleStatusRequest() {
  return Response::ok();
}

const Response handleRequest(const String& cmd, Message& args) {
  int output = args.nextInt();
  if (output != 0) {
    return Response::err(ERR_BAD_OUTPUT).addStr("No output:").addInt(output);
  }
  int value = args.nextInt() ? HIGH : LOW;

  digitalWrite(PIN_OUT, value);
  return Response::ok();
}

