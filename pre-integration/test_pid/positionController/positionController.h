#include "../driveController/driveController.h";
#include "../ultrasound/ultrasound.h";

#ifndef PositionController_h

#define PositionController_h

struct Point{
    float x;
    float y;
};

struct Path{
    Point point;
    float angle;

    int id;

    Path *next_task;
};

class PositionController
{
    private:
        DriveController *drive_controller;
        Ultrasound *ultrasound;

        Point current_position;
        float current_angle;

        Point target_position;
        float target_angle;

        float Disance(Point point1, Point point2);
        
        Path GetLastPath();

        bool manual_path_mode = true;
        bool next_path = false;

    public:
        bool start;
        Path current_task;

        void Init(DriveController *drive_controller, Ultrasound *ultrasound);
        void Update();

        void AddPath(Point point, float angle);
        void AddPoint(Point point);

        int GetTaskCount();
        int IsTaskCompleted();

        void Start();
        void Stop();
        void Next();
};

#endif