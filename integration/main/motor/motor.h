#include <Wire.h>
#include <Adafruit_MotorShield.h>


#ifndef Motor_h

#define Motor_h

class Motor {
    private:
        Adafruit_MotorShield shield;
        Adafruit_DCMotor *ada_motor;

        float target_speed;
        float current_speed;
        int timer;
        int ramp_timer;
        float ramp_increment; 

        void SetMotorSpeendAndDir(float speed);

    public:
        void Init(Adafruit_MotorShield adafruit_motorShield,int motor_nbr,int ramp_timer_);
        void SetSpeed(float target);
        
};

#endif
