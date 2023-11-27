#include "motor.h";
#include <Arduino.h>;


void Motor::Init(Adafruit_MotorShield adafruit_motorShield,int motor_nbr,int ramp_timer_ms){
    shield = adafruit_motorShield;
    ada_motor = shield.getMotor(motor_nbr);


    current_speed = 0;
    target_speed = 0;
    start_speed = 0;

    ramp_timer = ramp_timer_ms;
    start_timer = 0;
    end_timer = 0;


}

float Motor::GetSpeed(){
    return current_speed;
}

void Motor::SetSpeed(float target){

    //adjust the current speed to the target speed with a ramp

    if(target != target_speed){
        target_speed = target;
        start_speed = current_speed;
        start_timer = millis();
        end_timer = start_timer + ramp_timer;
    }

    if(millis() < end_timer){
        float time_position = (millis() - start_timer) / (end_timer - start_timer);
        float speed_factor = GetSpeedFactor(time_position);
        current_speed = start_speed + (target_speed - start_speed) * speed_factor;
    }
    else{
        current_speed = target_speed;
    }

    SetMotorSpeendAndDir(current_speed);

}

float Motor::GetSpeedFactor(float time_position){
    
    //return the speed factor for the given time position -> f(x) = (( (r*x) + a) / sqrt(1 + ( (r*x) + a)²) + 1) / 2
    float r = 8;
    float a = -4;

    float speed_factor = (( (r*time_position) + a) / sqrt(1 + ( (r*time_position) + a)*( (r*time_position) + a)) + 1) / 2;

    return speed_factor;
}

void Motor::UrgentStop(){
    SetMotorSpeendAndDir(0);
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

int Motor::GetDirection(){
    if(current_speed < 0){
        return -1;
    }
    if(current_speed == 0){
        return 1;
    }
    if(current_speed > 0){
        return 1;
    }
}