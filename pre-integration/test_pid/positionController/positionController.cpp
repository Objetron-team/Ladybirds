#include "positionController.h";
#include "../driveController/driveController.h";


void PositionController::Init(DriveController *drive_controller, Ultrasound *ultrasound){
    this->drive_controller = drive_controller;
    this->ultrasound = ultrasound;

    current_position.x = 0;
    current_position.y = 0;
    current_angle = 0;

    target_position.x = 0;
    target_position.y = 0;
    target_angle = 0;

    current_task.point.x = 0;
    current_task.point.y = 0;
    current_task.angle = 0;
    current_task.id = 0;
    current_task.next_task = NULL;

    start = false;

}

void PositionController::Start(){
    start = true;
}

void PositionController::Stop(){
    start = false;
}

float PositionController::Disance(Point point1, Point point2){
    return sqrt(pow(point1.x - point2.x,2) + pow(point1.y - point2.y,2));
}

void PositionController::Update(float obstacle_distance){

    if(!start){
        return;
    }

    this->drive_controller->Update(obstacle_distance);

    this->current_position.x = this->drive_controller->GetX() * 6.5 * PI / 40;
    this->current_position.y = this->drive_controller->GetY() * 6.5 * PI / 40;
    this->current_angle = (this->drive_controller->GetCurrentAngle() * PI / 40) * 180 / PI;

    if( (IsTaskCompleted() == 1 && manual_path_mode == false) || (next_path == true && manual_path_mode == true )  ){

        next_path = false;

        if(current_task.next_task != NULL){

            Path previous_task = current_task;
            current_task = *current_task.next_task;

            this->target_position = current_task.point;
            this->target_angle = current_task.angle;

            float distance = Disance(target_position,current_position);
            float angle = target_angle;// - current_angle;

            if(Disance(previous_task.point,current_task.point) != 0){

                //convert the distance (in cm) to a nbr of ticks
                distance = distance * 40 / (6.5 * PI);

                this->drive_controller->SetTargetDistance(distance);
            }

            if(previous_task.angle != current_task.angle){

                float angle_rad = angle * PI / 180;

                float arc_length = angle_rad * 40 / PI;

                this->drive_controller->SetTargetAngle(arc_length);

            }
        }
    }
}

void PositionController::AddPath(Point point, float angle){
    Path *new_task = new Path;
    new_task->point = point;
    new_task->angle = angle;
    new_task->id = GetTaskCount();
    new_task->next_task = NULL;

    if(current_task.next_task == NULL){
        current_task.next_task = new_task;
    }else{
        Path *temp_task = current_task.next_task;
        while(temp_task->next_task != NULL){
            temp_task = temp_task->next_task;
        }
        temp_task->next_task = new_task;
    }
}

int PositionController::IsTaskCompleted(){

    //Check if the position is reached
    float distance = Disance(current_task.point,current_position);
    if(distance > 7){
        return -1;
    }

    //Check if the angle is reached
    float angle = current_task.angle - current_angle;
    angle = fmod(angle,360);
    if(angle > 7){
        return -2;
    }

    return 1;
}

int PositionController::GetTaskCount(){
    int count = 1;
    Path *temp_task = current_task.next_task;
    while(temp_task != NULL){
        count++;
        temp_task = temp_task->next_task;
    }
    return count;
}

Path PositionController::GetLastPath(){
    Path *temp_task = &current_task;
    while(temp_task->next_task != NULL){
        temp_task = temp_task->next_task;
    }
    return *temp_task;
}

void PositionController::AddPoint(Point point){
    
    //Calculate the angle to the point from the last point
    Path last_path = GetLastPath();
    float angle = atan2(point.y - last_path.point.y,point.x - last_path.point.x) * 180 / PI;    //degree

    //angle /= 7;

    //add two path, one for the angle and one for the distance
    AddPath(last_path.point,angle);
    AddPath(point,angle);
}

void PositionController::Next(){
    next_path = true;
}