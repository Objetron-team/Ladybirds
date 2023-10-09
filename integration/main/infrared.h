// LED.h
#ifndef InfraredSensor_h
#define InfraredSensor_h

#include <Arduino.h>

class InfraredSensor {
  private:
    int state;
    int pin;

  public:
    void Init(int pin_);
    bool GetState();
};

#endif