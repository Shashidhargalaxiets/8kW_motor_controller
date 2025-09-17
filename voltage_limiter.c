#include"voltage_limiter.h"
#include"macrodriver.h"
#include "math.h"

#define Vs_REF_MAX 200//50//750//1350
extern int16_t v_q_Act;
extern int16_t v_d;
extern int16_t v_q;
int16_t vq_final = 0;

int16_t Torque_PI_MAX = 200;
int16_t Torque_PI_MIN = 0;
int16_t torque_PI_output = 0;

int16_t Flux_PI_MAX = 0;
int16_t Flux_PI_MIN = -5;
int16_t Flux_PI_output = 0;

int16_t act_Vs_Var = 0;

int16_t voltage_limit(int16_t vq,int16_t vd)
{
                        if( vq >= Torque_PI_MAX)
			{
				vq = Torque_PI_MAX;
			}

			if(vd <= Flux_PI_MIN)
			{
				vd = Flux_PI_MIN;
			}
			
			act_Vs_Var = (int16_t)(sqrt((vd * vd)+(vq * vq)));
		
			if(act_Vs_Var > Vs_REF_MAX)
			{
				vq_final = (int16_t)(sqrt((Vs_REF_MAX * Vs_REF_MAX) - (vd * vd)));//v_q Calculating 
			}
			else
			{
				vq_final = vq;
			}
			return vq_final;
}

int16_t Torque_limiter(int16_t T_PI_output)
{
    if (T_PI_output > Torque_PI_MAX)
    {
        torque_PI_output = Torque_PI_MAX;
    }
    else if (T_PI_output < Torque_PI_MIN)
    {
        torque_PI_output = Torque_PI_MIN;
    }
    else
    {
        torque_PI_output = T_PI_output;
    }
    return torque_PI_output;
}

int16_t Flux_limiter(int16_t F_PI_output)
{
    if (F_PI_output > Flux_PI_MAX)
    {
        Flux_PI_output = Flux_PI_MAX;
    }
    else if (F_PI_output < Flux_PI_MIN)
    {
        Flux_PI_output = Flux_PI_MIN;
    }
    else
    {
        Flux_PI_output = F_PI_output; 
    }
    return Flux_PI_output;
}