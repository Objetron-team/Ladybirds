#include "motor.h";
#include <Arduino.h>;


void Motor::Init(Adafruit_MotorShield adafruit_motorShield,int motor_nbr,float max_acceleration_, float threshold_speed, float min_speed,float max_speed){
    shield = adafruit_motorShield;
    ada_motor = shield.getMotor(motor_nbr);

    this->max_acceleration = max_acceleration_;
    this->threshold_speed = threshold_speed;
    this->min_speed = min_speed;
    this->max_speed = max_speed;

    ada_motor->setSpeed(0);
    ada_motor->run(RELEASE);

    target_speed = 0;
    current_speed = 0;
}

float Motor::GetSpeed(){
    return current_speed;
}

/*
    Set the target speed of the motor
    param: target speed in % (between -100 and 100)
*/
void Motor::SetSpeed(float target){

    //Increase or decrease the current speed to reach the target speed by the max acceleration

    if(target == target_speed){
        return;
    }

    float delta_time = (millis() - last_update_time) / 1000.0;
    last_update_time = millis();

    float delta_speed = delta_time * max_acceleration;

    if(target > target_speed){
        current_speed += delta_speed;
        if(current_speed > target){
            current_speed = target;
        }
    }
    if(target < target_speed){
        current_speed -= delta_speed;
        if(current_speed < target){
            current_speed = target;
        }
    }

    if(abs(current_speed) >= abs(target_speed) && target_speed != 0){
        current_speed = target_speed;
    }

    SetMotorSpeendAndDir(current_speed);
}

void Motor::UrgentStop(){
    target_speed = 0;
    current_speed = 0;

    SetMotorSpeendAndDir(0);
}

/*
    Convert the speed in % to a value between 0 and 255 and set the motor speed and direction
    param: speed in % (between -100 and 100)
*/
void Motor::SetMotorSpeendAndDir(float speed){

    int sign = GetDirection();

    if(abs(speed) < threshold_speed){
        speed = 0;
    }

    if(abs(speed) > max_speed){
        speed = sign * max_speed;
    }

    if(abs(speed) < min_speed){
        speed = sign * min_speed;
    }

    //Convert the speed in % to a value between 0 and 255

    float value = abs(speed) * 255.0 / 100.0;

    ada_motor->setSpeed(value);

    if(speed < 0){
        ada_motor->run(BACKWARD);
    }
    if(speed == 0){
        ada_motor->run(FORWARD);
    }
    if(speed > 0){
        ada_motor->run(FORWARD);
    }
}



void Motor::SetMaxSpeed(float max_speed){
    this->max_speed = max_speed;
}


int Motor::GetDirection(){
    if(current_speed < 0){
        return -1;
    }
    if(current_speed == 0){
        return 1;
    }
    if(current_speed > 0){
        return 1;
    }
}