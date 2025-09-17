#include "MTPA.h"
#include "macrodriver.h"
#include <math.h>
#include "stdint.h"

float Id_mtpa = 0.0f;
float Iq_mtpa = 0.0f;

// Inputs
float omega_e;			  // Electrical speed in rad/s

// Result variables
float id_fw_max_torque, iq_fw_max_torque;
float id_fw_given_torque, iq_fw_given_torque;
float Im = 0;

/* Ref_Flux_PI Variable */
float id_MIN_LIM_MF = 0.5;
float id_MAX_LIM_MF = 0.3;
int16_t Id_MIN = 0;
int16_t Id_MAX = 0;
uint8_t flux_Ref_Start_Cnt = 0;
float flux_Ref_Kp = 0.4;
float flux_Ref_Ki = 0.001;
float flux_Ref_Error = 0;
float Pro_Flux_Ref = 0;
float Integ_Flux_Ref = 0;
float pre_flux_Ref_Error = 0;
int16_t flux_Ref_Val = 0;
int32_t iq_Max = 0;
int16_t iq_SetPoint = 0;
int16_t iq_Max_Limit = 0;
//SVG
//float term1 = -16.1928;//-129.542;//-274.14;
//float term2 = 262.206;//16781.23;//75152.89;
float Iq_ref = 0.0f;
float Id_ref = 0.0f;
float term3 = 0.0f;
float Iq_ref_factor = 0.0f;
extern int16_t v_d ;
extern int16_t v_q_Act;
int16_t act_Vs_FeedBack = 0;
extern float throttle_read;
float I_max = 282.8f;
void MTPA()			//Tref = speed_Sat_Limit in mahesh sir code
{
    float delta_L = Lq - Ld;
    float second_term;
    float lambda_term;

    // Step 2: Compute Id_mtpa using analytical formula
    lambda_term = lambda_pm / (4.0f * delta_L);
    second_term= sqrtf(((lambda_pm * lambda_pm) / (16.0f * delta_L * delta_L)) + (Im * Im / 2.0f));
    
    Id_mtpa = lambda_term - second_term;

    // Step 3: Compute Iq
    Iq_mtpa = sqrtf(Im * Im - Id_mtpa * Id_mtpa);
}

void compute_field_weakening_max_torque()
{
    float denominator = (Ld * Ld - Lq * Lq);
    float A = lambda_pm * Ld;
    float A1 = (lambda_pm * Ld)*(lambda_pm * Ld);
    float B =  A1 - (denominator * ((lambda_pm*lambda_pm) + (Lq * Lq * I_max * I_max) - ((v_max*v_max) / (omega_e*omega_e))));
    
    id_fw_max_torque = (-A + sqrt(B)) / denominator;
    iq_fw_max_torque = sqrt((I_max * I_max) - (id_fw_max_torque * id_fw_max_torque));

}

void compute_field_weakening_given_torque()
{
	
    // Constants used in the torque and voltage constraint equation
    float term;
    compute_field_weakening_max_torque();
    
    term = ((v_max * v_max) / (omega_e * omega_e)) - (Lq * Lq * iq_fw_given_torque *iq_fw_given_torque);   
    id_fw_given_torque = (-lambda_pm / Ld) + (1.0 / Ld) * sqrt(term);
    iq_fw_given_torque = sqrt((I_max * I_max) - (id_fw_given_torque * id_fw_given_torque));
}

void MTPA_OR_FW(float Tref, uint16_t speed, float *Id_ref, float *Iq_ref)			//Tref = speed_Sat_Limit in mahesh sir code
{    
    // Step 1: Calculate total current magnitude required
    float Im_ref = (2.0f * Tref) / (3.0f * p * lambda_pm);
    // Clamp Im_ref
    if (Im_ref > I_max){
	Im = I_max;
    }
    else{
	Im = Im_ref;
    } 
    if(speed < 2000){
	 MTPA();
	*Id_ref = Id_mtpa;
        *Iq_ref = Iq_mtpa;
    }else{ 
	compute_field_weakening_given_torque();
	// For MAX(id_fw_given_torque, -I_max)
	if (id_fw_given_torque > -I_max)
	    *Id_ref = id_fw_given_torque;
	else
	    *Id_ref = (-I_max);

	// For MIN(iq_fw_given_torque, Im)
	if (iq_fw_given_torque < Im)
	    *Iq_ref = iq_fw_given_torque;
	else
	    *Iq_ref = Im;
    } 
}

void MTPA_cal(float torque_ref)
{       
	//Iq_ref = Iq_ref/4.1;
	Iq_ref_factor = I_max_factor*torque_ref;
	term3 = sqrtf(term2 + ((Iq_ref_factor*Iq_ref_factor)/2));
	Id_ref = (term1 - term3) ;
	Iq_ref = sqrtf((Iq_ref_factor*Iq_ref_factor) - (Id_ref*Id_ref));
	if(torque_ref < 5)
	{
	  Id_ref = 0;
	  Iq_ref = 0;
	}
}

void MTPV_cal(void)
{
	Iq_ref = ((I_max*I_max) - (Id_ref*Id_ref));
}

/*void field_weakening(float torque_ref)
{
      act_Vs_FeedBack = (sqrt((v_d * v_d) + (v_q_Act *v_q_Act)));      if(act_Vs_FeedBack > Vs_MAX_FLX_FEEDBACK)      {        act_Vs_FeedBack = Vs_MAX_FLX_FEEDBACK;      }      else if(act_Vs_FeedBack <= 0)      {        act_Vs_FeedBack = 0;      }
        Id_MIN = ((float)id_MIN_LIM_MF * -1 * torque_ref);        Id_MAX = ((float)id_MAX_LIM_MF * -1 * torque_ref);        if(Id_MAX <= -75)        {          Id_MAX = -75;        }
	
	flux_Ref_Error = (Vs_REF_MAX - act_Vs_FeedBack);
	Pro_Flux_Ref = (flux_Ref_Error * flux_Ref_Kp);
	Integ_Flux_Ref = (Integ_Flux_Ref + (flux_Ref_Ki * (flux_Ref_Error + pre_flux_Ref_Error)));
	if(Integ_Flux_Ref < Id_MIN)
	{
		Integ_Flux_Ref = Id_MIN;
	}
	else if(Integ_Flux_Ref > Id_MAX)
	{
		Integ_Flux_Ref = Id_MAX;
	}
	flux_Ref_Val = (Pro_Flux_Ref + Integ_Flux_Ref);
	if(flux_Ref_Val < Id_MIN)
	{
		flux_Ref_Val = Id_MIN;
	}
	else if(flux_Ref_Val > Id_MAX)
	{
		flux_Ref_Val = Id_MAX;
	} 
	pre_flux_Ref_Error = flux_Ref_Error;
}*/


