#ifndef __RESPONSE_H_
#define __RESPONSE_H_

#include <WString.h>

class Response {
public:
  Response();
  Response(const String& str);

  static Response ok();
  static Response err(int code);

  String toString() const;
  Response& addStr(const String& str);
  Response& addInt(int i);

private:
  String _str;
};

#endif
