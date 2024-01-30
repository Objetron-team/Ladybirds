#include <Arduino.h>

#ifndef ultrasound_h
#define ultrasound_h


class Ultrasound {
  private:
    byte pinEcho;
    byte pinTrigger;
    const unsigned long MEASURE_TIMEOUT = 25000UL;
    const float SOUND_SPEED = 340/1000;

    int last_mesure_time;

  public:
    void Init(byte pinEcho_, byte pinTrigger_);
    float GetDistance();
    void DebugUltrasound(String distance_mm);
};

#endif