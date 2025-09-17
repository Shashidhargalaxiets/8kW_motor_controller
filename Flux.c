#include"macrodriver.h"
#include"flux.h"

extern float kp;
extern float ki;
extern float kc ;

int16_t Flux_MAX = 0;
                  //MTPA//FW//MTPA
int16_t Flux_MIN = -950;//-1230;//-950;//-750;//-600;//-472;//-300;//0;//-210;//-20;//0;//-1140;

int16_t Flux_Output;
float F_kp = 0.25;//0.5;//0.05;//0.1;///1;//2;//tuned value//0.03;//0.001;//0.6;
float F_ki = 0.0001;//0.0002;//0.0001;//0.009;//tuned value//0.05;//0.52;//0.05;//0.003;//
float F_kc = 0.4;//0.1;//tuned value//0.1;//0.003;
//float error_f_array[2000];
//int16_t U_f_array[2000];
int16_t Flux_Output_array[2000];                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
int16_t Id_array[2000];
uint16_t cnt3 = 0;
extern uint16_t flag1; 
//int16_t F_initial_setpoint = 0;
//int16_t F_target_setpoint = 0;
float ramp_flux_setpoint;

int16_t Flux_PI(int16_t iD)
{
    float Err;
    
    int16_t U;
    float Exc;
    static float pi_sum_Flux=0;
    //flux_setPoint = RampToTarget(F_initial_setpoint,F_target_setpoint);
    //flux_setPoint = ramp_flux_setpoint;
    Err = (int16_t)ramp_flux_setpoint - iD;
    U = (int16_t)(pi_sum_Flux + (F_kp * Err));
 
    if (U > Flux_MAX)
    {
        Flux_Output = Flux_MAX;
    }
    else if (U < Flux_MIN)
    {
        Flux_Output = Flux_MIN;
    }
    else
    {
        Flux_Output = U;
    }
 
    Exc = U - (Flux_Output);
    pi_sum_Flux = pi_sum_Flux + (F_ki * Err) - (F_kc * Exc);
    
    if((cnt3<=2000)&&(flag1==1))
	   {
		//error_f_array[cnt3] = Err;
		//U_f_array[cnt3] = U;
		Flux_Output_array[cnt3] = Flux_Output;
		Id_array[cnt3] = iD;
		cnt3++;
	   }
	   else
	   {
	        cnt3 = 0;
		flag1 = 0;
	   }
    return Flux_Output;
}