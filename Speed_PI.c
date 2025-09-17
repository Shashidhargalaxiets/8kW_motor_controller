#include "speed.h"
#include "macrodriver.h"

float S_kp = 0.001;//0.00001;		// Proportional gain
float S_ki = 0.00001;//0.000001;		// Integral gain
float S_kc = 0.4;
float Ts=0.001;		// Sample time
float integral=0;		// Integral state
float Speed_MAX = 10.0f;//7000.0f;	// Min limit
float Speed_MIN = 0.0f;//-7000.0f;	// Max limit
float pi_sum_Speed=0;
 float Speed_Err;
 float Exc;
 float error_int;
 float Speed_U;
 
void speed_PI_controller(float speed_setPoint, float speed_measured, float *Tref)
{

	 
    //speed_setPoint = speed_setPoint * (45/7000);
    Speed_Err = (speed_setPoint - speed_measured);
    
    error_int = (S_kp * Speed_Err);
    
    Speed_U = (pi_sum_Speed + error_int);
    
    if (Speed_U > Speed_MAX)
    {
        *Tref = Speed_MAX;
    }
    else if (Speed_U < Speed_MIN)
    {
        *Tref = Speed_MIN;
    }
    else
    {
        *Tref = Speed_U;
    }
    Exc = Speed_U - *Tref;
    pi_sum_Speed = pi_sum_Speed + (S_ki * Speed_Err) - (S_kc * Exc);
   
}
    
    
/*	float e_speed;
	speed_setPoint = speed_setPoint * (45/7000);
    e_speed = speed_setPoint - speed_measured;

    // PI calculation
    integral += e_speed * Ts;
	
    // Output (before saturation)
    *Tref = (uint16_t) (kp * e_speed + ki * integral);

    // Anti-windup and output Tref saturation
    if (*Tref > Speed_MAX)
        *Tref = Speed_MAX;
    else if (*Tref < Speed_MIN)
        *Tref = Speed_MIN;*/
