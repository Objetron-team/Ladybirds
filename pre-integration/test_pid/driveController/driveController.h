#include "../motor/motor.h";
#include "../pid/pid.h";
#include "../encoder/encoder.h";



#ifndef DriveController_h

#define DriveController_h

class DriveController
{
private:
    /* data */

    Motor *motor_left;
    Motor *motor_right;

    Encoder *encoder_left;
    Encoder *encoder_right;

    PID pid_left;
    PID pid_right;

    PID pid_distance;
    PID pid_angle;

    bool is_in_distance_mode;

    float target_speed_left;    //in degree per seconde
    float target_speed_right;   //in degree per seconde

    float target_distance;  //in cm
    float target_angle;     //in degree

    float current_distance; //in cm
    float current_angle;    //in degree

    void SetTargetSpeed(float target_speed_left, float target_speed_right);

    float x,y,theta;    //in cm and degree
    long last_update_time;

public:

    void Init(Motor *motor_left, Motor *motor_right, Encoder *encoder_left, Encoder *encoder_right);

    void SetTargetDistance(float target_distance);
    void SetTargetAngle(float target_angle);

    void Update();

    float GetSpeed();

    float GetTargetSpeed();

    float GetTargetDistance();
    float GetTargetAngle();

    float GetCurrentDistance();
    float GetCurrentAngle();

    float GetX();
    float GetY();
    float GetTheta();

    void UrgentStop();
};

#endif