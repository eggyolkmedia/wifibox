#ifndef __IR_H_
#define __IR_H_

class IR {
  public:
    IR(int pin, int delay, int lag);
    void Emit(int length, int* command);
  private:
    int _pin;
    int _delay;
    int _lag;
    void EmitPulse(long on, long off);
};

#endif
