#include "response.h"
#include "codes.h"

Response::Response() { }
Response::Response(const String& str) : _str(str) { }

Response Response::ok() {
  return Response(RES_OK);
}

Response Response::err(int code) {
  Response res(RES_ERR);
  res.addInt(code);
  return res;
}

String Response::toString() const {
  return _str;
}

Response& Response::addStr(const String& str) {
  _str += MSG_DELIM;
  _str += str;
  return *this;
}

Response& Response::addInt(int i) {
  _str += MSG_DELIM;
  _str += i;
  return *this;
}
