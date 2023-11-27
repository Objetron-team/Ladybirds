#include "encoder.h";
#include <Arduino.h>;
#include "../motor/motor.h";


void Encoder::Init(Motor *motor_,int pin_){

    motor = motor_;
    pin = pin_;
    counter = 0;
    last_wheel_interrupt = 0;

    last_wheel_speed_measurement = 0;
    counter_back = 0;

    for(int i = 0; i < 5; i++){
        rotation_speeds[i] = 0;
    }

    pinMode(pin, INPUT_PULLUP);
}

void Encoder::DebouncedCount(){
    if (millis() - last_wheel_interrupt > 10){

        counter += 1;

        last_wheel_interrupt = millis();
    }
}

void Encoder::ResetCounter(){
    counter = 0;
}

float Encoder::GetSpeed(){
    return motor->GetSpeed();
}

int Encoder::GetCounter(){
    return counter;
}

float Encoder::GetDistance(){
    return (counter * wheel_circumference) / encoder_resolution;
}

float Encoder::GetRotationSpeed(){

    long current_time = millis();

    if (current_time - last_wheel_speed_measurement > measurement_interval_ms){

        //shift the array
        for(int i = 4; i > 0; i--){
            rotation_speeds[i] = rotation_speeds[i-1];
        }

        //add the new measurement to the array -> degree per second
        rotation_speeds[0] = ((counter - counter_back) * motor->GetDirection()) * measurement_interval_ms * degrees_per_pulse * 10 / (current_time - last_wheel_speed_measurement);
        
        counter_back = counter;
        last_wheel_speed_measurement = current_time;
    }

    //smooth out the rotation speed by taking the average of the last 5 measurements
    float rotation_speed = 0;
    for(int i = 0; i < 5; i++){
        rotation_speed += rotation_speeds[i];
    }
    rotation_speed /= 5;

    return rotation_speed;
}
