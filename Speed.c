#include "speed.h"
#include "macrodriver.h"

#define POLE_PAIRS 4.0f
#define TS_SEC     0.001f // 10ms
int16_t speed = 0;
#define PI 3.14159265f
float testDegree;

uint16_t count22;
float Avrage = 0;
extern uint8_t flag;
float delta_theta ;
float speed_rps;

void calculate_speed_rpm(float rotor_theta_rad_new, float *speed_rpm)
{
	//testDegree = rotor_theta_deg_new;
    
	//float rotor_theta_rad_new = rotor_theta_deg_new * (PI/180.0f);
    static float rotor_theta_rad_prev = 0.0f;
    
     delta_theta = rotor_theta_rad_prev - rotor_theta_rad_new;

    //Handle wrap-around (assuming angle in [0, 360))
    if (delta_theta > PI)
      delta_theta -= 2.0f*PI;
    else if (delta_theta < -PI)
      delta_theta += 2.0f*PI;

    // 360 degrees = one electrical revolution
    if(delta_theta<0)
    {
        speed_rps = (delta_theta / (TS_SEC * 2.0f * PI))*(-1);
    }
    else
    {
	speed_rps = (delta_theta / (TS_SEC * 2.0f * PI));    
    }
         rotor_theta_rad_prev = rotor_theta_rad_new; 

    // Convert to mechanical RPM
    speed = (uint16_t)((speed_rps * 60.0f))/ POLE_PAIRS; //+ 0.5f);
    
    // Store in buffer if logging is enabled
    if (count22 < 500)
    {
        Avrage+=speed;
        count22++;
    }
    else
    {
	Avrage/= 500;
        count22 = 0;
	*speed_rpm = Avrage;
    }
}
