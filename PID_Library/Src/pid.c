#include "pid.h"

void PID_Init(PID_Controller* pid, float kp, float ki, float kd, float min_out, float max_out) {
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
    pid->output_limit_min = min_out;
    pid->output_limit_max = max_out;
}

float PID_Compute(PID_Controller* pid, float setpoint, float measurement, float dt) {
    float error = setpoint - measurement;
    //pid->integral += error * dt;
    float derivative = (error - pid->previous_error) / dt;

	//Anti-WindUp integral sıfırlama
    if(pid->previous_error > 0 && error < 0)
	{
		pid->integral=0;
	}
	else if(pid->previous_error < 0 && error > 0)
	{
		pid->integral=0;
	}

    pid->previous_error = error;
    // Sadece çıkış limit içinde kalırsa integral topla
	float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;

	if (output < pid->output_limit_max && output > pid->output_limit_min) {
		pid->integral += error * dt;
	}

    // Sınırlama (limitör)
    if (output > pid->output_limit_max) output = pid->output_limit_max;
    if (output < pid->output_limit_min) output = pid->output_limit_min;

    return output;

}

