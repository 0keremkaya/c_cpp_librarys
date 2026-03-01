#ifndef PID_H
#define PID_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float integral;
    float previous_error;
    float output_limit_max;
    float output_limit_min;
} PID_Controller;

void PID_Init(PID_Controller* pid, float kp, float ki, float kd, float min_out, float max_out);
float PID_Compute(PID_Controller* pid, float setpoint, float measurement, float dt);

#endif