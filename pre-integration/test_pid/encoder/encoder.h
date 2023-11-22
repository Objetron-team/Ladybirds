#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "../motor/motor.h";



#ifndef Encoder_h

#define Encoder_h

class Encoder {
    private:
        Motor *motor;

        int pin;
        int counter;
        int last_wheel_interrupt;
        int nbr_of_holes = 20;
        float wheel_diameter = 0.026;
        float wheel_circumference = wheel_diameter * PI;

    public:
        void Init(Motor *motor_,int pin_);

        void DebouncedCount();
        int GetCounter();
        float GetSpeed();
        float GetDistance();

};

#endif
