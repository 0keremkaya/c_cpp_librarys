/*
Örnek konum pid kontrol kodudur.
Doğrudan derlenip çalıştırılamaz.
Kullanılan sisteme göre zaman ölçümü yapılmalıdır.
*/

#include "main.h"
#include <stdint.h>
#include "pid.h"

#define KP_POS 25.0f
#define KI_POS 0.05f
#define KD_POS 0.15f

uint32_t current_time=0;
uint32_t last_time=0;

float dt=0;
float target_degree=0; 
float current_degree=0;
float target_vel=0;

PID_Controller position_pid;

int main(void)
{
    PID_Init(&position_pid, KP_POS, KI_POS, KD_POS, -1000.0f, 1000.0f); // KONUM PID 

    while (1)
    {
        target_vel = PID_Compute(&position_pid, target_degree, current_degree, dt);
        dt = (current_time - last_time);
        last_time=current_time;
    }

}
