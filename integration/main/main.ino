
#include "infrared/infrared.h";
#include "infrared/infrared.cpp";

#include "motor/motor.h";
#include "motor/motor.cpp";

#include "ultrasound/ultrasound.h";
#include "ultrasound/ultrasound.cpp";

void setup(){
    InitInfrared();
    //InitMotor();
}


InfraredSensor infraredSensor1;
InfraredSensor infraredSensor2;
InfraredSensor infraredSensor3;

void InitInfrared(){

    const int PIN_IR_1;
    const int PIN_IR_2;
    const int PIN_IR_3;

    infraredSensor1.Init(PIN_IR_1);
    infraredSensor1.Init(PIN_IR_1);
    infraredSensor1.Init(PIN_IR_1);
}

Motor motorRight;
Motor motorLeft;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,1,1000);
    motorLeft.Init(AFMS,2,1000);
}





void loop(){



}


