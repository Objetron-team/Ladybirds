#include "infrared.h";
#include <Arduino.h>


void InfraredSensor::Init(int pin_){
  pinMode(pin_,INPUT);
  counter = 0;
  pin = pin_;
}

bool InfraredSensor::GetState(){
    state = digitalRead(pin);

    //Serial.write("Infra [");
    //Serial.print(pin);
    //Serial.write("] state :");

    if(state == HIGH){
        counter+= 2;
        //Serial.write("haut");

    }else{
        //Serial.write("bas");
        counter -= 1;

    }

    if(counter >= 2){
        counter = 2;
    }
    if (counter < -1){
        counter = -1;
    }

    Serial.write("\n");


  return (counter > 0);
}