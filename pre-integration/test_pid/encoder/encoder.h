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
        int counter_back;

        long last_wheel_speed_measurement;

        long last_wheel_interrupt;

        const int encoder_resolution = 40;
        const float wheel_diameter = 0.026;
        const float wheel_circumference = wheel_diameter * PI;
        const float degrees_per_pulse = 360.0 / encoder_resolution;
        const float measurement_interval_ms = 5;

        float rotation_speeds[5];

    public:
        void Init(Motor *motor_,int pin_);

        void DebouncedCount();
        void ResetCounter();
        int GetCounter();
        float GetSpeed();
        float GetDistance();
        float GetRotationSpeed();
};

#endif
