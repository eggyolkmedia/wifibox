#include "arduino.h"
#include "ir.h"

IR::IR(int pin, int delay, int lag) {
  _pin = pin;
  _delay = delay;
  _lag = lag;
}

void IR::Emit(int length, int* intervals) {
  for (int i=0; i<length; i+=2) {
    EmitPulse(intervals[i], intervals[i+1]);
  }
}

void IR::EmitPulse(long on, long off) {  
  digitalWrite(_pin, HIGH);
  cli();  // this turns off any background interrupts
  while (on > 0) {
   digitalWrite(_pin, HIGH);
   delayMicroseconds(_delay - _lag);
   digitalWrite(_pin, LOW);
   delayMicroseconds(_delay- _lag); 
   on -= (_delay * 2);
  }
  digitalWrite(_pin, LOW); 
  sei();  // this turns them back on  
  delayMicroseconds(off);
}
