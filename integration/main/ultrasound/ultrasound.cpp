#include "ultrasound.h";
#include <Arduino.h>

void Ultrasound::Init(byte pinEcho_, byte pinTrigger_){
    pinEcho = pinEcho_;
    pinTrigger = pinTrigger_;


    pinMode(pinEcho_,INPUT);
    pinMode(pinTrigger_,OUTPUT);

    digitalWrite(pinTrigger_, LOW);    
}

float Ultrasound::GetDistance(){

    /* 1. Starts a distance measurement by sending a 10µs HIGH pulse to the TRIGGER pin */
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);
    
    /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
    long measure = pulseIn(pinEcho, HIGH, MEASURE_TIMEOUT);
    
    /* 3. Calcul la distance à partir du temps mesuré */
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