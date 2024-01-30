
#ifndef PID_h

#define PID_h

class PID {
    private:
        float Kp;
        float Ki;
        float Kd;

        float target;
        float current;
        float last_error;
        float integral;
        float derivative;

        float last_time;
        float dt;

        float output;

        float min_output;
        float max_output;

        float ClampOutput(float output);

    public:
        void Init(float Kp_,float Ki_,float Kd_, float min_output_, float max_output_);

        float Compute(float target_,float current_);

        void UpdateKpKiKd(float Kp_,float Ki_,float Kd_);

        float GetError();
};

#endif
