#include "infrared.h";
#include <Arduino.h>


void InfraredSensor::Init(int pin_){
  pinMode(pin_,INPUT);
  counter = 0;
  pin = pin_;

  a = 0.5;

}

bool InfraredSensor::GetState(){
    state = digitalRead(pin);

    average = a * state + (1 - a) * average;


  return (average > 0.5);
}