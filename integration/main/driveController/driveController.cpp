#include "driveController.h";
#include "../motor/motor.h";
#include "../pid/pid.h";
#include "../encoder/encoder.h";


void DriveController::Init(Motor *motor_left, Motor *motor_right, Encoder *encoder_left, Encoder *encoder_right){
    this->motor_left = motor_left;
    this->motor_right = motor_right;

    this->encoder_left = encoder_left;
    this->encoder_right = encoder_right;

    is_in_distance_mode = true;

    float p_left = 1;
    float i_left = 0;
    float d_left = 0;

    float p_right = 1;
    float i_right = 0;
    float d_right = 0;

    pid_left.Init(p_left,i_left,d_left , -100, 100);
    pid_right.Init(p_right,i_right,d_right, -100, 100);

    float p_distance = 7;
    float i_distance = 0;
    float d_distance = 0;

    float p_angle = 6;
    float i_angle = 0;
    float d_angle = 0;

    pid_distance.Init(p_distance,i_distance,d_distance, -100, 100);
    pid_angle.Init(p_angle,i_angle,d_angle, -100, 100);

    target_speed_left = 0;
    target_speed_right = 0;

    target_distance = 0;
    target_angle = 0;

    current_distance = 0;
    current_angle = 0;

    x = 0;
    y = 0;
    theta = 0;
}

void DriveController::SetTargetDistance(float target_distance){

    if(target_distance != this->target_distance){
        is_in_distance_mode = true;
    }

    this->target_distance += target_distance;
}

void DriveController::SetTargetAngle(float target_angle){

    if(target_angle != this->target_angle){
        is_in_distance_mode = false;
    }

    this->target_angle = target_angle;
}

void DriveController::Update(float obstacle_distance){

    if(obstacle_distance < collision_distance){
        UrgentStop();
        return;
    }

    long current_time = millis();
    float dt = (current_time - last_update_time) / 1000.0;
    last_update_time = current_time;

    float speed_left = encoder_left->GetRotationSpeed();
    float speed_right = encoder_right->GetRotationSpeed();

    current_distance += (speed_left + speed_right) / 2.0 * dt;  //in ticks
    current_angle += (speed_right - speed_left) / 2.0 * dt;     //in ticks

    float requested_speed = pid_distance.Compute(target_distance, current_distance);

    target_speed_right = pid_right.Compute(requested_speed, speed_right);
    target_speed_left  = pid_left.Compute(requested_speed, speed_left);

    float angle_speed = pid_angle.Compute(target_angle, current_angle);

    target_speed_right += angle_speed;
    target_speed_left -= angle_speed;

    motor_left->SetSpeed(target_speed_left);
    motor_right->SetSpeed(target_speed_right);

    theta += (speed_right - speed_left) / 2.0 * dt; //in degree
    theta = fmod(theta,360);

    x += cos(theta * PI / 180.0) * (speed_left + speed_right) / 2.0 * dt;
    y += sin(theta * PI / 180.0) * (speed_left + speed_right) / 2.0 * dt;
    
    if(obstacle_distance < collision_distance){
        UrgentStop();
        return;
    }
}

float DriveController::GetSpeed(){
    return (encoder_left->GetSpeed() + encoder_right->GetSpeed()) / 2.0;
}


float DriveController::GetTargetSpeed(){
    return (target_speed_left + target_speed_right) / 2.0;
}

float DriveController::GetTargetDistance(){
    return target_distance;
}

float DriveController::GetTargetAngle(){
    return target_angle;
}

float DriveController::GetCurrentDistance(){
    return current_distance;
}

float DriveController::GetCurrentAngle(){
    return current_angle;
}

float DriveController::GetX(){
    return x;
}

float DriveController::GetY(){
    return y;
}

float DriveController::GetTheta(){
    return theta;
}

void DriveController::UrgentStop(){
    motor_left->UrgentStop();
    motor_right->UrgentStop();
}