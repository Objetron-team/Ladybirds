#include "infrared.h";
#include <Arduino.h>


void InfraredSensor::Init(int pin_){
  pinMode(pin_,INPUT);
  pin = pin_;
}

bool InfraredSensor::GetState(){
  state = digitalRead(pin);
  return (state == HIGH);
}