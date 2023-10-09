#include "infrared/infrared.h";
#include "infrared/infrared.cpp";


void setup(){
    InitInfrared();
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





void loop(){



}


