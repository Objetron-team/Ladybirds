#include "motor/motor.h";
#include "motor/motor.cpp";

#include "encoder/encoder.h";
#include "encoder/encoder.cpp";

#include "pid/pid.h";
#include "pid/pid.cpp";

Motor motorRight;
Motor motorLeft;

const int MOTOR_RIGHT_NBR = 2;
const int MOTOR_LEFT_NBR = 1;

const int time_to_get_to_speed = 1;
const float turnFactor = 1;

void InitMotor(){
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    AFMS.begin();

    motorRight.Init(AFMS,MOTOR_RIGHT_NBR,time_to_get_to_speed);
    motorLeft.Init(AFMS ,MOTOR_LEFT_NBR ,time_to_get_to_speed);

    motorRight.SetSpeed(0);
    motorLeft.SetSpeed(0);
}

const int WHEEL_ENCODER_PIN_RIGHT = 2;
const int WHEEL_ENCODER_PIN_LEFT = 3;

Encoder encoderRight;
Encoder encoderLeft;

void InitEncoder(){

    encoderRight.Init(&motorRight,WHEEL_ENCODER_PIN_RIGHT);
    encoderLeft.Init(&motorLeft,WHEEL_ENCODER_PIN_LEFT);

    attachInterrupt(digitalPinToInterrupt(WHEEL_ENCODER_PIN_RIGHT), CouterRight, FALLING);
    attachInterrupt(digitalPinToInterrupt(WHEEL_ENCODER_PIN_LEFT), CouterLeft, FALLING);
}

void CouterRight(){
    //Serial.println("Right Counter ; ");
    //Serial.println(encoderRight.GetCounter());

    encoderRight.DebouncedCount();
}

void CouterLeft(){
    //Serial.println("Left Counter ; ");
    //Serial.println(encoderLeft.GetCounter());

    encoderLeft.DebouncedCount();
}

int target_counter_right = 0;
int target_counter_left = 0;

        //PID parameter for the right motor
float Kp_r = 0.0f;
float Ki_r = 0.0f;
float Kd_r = 0.0f;

//PID parameter for the left motor
float Kp_l = 0.0f;
float Ki_l = 0.0f;
float Kd_l = 0.0f;

PID left_PID;
PID Right_PID;

void InitPID(){
    left_PID.Init(Kp_l,Ki_l,Kd_l);
    Right_PID.Init(Kp_r,Ki_r,Kd_r);
}


int position_right = 0;
int position_left = 0;

void setup() {

    Serial.begin(9600);


    InitMotor();
    InitEncoder();
    InitPID();
}


void DebugRight(int error_right,float PID_right){
    Serial.print("Right :");

    Serial.print("M dir : ");
    Serial.print(motorRight.GetDirection());
    Serial.print(" - ");
    
    Serial.print("Speed : ");
    Serial.print(motorRight.GetSpeed());
    Serial.print(" - ");

    Serial.print("Counter : ");
    Serial.print(encoderRight.GetCounter());
    Serial.print(" - ");

    Serial.print("Error : ");
    Serial.print(error_right);
    Serial.print(" - ");

    Serial.print("PID : ");
    Serial.println(PID_right);
}

void DebugLeft(int error_left,float PID_left){
    Serial.print("Left :");

    Serial.print("M dir : ");
    Serial.print(motorLeft.GetDirection());
    Serial.print(" - ");

    Serial.print("Speed : ");
    Serial.print(encoderLeft.GetSpeed());
    Serial.print(" - ");

    Serial.print("Counter : ");
    Serial.print(encoderLeft.GetCounter());
    Serial.print(" - ");

    Serial.print("Error : ");
    Serial.print(error_left);
    Serial.print(" - ");

    Serial.print("PID : ");
    Serial.println(PID_left);
}




void ControlFromSerial(){
    if(Serial.available() > 0){
        String input = Serial.readString();

        // set the target counter base on the input zqsd
        // {side}{value}
        // z -> forward, s -> backward, q -> left, d -> right
        // value: int value

        // example: z100 -> set the target counter of the right and left motor to 100

        if(input[0] == 'z' || input[0] == 's' || input[0] == 'q' || input[0] == 'd'){
            int value = input.substring(1).toInt();
            if(input[0] == 'z'){
                target_counter_right = value;
                target_counter_left = value;
            }
            if(input[0] == 's'){
                target_counter_right = -value;
                target_counter_left = -value;
            }
            if(input[0] == 'q'){
                target_counter_right = value;
                target_counter_left = -value;
            }
            if(input[0] == 'd'){
                target_counter_right = -value;
                target_counter_left = value;
            }
        }

        // update PID parameter base on the input
        // {side}{parameter}{value}
        // side: r -> right motor, l -> left motor, b -> both motor
        // parameter: p -> Kp, i -> Ki, d -> Kd
        // value: float value

        // example: rpi0.5 -> set Kp of the right motor to 0.5

        if(input[0] == 'r' || input[0] == 'l' || input[0] == 'b'){
            if(input[1] == 'p' || input[1] == 'i' || input[1] == 'd'){
                float value = input.substring(2).toFloat();
                if(input[0] == 'r'){
                    if(input[1] == 'p'){
                        Kp_r = value;
                        Serial.println("Update Kp_r");
                        Serial.println(Kp_r);
                    }
                    if(input[1] == 'i'){
                        Ki_r = value;
                    }
                    if(input[1] == 'd'){
                        Kd_r = value;
                    }
                }
                if(input[0] == 'l'){
                    if(input[1] == 'p'){
                        Kp_l = value;
                    }
                    if(input[1] == 'i'){
                        Ki_l = value;
                    }
                    if(input[1] == 'd'){
                        Kd_l = value;
                    }
                }
                if(input[0] == 'b'){
                    if(input[1] == 'p'){
                        Kp_r = value;
                        Kp_l = value;
                    }
                    if(input[1] == 'i'){
                        Ki_r = value;
                        Ki_l = value;
                    }
                    if(input[1] == 'd'){
                        Kd_r = value;
                        Kd_l = value;
                    }
                }
            }
        }

    }

    left_PID.UpdateKpKiKd(Kp_l,Ki_l,Kd_l);
    Right_PID.UpdateKpKiKd(Kp_r,Ki_r,Kd_r);
}

void loop(){
    
    //get the distance from right and left encoder
    float distance_in_tick = ( encoderRight.GetCounter() - encoderLeft.GetCounter() ) / 2;

    float angle_in_tick = ( encoderRight.GetCounter() - encoderLeft.GetCounter() );

    ControlFromSerial();



    float PID_right = Right_PID.Compute(target_counter_right, encoderRight.GetCounter());
    float PID_left = left_PID.Compute(target_counter_left, encoderLeft.GetCounter());

    
    //DebugLeft(left_PID.GetError(), PID_left);
    DebugRight(Right_PID.GetError(), PID_right);




    //set the speed of the motor
    motorRight.SetSpeed(PID_right);
    motorLeft.SetSpeed(PID_left);

}