#include "ultrasound.h";
#include <Arduino.h>

void Ultrasound::Init(int pinInput, int pinOutput){
    pinMode(pinInput,INPUT);
    pinIP = pinInput;
    pinMode(pinOutput,OUTPUT);
    pinOP = pinOutput;
}

String Ultrasound::GetDistance(){
  /* 1. Starts a distance measurement by sending a 10µs HIGH pulse to the TRIGGER pin */
    digitalWrite(TRIGGER_PIN, HIGH);
    if(millis() - wheel_last_interrupt >= 10){
      counter++;
      wheel_last_interrupt = millis();
    }
    digitalWrite(TRIGGER_PIN, LOW);
    
    /* 2. Measures the time between sending the ultrasonic pulse and its echo (if it exists) */
    long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
    
    /* 3. Calculating the distance from the measured time */
    float distance_mm = measure / 2.0 * SOUND_SPEED;
    
    return distance_mm;
}

void DebugUltrasound(String distance_mm){
    /* Show the result in mm, cm and m */
    Serial.print(F("Distance: "));
    Serial.print(distance_mm);
    Serial.print(F("mm ("));
    Serial.print(distance_mm / 10.0, 2);
    Serial.print(F("cm, "));
    Serial.print(distance_mm / 1000.0, 2);
    Serial.println(F("m)"));
}