#include "encoder.h";
#include <Arduino.h>;
#include "../motor/motor.h";


void Encoder::Init(Motor *motor_,int pin_){

    motor = motor_;
    pin = pin_;
    counter = 0;
    last_wheel_interrupt = 0;

    pinMode(pin, INPUT_PULLUP);
}

void Encoder::DebouncedCount(){
    if (millis() - last_wheel_interrupt > 10){

        counter += motor->GetDirection();

        last_wheel_interrupt = millis();
    }
}

float Encoder::GetSpeed(){
    return motor->GetSpeed();
}

int Encoder::GetCounter(){
    return counter;
}

float Encoder::GetDistance(){
    return (counter * wheel_circumference) / nbr_of_holes;
}