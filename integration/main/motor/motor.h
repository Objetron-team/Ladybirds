#include <Wire.h>
#include <Adafruit_MotorShield.h>


#ifndef Motor_h

#define Motor_h

class Motor {
    private:
        Adafruit_MotorShield shield;
        Adafruit_DCMotor *ada_motor;

        float target_speed;
        float start_speed;
        float current_speed;

        int ramp_timer;
        float start_timer;
        float end_timer;


        void SetMotorSpeendAndDir(float speed);

        float GetSpeedFactor(float time_position);

    public:
        void Init(Adafruit_MotorShield adafruit_motorShield,int motor_nbr,int ramp_timer_);
        void SetSpeed(float target);
        void UrgentStop();
};

#endif
