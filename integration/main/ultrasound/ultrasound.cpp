#include "ultrasound.h";
#include <Arduino.h>

void Ultrasound::Init(int pinInput_, int pinOutput_){
    pinMode(pinInput_,INPUT);
    pinEcho = pinInput_;
    pinMode(pinOutput_,OUTPUT);
    pinTrigger = pinOutput_;
}

float Ultrasound::GetDistance(){
    /* 1. Starts a distance measurement by sending a 10µs HIGH pulse to the TRIGGER pin */
    digitalWrite(pinTrigger, HIGH);
    if(millis() - last_mesure_time >= 10){
      
      last_mesure_time = millis();
    }
    digitalWrite(pinTrigger, LOW);
    
    /* 2. Measures the time between sending the ultrasonic pulse and its echo (if it exists) */
    long measure = pulseIn(pinEcho, HIGH, MEASURE_TIMEOUT);
    
    /* 3. Calculating the distance from the measured time */
    float distance_mm = measure / 2.0 * SOUND_SPEED;
    
    return distance_mm;
}

void DebugUltrasound(float distance_mm){
    /* Show the result in mm, cm and m */
    Serial.print(F("Distance: "));
    Serial.print(distance_mm);
    Serial.print(F("mm ("));
    Serial.print(distance_mm / 10.0, 2);
    Serial.print(F("cm, "));
    Serial.print(distance_mm / 1000.0, 2);
    Serial.println(F("m)"));
}