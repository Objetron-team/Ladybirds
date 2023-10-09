// ultrasound.h
#ifndef ultrasound_h
#define ultrasound_h

#include <Arduino.h>

class Ultrasound {
  private:
    int distance;
    int pinInput;
    int pinOutput;

  public:
    void Init(int pinInput, int pinOutput);
    String GetDistance();
    void DebugUltrasound(String distance_mm)
};

#endif