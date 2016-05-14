#include <box.h>
#include <response.h>

bool isSupportedCmd(const String& cmd) {
  return cmd == REQ_ECHO;
}
const Response handleStatusRequest() {
  return Response::ok();
}

void initializeBox() { }

const Response handleRequest(const String& cmd, Message& args) {
  return Response::ok().addStr(args.nextStr());
}

