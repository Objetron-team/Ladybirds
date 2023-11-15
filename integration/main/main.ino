
#include "infrared/infrared.h";
#include "infrared/infrared.cpp";

#include "motor/motor.h";
#include "motor/motor.cpp";

#include "ultrasound/ultrasound.h";
#include "ultrasound/ultrasound.cpp";

/*
    Notes:

    - The infrared sensors are connected to the digital pins 2,3,4
    - The ultrasound sensor is connected to the digital pins 5,6
    - The motors are connected to the motor shield, using I2C protocol (pins A4,A5)
    
*/

const int INFRARED_RIGHT_PIN = 4;
const int INFRARED_CENTRAL_PIN = 2;
const int INFRARED_LEFT_PIN = 3;

const int MOTOR_RIGHT_NBR = 4;
const int MOTOR_LEFT_NBR = 2;

const int ULTRASOUND_TRIG_PIN = 5;
const int ULTRASOUND_ECHO_PIN = 6;

/*
-----------------------------------------------------------------------------------------------------------------------

    Main setup

-----------------------------------------------------------------------------------------------------------------------
*/

void setup(){
    Serial.begin(9600);

    InitInfrared();
    InitMotor();
    InitUltraSound();
}

/*
----------------------------------------------------------
    Infrared setup
----------------------------------------------------------
*/

InfraredSensor infraredSensorRight;
InfraredSensor infraredSensorCentral;
InfraredSensor infraredSensorLeft;

void InitInfrared(){
    infraredSensorRight.Init(INFRARED_RIGHT_PIN);  
    infraredSensorCentral.Init(INFRARED_CENTRAL_PIN);  
    infraredSensorLeft.Init(INFRARED_LEFT_PIN);  
}

/*
----------------------------------------------------------
    Motor setup
----------------------------------------------------------
*/

Motor motorRight;
Motor motorLeft;

const int time_to_get_to_speed = 2000;
const float baseSpeed = 20;
const float turnFactor = 1;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,MOTOR_RIGHT_NBR,time_to_get_to_speed);
    motorLeft.Init(AFMS ,MOTOR_LEFT_NBR ,time_to_get_to_speed);

    motorRight.SetSpeed(0);
    motorLeft.SetSpeed(0);
}

/*
----------------------------------------------------------
    Ultrasound setup
----------------------------------------------------------
*/

Ultrasound ultraSound;

void InitUltraSound(){
    ultraSound.Init(ULTRASOUND_TRIG_PIN,ULTRASOUND_ECHO_PIN);
}

/*
-----------------------------------------------------------------------------------------------------------------------

    Main loop

-----------------------------------------------------------------------------------------------------------------------
*/

void loop(){

    //Serial.write("Gauche : ");
    //Serial.print(infraredSensorLeft.GetState());
    //Serial.print("\n");

    //Serial.write("Central : ");
    Serial.print(infraredSensorCentral.GetState());
    Serial.print("\n");

    //Serial.write("Droit : ");
    //Serial.print(infraredSensorRight.GetState());
    //Serial.print("\n");


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
      motorRight.UrgentStop();
      motorLeft.UrgentStop();
  }*/

}


