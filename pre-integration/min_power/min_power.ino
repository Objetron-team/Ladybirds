#include "motor/motor.h";
#include "motor/motor.cpp";

Motor motorRight;
Motor motorLeft;

const int MOTOR_RIGHT_NBR = 2;
const int MOTOR_LEFT_NBR = 1;

const int time_to_get_to_speed_ms = 1;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,MOTOR_RIGHT_NBR,time_to_get_to_speed_ms);
    motorLeft.Init(AFMS ,MOTOR_LEFT_NBR ,time_to_get_to_speed_ms);

    motorRight.SetSpeed(0);
    motorLeft.SetSpeed(0);
}

void setup() {

    Serial.begin(38400);

    InitMotor();
}

float target_speed_left = 0;
float target_speed_right = 0;

void SerialControl(){

    //{side}{speed}
    //side : l = left, r = right
    //speed : -100 to 100
    if(Serial.available() > 0){
        String input = Serial.readStringUntil('\n');
        char side = input.charAt(0);
        float speed = input.substring(1).toFloat();

        if(side == 'l'){
            target_speed_left = speed;
        }else if(side == 'r'){
            target_speed_right = speed;
        }
    }

}

void loop() {

    SerialControl();

    motorRight.SetSpeed(target_speed_right);
    motorLeft.SetSpeed(target_speed_left);

}