#define MSG_DELIM ' '

#include "message.h"

Message::Message(const String& str) : _str(str), _pos(0) {}

const String& Message::getMessage() {
  return _str;
}

bool Message::hasNext() {
  return _pos != -1;
}

const String Message::nextStr() {
	int nextPos = _str.indexOf(MSG_DELIM, _pos);
	String token;
	if (nextPos==-1) {
		token = _str.substring(_pos);
	} else {
		token = _str.substring(_pos, nextPos);
	}
	_pos = nextPos;

  // Advance to next starting pos (or -1)
  while (_str[_pos] == MSG_DELIM && _pos<_str.length()) ++_pos;
  if (_pos == _str.length()) _pos = -1;
	return token;
}

int Message::nextInt() {
  return nextStr().toInt();
}


