// ultrasound.h
#ifndef ultrasound_h
#define ultrasound_h

#include <Arduino.h>

class Ultrasound {
  private:
    int distance;
    int pinInput;
    int pinOutput;
    unsigned long MEASURE_TIMEOUT = 25000UL;
    float SOUND_SPEED = 340/1000;

    int last_mesure_time;

  public:
    void Init(int pinInput_, int pinOutput_);
    float GetDistance();
    void DebugUltrasound(String distance_mm);
};

#endif