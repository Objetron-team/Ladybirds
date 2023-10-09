
#include "infrared/infrared.h";
#include "infrared/infrared.cpp";

#include "motor/motor.h";
#include "motor/motor.cpp";

#include "ultrasound/ultrasound.h";
#include "ultrasound/ultrasound.cpp";

void setup(){
    InitInfrared();
    InitMotor();
    InitUltraSound();
}

InfraredSensor infraredSensorRight;
InfraredSensor infraredSensorCentral;
InfraredSensor infraredSensorLeft;

void InitInfrared(){
    infraredSensorRight.Init(1);  
    infraredSensorCentral.Init(2);  
    infraredSensorLeft.Init(3);  
}

Motor motorRight;
Motor motorLeft;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,1,1000);
    motorLeft.Init(AFMS,2,1000);
}

Ultrasound ultraSound;

void InitUltraSound(){
    ultraSound.Init(4,5);
}



void loop(){

    if(infraredSensorCentral.GetState()){

        motorRight.SetSpeed(50);
        motorLeft.SetSpeed(50);

        if(infraredSensorRight.GetState()){
            motorRight.SetSpeed(40);
            motorLeft.SetSpeed(60);
        }

        if(infraredSensorLeft.GetState()){
            motorRight.SetSpeed(60);
            motorLeft.SetSpeed(40);
        }


    }


}


