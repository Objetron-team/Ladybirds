#include "motor.h";
#include <Arduino.h>;


void Motor::Init(Adafruit_MotorShield adafruit_motorShield,int motor_nbr,int ramp_timer_){
    shield = adafruit_motorShield;
    ada_motor = shield.getMotor(motor_nbr);

    ramp_timer = ramp_timer_;

    target_speed = 0;   //can be between -100 and 100;
    timer = 0;
}

void Motor::SetSpeed(float target){

    //detect a change in target;
    if(target != target_speed){
        timer = millis();

        float delta_speed = target - current_speed;

        ramp_increment = delta_speed / ramp_timer;
    }
    target_speed = target;

    //put the current_speed to the target after the delay to take rounding into account
    if(millis() - timer >= ramp_timer){
        current_speed = target_speed;
    }else{
        current_speed += ramp_increment;
    }

    SetMotorSpeendAndDir(current_speed);

}

void Motor::SetMotorSpeendAndDir(float speed){

    int value = map(abs(speed),0,100,0,255);

    ada_motor->setSpeed(value);

    if(speed < 0){
        ada_motor->run(BACKWARD);
    }
    if(speed == 0){
        ada_motor->run(RELEASE);
    }
    if(speed > 0){
        ada_motor->run(FORWARD);
    }
}