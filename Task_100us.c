#include"macrodriver.h"
#include"Task_100us.h"
#include"Config_OSTM.h"
#include"math.h"
#include"Register_Interface.h"
#include"Digital_Input_Read.h"
#include"Speed.h"
#include"Ramp.h"

#define M_PI 3.14159265358979323846
extern uint8_t TASK_100us_FLAG;

//extern uint8_t TASK_100us_FLAG;
int16_t Sine_Theta;
int16_t Cos_Theta;
uint16_t RotarTheta = 0U;
extern uint16_t tps1_V_Cnt;

float vd_Ratio = 0.0;
int16_t iA_filteredCnt = 0;
int16_t iB_filteredCnt = 0;
int16_t iC_filteredCnt = 0;
int16_t v_q_Act = 0;
int16_t v_q = 0;
int16_t v_d = 0;
int16_t act_Vs = 0;
int16_t watch_IQ = 0;//90;//0

OpenLoopParameters OpenLpParam;
Current_Params IaIb_Params;
Clarke_Params Clarke_AlphaBeta;
CurrentControl_Params Curnt_Controls;
SpeedParameters SpeedParams;
//int16_t valpha_array[2000];
//int16_t vbeta_array[2000];
//int16_t v_q_Act_array[2000];
//int16_t v_q_array[2000];
//int16_t v_d_array[2000];
//int16_t sine_array[2000];
//int16_t cos_array[2000];
float speed_setpoint_array[2000];
float speed_feedback_array[2000];
//int16_t power_array[2000];
float torque_array[2000];
float corrected_theta;
float sine_val;
float cos_val;
//int16_t act_Vs_array[2000];
//int16_t v_q_Act_array[2000];
int16_t T_initial_setpoint = 0;
int16_t T_target_setpoint = 0;
int16_t F_initial_setpoint = 0;
int16_t F_target_setpoint = 0;

uint16_t cnt6 = 0;
uint16_t time = 0;

extern uint16_t flag1; 
float offset = 264.0f;//272.0f;//10.0f;
extern float Rotar_ThetaRadian;
//float torque_PI_SetPoint;
float flux_setPoint;
float T_setpoint = 0.0f;
float F_setpoint = 0.0f;
extern float ramp_torque_setpoint;
extern float ramp_flux_setpoint;

float step_up = 0.09;//0.001;
float step_down = 0.09;//0.001;
int16_t throttle_Read_Act = 0;
float throttle_Read = 0;
uint8_t soft_start_delay = 0;
extern float speed_rps;

/* MTPA Calculation Variable */
uint16_t mtpa_Cal_1 = 0;
uint16_t mtpa_Cal_2 = 0;
int16_t mtpa_Flux_Ref = 0;
float torq_Ref_SI = 0;
int16_t ref_Torque_Nm = 0;

/*limits*/
float flux_ref_limit = -600;
float torque_ref_limit = 800;
float throttle_map_ratio = 0.3975;
extern float Iq_ref;
extern float Id_ref;
extern int16_t flux_Ref_Val;
extern float torque;
extern int16_t Power_input;
uint16_t Speed_PI_counter = 0;

