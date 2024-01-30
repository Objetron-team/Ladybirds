#include "pid.h";
#include <Arduino.h>;

void PID::Init(float Kp_,float Ki_,float Kd_, float min_output_, float max_output_){
    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    min_output = min_output_;
    max_output = max_output_;

    target = 0;
    current = 0;
    last_error = 0;
    integral = 0;
    derivative = 0;

    last_time = 0;
    dt = 0;

    output = 0;

}

float PID::Compute(float target_,float current_){
    target = target_;
    current = current_;

    dt = (millis() - last_time) / 1000;
    last_time = millis();

    float error = target - current;
    integral += error * dt;
    derivative = (error - last_error) / dt;

    output = Kp * error + Ki * integral + Kd * derivative;

    last_error = error;

    return ClampOutput(output);
}

float PID::ClampOutput(float output){
    if(output > max_output){
        return max_output;
    }else if(output < min_output){
        return min_output;
    }else{
        return output;
    }
}

float PID::GetError(){
    return target - current;
}

void PID::UpdateKpKiKd(float Kp_,float Ki_,float Kd_){

    //if value is not changed, do not update
    if(Kp_ == Kp && Ki_ == Ki && Kd_ == Kd){
        return;
    }

    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    integral = 0;
}
