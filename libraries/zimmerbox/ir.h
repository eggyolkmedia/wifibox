#ifndef __IR_H_
#define __IR_H_

class IR {
  public:
    IR(int pin, int delay, int lag);
    void emit(int length, int* command);
  private:
    int _pin;
    int _delay;
    int _lag;
    void emitPulse(long on, long off);
};

#endif