void Task_100micro(void)
{
	if(TASK_100us_FLAG == 1u)
	{
	    //Reading Analog Input for resolver
	    Analog_Read();
	    
	    
	    //
	    GPIO_DriverEnable(GD_CONDITION ,6U);
	    
	    //Delay for increment theta and reading the electrical theta
	    //OpenLpParam.time_adj = 1u;
	    //OpenLpParam.electrical_theta = Emulated_RotarThetaGeneration(OpenLpParam.time_adj);
	    
	    //Generating sin(theta) from electricaltheta
	   OpenLpParam.sincos=0u;
	   OpenLpParam.offset=264u;//10u;
	    //OpenLpParam.sin_theta =  SinCos_AngleConversion_AngleConversion(OpenLpParam.electrical_theta, OpenLpParam.sincos,OpenLpParam.offset);
	   OpenLpParam.sin_theta =  SinCos_AngleConversion_AngleConversion(RotarTheta, OpenLpParam.sincos,OpenLpParam.offset);
	   corrected_theta = (Rotar_ThetaRadian + (offset * (M_PI / 180.0f)));
	   //sine_val = sinf(corrected_theta);
	   // Clamp the value to ensure it stays within [-1.0f, +1.0f]
          /* if (sine_val > 1.0f)
           sine_val = 1.0f;
           else if (sine_val < -1.0f)
           sine_val = -1.0f;*/
	   
	   //OpenLpParam.sin_theta = (int16_t)(sine_val*32767.0f);
	    //Generating cos(theta) from electricaltheta
	   OpenLpParam.sincos=1u;
	   OpenLpParam.offset=264u;
            //OpenLpParam.cos_theta = SinCos_AngleConversion_AngleConversion(OpenLpParam.electrical_theta, OpenLpParam.sincos,OpenLpParam.offset);
           OpenLpParam.cos_theta = SinCos_AngleConversion_AngleConversion(RotarTheta, OpenLpParam.sincos,OpenLpParam.offset);
	   //cos_val = cosf(corrected_theta);
	   
	   // Clamp the value to avoid overflow before casting
           /*if (cos_val > 1.0f)
           cos_val = 1.0f;
           else if (cos_val < -1.0f)
           cos_val = -1.0f;*/
	   
	   //OpenLpParam.cos_theta = (int16_t)(cos_val*32767.0f);
	   if(time == 10){
	  	    calculate_speed_rpm(corrected_theta, &SpeedParams.speed_measured_rpm);
	  	    time = 0;
	    }
	     time ++;
	     torque_cal();
	     Temp_Cal();
	    //Power_Torque_Calculation(SpeedParams.speed_measured_rpm);
	    //Clarke and park for current:
		
	    clarke_transform(iA_filteredCnt,iB_filteredCnt, &Clarke_AlphaBeta.Ialpha, &Clarke_AlphaBeta.Ibeta);
	    
	    park_transform(Clarke_AlphaBeta.Ialpha,Clarke_AlphaBeta.Ibeta,OpenLpParam.sin_theta,OpenLpParam.cos_theta,&Curnt_Controls.iQ,&Curnt_Controls.iD);
	    
	   
	  //ramp_torque_setpoint = RampToTarget(T_initial_setpoint,T_target_setpoint);
	  //ramp_flux_setpoint = RampToTarget(F_initial_setpoint,F_target_setpoint);
	  //ramp_torque_setpoint = Ramp_function(T_setpoint,torque_PI_SetPoint);
	  //ramp_torque_setpoint = Ramp_function(F_setpoint,flux_setPoint);
	  
	  
	  //int16_t *Id_ref, int16_t *Iq_ref = flux_setPoint, torque_PI_SetPoint
	   throttle_Read_Act = ((tps1_V_Cnt - MINIMUM_THROT) * (float)throttle_map_ratio);//max = 3621,min = 730//703//max = 30//0.01038
	    
		if(throttle_Read_Act >= 1160)
		{
			throttle_Read_Act = 1160;
		}
		//Torque_ramp
		if(throttle_Read_Act > throttle_Read)
		{
			soft_start_delay++;
			if(soft_start_delay > RAMP_UP_DELAY)
			{
				throttle_Read+= 1.0f;//0.01f;
			 	soft_start_delay = 0;
			}
		}
		else if(throttle_Read_Act < throttle_Read)
		{
			soft_start_delay++;
			if(soft_start_delay > RAMP_DOWN_DELAY)
			{
				throttle_Read-= 1.0f; //0.01f;
				soft_start_delay = 0;
			}
		}
		
	 //Curnt_Controls.torque_PI_SetPoint = throttle_Read;
	 //Iq_ref = Curnt_Controls.torque_PI_SetPoint;
	 //Speed PI
	 
	 if(Speed_PI_counter > 10)
	 {
             speed_PI_controller(SpeedParams.speed_setPoint,SpeedParams.speed_measured_rpm,&SpeedParams.Tref);
	     Speed_PI_counter = 0;
	 }
	 else
	 {
	     Speed_PI_counter++;
	 }
	 // below method is for the MTPA
	  MTPA_cal(SpeedParams.Tref);
	  Curnt_Controls.torque_PI_SetPoint = Iq_ref * 4.1*1.5;//1.1
	  Curnt_Controls.flux_setPoint = Id_ref * 2.05;
	 

	 
	 // field-weakening
	 //field_weakening(SpeedParams.Tref);
	 //MTPA_cal(SpeedParams.Tref,SpeedParams.speed_measured_rpm);
	 //MTPV_cal();
	 //Curnt_Controls.torque_PI_SetPoint = Iq_ref * 4.1*1.5;//1.1
	 //Curnt_Controls.flux_setPoint = Id_ref * 2.05;
	
	 
	 //Curnt_Controls.flux_setPoint =  flux_Ref_Val;
	 //SpeedParams.Tref = throttle_Read;
	  //MTPA_Cal();
//	  MTPA_OR_FW(SpeedParams.Tref, SpeedParams.speed_measured_rpm, &Curnt_Controls.flux_setPoint, &Curnt_Controls.torque_PI_SetPoint);
//	  Curnt_Controls.flux_setPoint = (Curnt_Controls.flux_setPoint) * (4.1);
//	  Curnt_Controls.torque_PI_SetPoint = (Curnt_Controls.torque_PI_SetPoint) * (4.1);
	  
	  
/*	  if(Curnt_Controls.flux_setPoint < flux_ref_limit)
	  {
		Curnt_Controls.flux_setPoint = flux_ref_limit;
	  }
	  else if(Curnt_Controls.flux_setPoint > 0)
	  {
		Curnt_Controls.flux_setPoint = 0; 
	  }
	  if(Curnt_Controls.torque_PI_SetPoint > torque_ref_limit)
	  {
		Curnt_Controls.torque_PI_SetPoint = torque_ref_limit;
	  }
	  else if(Curnt_Controls.torque_PI_SetPoint < 0)
	  {
		Curnt_Controls.torque_PI_SetPoint = 0; 
	  }
	  */
	  
	   //Torque_ramp
	    /*if(T_setpoint >  Curnt_Controls.torque_PI_SetPoint ) 
	    {
               T_setpoint = T_setpoint - step_up;//0.0005;
	    }
            else if(T_setpoint < Curnt_Controls.torque_PI_SetPoint ) 
	    {
	    T_setpoint = T_setpoint + step_down;//0.001;
	    }
	    else
	    {
		    T_setpoint = Curnt_Controls.torque_PI_SetPoint;
	    }	    
	   ramp_torque_setpoint = T_setpoint;*/
	   ramp_torque_setpoint = Curnt_Controls.torque_PI_SetPoint;
	   //Flux_ramp
	   /*  if(F_setpoint >  Curnt_Controls.flux_setPoint ) 
	    {
               F_setpoint = F_setpoint - step_up;//0.0005;
	    }
            else if(F_setpoint < Curnt_Controls.flux_setPoint ) 
	    {
	      F_setpoint = F_setpoint + step_down;//0.001;
	    }
	    else
	    {
		    F_setpoint = Curnt_Controls.flux_setPoint;
	    }
	    ramp_flux_setpoint = F_setpoint;*/
	    ramp_flux_setpoint = Curnt_Controls.flux_setPoint;
	    v_q_Act = Torque_PI(Curnt_Controls.iQ);

	    v_d = Flux_PI(Curnt_Controls.iD);
	    
	    OpenLpParam.vQ = v_q_Act;//0;
	    OpenLpParam.vD = v_d;//0;
	    //OpenLpParam.vD = ( OpenLpParam.vS * -1 * (float)vd_Ratio);
            //OpenLpParam.vQ = (int16_t)(sqrt((OpenLpParam.vS * OpenLpParam.vS) - ( OpenLpParam.vD * OpenLpParam.vD)));
	    //OpenLpParam.sincos=0u;
	    //OpenLpParam.offset=264u;//10u;
	    //OpenLpParam.sin_theta =  SinCos_AngleConversion_AngleConversion(OpenLpParam.electrical_theta, OpenLpParam.sincos,OpenLpParam.offset);
	    //OpenLpParam.sin_adv_theta =  Adv_SinCos_AngleConversion_AngleConversion(RotarTheta, OpenLpParam.sincos,OpenLpParam.offset,OpenLpParam.adv_theta);
	    
	    //OpenLpParam.sincos=1u;
	    //OpenLpParam.offset=264u;
            //OpenLpParam.cos_theta = SinCos_AngleConversion_AngleConversion(OpenLpParam.electrical_theta, OpenLpParam.sincos,OpenLpParam.offset);
            //OpenLpParam.cos_adv_theta = SinCos_AngleConversion_AngleConversion(RotarTheta, OpenLpParam.sincos,OpenLpParam.offset,OpenLpParam.adv_theta);
	    //InversePark(OpenLpParam.sin_adv_theta,OpenLpParam.cos_adv_theta,OpenLpParam.vQ, OpenLpParam.vD,&OpenLpParam.vAlpha, &OpenLpParam.vBeta);
	    InversePark(OpenLpParam.sin_theta,OpenLpParam.cos_theta,OpenLpParam.vQ, OpenLpParam.vD,&OpenLpParam.vAlpha, &OpenLpParam.vBeta);
            
	    //Feeding the output of inverse park to inverse clarke
	    
	    InverseClarke(OpenLpParam.vAlpha,OpenLpParam.vBeta, &OpenLpParam.vA, &OpenLpParam.vB,&OpenLpParam.vC);
            
	    //Feeding the output of inverse clarke to SVPWM so that sending the pwm values out of microcontroller
	    
	   Svpwm_Duty(OpenLpParam.vA,OpenLpParam.vB,OpenLpParam.vC);
	    
	   if((cnt6<=2000)&&(flag1==1))
	   {
		torque_array[cnt6] = torque;
		speed_setpoint_array[cnt6] = SpeedParams.speed_setPoint;
		speed_feedback_array[cnt6] = SpeedParams.speed_measured_rpm;
		cnt6++;
	   }
	   else
	   {
	        cnt6 = 0;
		flag1 = 0;
	   }
	    //Resetting the timer flag
	    
	    TASK_100us_FLAG = 0u;	    
	    
	}
}

/*void MTPA_Cal(void)
{
	torq_Ref_SI = (ref_Torque_Nm / (float)4.1);// Divisionof 4.1 is Cnt to SI Unit Conversion 
	mtpa_Cal_1 = (uint16_t)(LAMDA_mWb/(2 * (Lq_mH - Ld_mH)));
	mtpa_Cal_2 = (uint16_t)(sqrt((mtpa_Cal_1 * mtpa_Cal_1) + ((float)torq_Ref_SI * (float)torq_Ref_SI)));
	mtpa_Flux_Ref = (int16_t)( (mtpa_Cal_1 - mtpa_Cal_2) * (float)4.1);
	
}*/
