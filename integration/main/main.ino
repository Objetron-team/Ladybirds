
#include "infrared/infrared.h";
#include "infrared/infrared.cpp";

#include "motor/motor.h";
#include "motor/motor.cpp";

#include "ultrasound/ultrasound.h";
#include "ultrasound/ultrasound.cpp";

void setup(){
    Serial.begin(9600);

    InitInfrared();
    InitMotor();
    InitUltraSound();
}

InfraredSensor infraredSensorRight;
InfraredSensor infraredSensorCentral;
InfraredSensor infraredSensorLeft;

void InitInfrared(){
    infraredSensorRight.Init(4);  
    infraredSensorCentral.Init(2);  
    infraredSensorLeft.Init(3);  
}

Motor motorRight;
Motor motorLeft;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,4,2000);
    motorLeft.Init(AFMS,2,2000);

    motorRight.SetSpeed(0);
    motorLeft.SetSpeed(0);

}

Ultrasound ultraSound;

void InitUltraSound(){
    ultraSound.Init(5,6);
}

float baseSpeed = 20;
float turnFactor = 1;


void loop(){

    if(infraredSensorCentral.GetState()){

        motorRight.SetSpeed(baseSpeed);
        motorLeft.SetSpeed(-baseSpeed);

        if(infraredSensorRight.GetState()){
            motorRight.SetSpeed(baseSpeed*turnFactor);
            motorLeft.SetSpeed(-(baseSpeed * (1+turnFactor)));
        }

        if(infraredSensorLeft.GetState()){
            motorRight.SetSpeed(baseSpeed * (1+turnFactor));
            motorLeft.SetSpeed(-(baseSpeed * (turnFactor)));

        }
    }else{
      motorRight.SetSpeed(0);
      motorLeft.SetSpeed(0);
    }
  /*
  if(ultraSound.GetDistance() <= 10){
      motorRight.SetSpeed(0);
      motorLeft.SetSpeed(0);
  }*/

}


