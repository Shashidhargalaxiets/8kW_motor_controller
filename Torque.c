#include"macrodriver.h"
#include"torque.h"
                     //MTPA//FW//MTPA
int16_t Torque_MAX = 800;//200;//800;//1000;//900;//820;//576;//150;//576;//200;//50;//800;//1400;
int16_t Torque_MIN = 0;
float T_kp = 0.25;//0.5;// 0.05;//0.1;2;//tuned value//0.03;//0.001;//0.6;
float T_ki = 0.0001;//0.0002;//0.0001;//tuned value//0.05;//0.52;//0.05;//0.003;//
float T_kc = 0.4;//0.1;//tuned value//0.1;//0.003;
int16_t U; 

int16_t torque_output;
float Err;

//int16_t U_t_array[2000];
int16_t Torque_Output_array[2000];
//float error_t_array[2000];
int16_t Iq_array[2000];

uint16_t cnt4 = 0;
extern uint16_t flag1; 
float pi_sum_Torque=0;
uint16_t one_cycle_flag = 0;
// 0;//100;//0
//int16_t T_initial_setpoint = 0;
//int16_t T_target_setpoint = 0;
float ramp_torque_setpoint;

int16_t Torque_PI(int16_t Iq)
{
    //float Err;
   // float torque_output;
   // float U;
    float Exc;
    float error_int;
    
   // torque_PI_SetPoint = RampToTarget(T_initial_setpoint,T_target_setpoint);
   //torque_PI_SetPoint = ramp_torque_setpoint;
    Err = (int16_t)(ramp_torque_setpoint - Iq);
    
    if (ramp_torque_setpoint == 0)
    {
        pi_sum_Torque = 0;
    }

    error_int = (T_kp * Err);
    
    U = (int16_t)(pi_sum_Torque + error_int);
    
    if (U > Torque_MAX)
    {
        torque_output = Torque_MAX;
    }
    else if (U < Torque_MIN)
    {
        torque_output = Torque_MIN;
    }
    else
    {
        torque_output = U;
    }
    Exc = U - torque_output;
    pi_sum_Torque = pi_sum_Torque + (T_ki * Err) - (T_kc * Exc);
   
    
    if((cnt4<=2000)&&(flag1==1))
	   {
		//error_t_array[cnt4] = Err;
		//U_t_array[cnt4] = U;
		Iq_array[cnt4] = Iq;
		Torque_Output_array[cnt4] = torque_output;
		cnt4++;
	   }
	   else
	   {
	        cnt4 = 0;
		flag1 = 0;
	   }
       
     
    return torque_output;
}