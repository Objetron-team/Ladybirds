// LED.h
#ifndef InfraredSensor_h
#define InfraredSensor_h

class InfraredSensor {
  private:
    int state;
    int pin;
    int counter;

  public:
    void Init(int pin_);
    bool GetState();
};

#endif