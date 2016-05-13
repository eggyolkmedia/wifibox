#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <WString.h>

class Message {
public:
	Message(const String& str);
  const String& getMessage();
	bool hasNext();
	const String nextStr();
  int nextInt();

private:
	const String& _str;
	int _pos;
};

#endif
