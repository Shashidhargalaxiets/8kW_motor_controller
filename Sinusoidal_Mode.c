
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "Sinusoidal_Mode.h"
#include "Config_PWM.h"
#include "Motor_Control.h"
#include "Digital_Input_Read.h"
#include "math.h"
#include "Register_Interface.h"

/**
*****************************************************************************************
*          Macros  
*****************************************************************************************
*/
	
/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/
extern uint8_t PWM_MODE_Switch;

extern uint16_t sect_Deg;
extern int16_t ele_Theta;

extern int16_t ac_R_Ph_I_Cnt;
extern int16_t ac_Y_Ph_I_Cnt;
extern int16_t ac_B_Ph_I_Cnt;

/* Vehical Function Input */
extern uint8_t forward_Mode;
extern uint8_t drive_Mode;
extern uint8_t park_Mode;
/* Hall signal */
extern uint16_t speed_RPM;

extern int16_t vd_SetPoint;
extern int16_t vq_SetPoint;

extern int16_t torque_Sat_Limit;
extern int16_t speed_Sat_Limit;

extern float speed_error;
extern float Prop_Speed;
extern float Integ_Speed;

extern float dc_I_error;
extern float Prop_DC_I;
extern float Integ_DC_I;


extern uint8_t rev_Rotate_FLG;
extern int32_t iq_Max;

extern int16_t iq_SetPoint;
extern int16_t flux_Ref_Val;

extern uint8_t hall_Debouns_Cnt;

extern float delta_Theta;
extern float delta_Theta_cnt;
extern uint16_t freq;

/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
const signed int Table[256] = {0, 807, 1614, 2420, 3224, 4027, 4827, 5624, 6417, 7207, 7992, 8773, 9548, 10317, 11080,
        11837, 12586, 13328, 14061, 14786, 15502, 16208, 16905, 17592, 18267, 18932, 19585, 20226, 20855, 21472, 22075,
        22665, 23241, 23803, 24351, 24883, 25401, 25903, 26390, 26860, 27315, 27752, 28173, 28577, 28963, 29332, 29683,
        30016, 30330, 30627, 30904, 31163, 31403, 31624, 31826, 32008, 32171, 32315, 32439, 32543, 32627, 32692, 32737,
        32761, 32766, 32751, 32717, 32662, 32587, 32493, 32379, 32246, 32092, 31920, 31728, 31516, 31286, 31036, 30768,
        30481, 30175, 29851, 29510, 29150, 28772, 28377, 27965, 27536, 27090, 26627, 26149, 25654, 25144, 24619, 24079,
        23524, 22955, 22372, 21775, 21165, 20542, 19907, 19260, 18601, 17931, 17250, 16558, 15856, 15145, 14425, 13695,
        12958, 12212, 11459, 10700, 9933, 9161, 8383, 7600, 6813, 6021, 5226, 4427, 3626, 2822, 2017, 1211, 404, -404,
        -1211, -2017, -2822, -3626, -4427, -5226, -6021, -6813, -7600, -8383, -9161, -9933, -10700, -11459, -12212,
        -12958, -13695, -14425, -15145, -15856, -16558, -17250, -17931, -18601, -19260, -19907, -20542, -21165, -21775,
        -22372, -22955, -23524, -24079, -24619, -25144, -25654, -26149, -26627, -27090, -27536, -27965, -28377, -28772,
        -29150, -29510, -29851, -30175, -30481, -30768, -31036, -31286, -31516, -31728, -31920, -32092, -32246, -32379,
        -32493, -32587, -32662, -32717, -32751, -32766, -32761, -32737, -32692, -32627, -32543, -32439, -32315, -32171,
        -32008, -31826, -31624, -31403, -31163, -30904, -30627, -30330, -30016, -29683, -29332, -28963, -28577, -28173,
        -27752, -27315, -26860, -26390, -25903, -25401, -24883, -24351, -23803, -23241, -22665, -22075, -21472, -20855,
        -20226, -19585, -18932, -18267, -17592, -16905, -16208, -15502, -14786, -14061, -13328, -12586, -11837, -11080,
        -10317, -9548, -8773, -7992, -7207, -6417, -5624, -4827, -4027, -3224, -2420, -1614, -807, 0};

/* Limit Variable */
int16_t Flux_MAX = 0;
int16_t Flux_MIN = -1140;
int16_t Torque_MAX = 1400;
int16_t Torque_MIN = 0;



/* Self Commision Variable */
uint8_t man_Theta_Inc_delay = 0;
uint8_t man_Theta_delay_adj = 0;
uint16_t man_Theta = 0;


/* Sinusoidal Mode Function Variable */
uint32_t theta1 = 0;
uint16_t OFFSET_THE = 30;
int16_t ADV_THE = 0;
uint32_t rotor_Theta_Act = 0;
uint32_t rotor_Theta1_Act = 0;
uint32_t rotor_Theta = 0;
uint32_t rotor_Theta1 = 0;
uint32_t rotor_Theta_ADV = 0;
uint32_t rotor_Theta1_ADV = 0;
int32_t sine_Theta_ADV = 0;
int32_t cose_Theta_ADV = 0;

int16_t sine_Theta = 0;
int16_t cose_Theta = 0;

int16_t act_Vs = 0;
int16_t v_q_Act = 0;
int16_t v_q = 0;
int16_t v_d = 0;
int16_t v_Alpha = 0;
int16_t v_Beta = 0;

signed int va = 0;
signed int vb = 0;
signed int vc = 0;

uint16_t pi_Delay = 0;
uint16_t manual_Delay = 0;


/* Flux PI variables */
float Error_Flux = 0.0;
float Integ_Error_Flux = 0.0;
float Pre_Error_Flux = 0.0;
float Prop_F = 0.0;
float Integ_F = 0.0;
float Flux_Output = 0;
int16_t flux_setPoint = 0;
int16_t Id_ref = 0;

/* Torque PI variables */
float kp = 0.6;
float ki = 0.003;
float Error_T = 0.0;
float Error_Torque = 0.0;
float Torque_Output = 0.0;
float Integ_Error_Torque = 0.0;
float Pre_Error_Torque = 0.0;
float Prop_T = 0.0;
float Integ_T = 0.0;
int16_t torque_PI_SetPoint = 0;
uint16_t Iq_ref = 0;


/* Clark Trans Variable */
signed int I_Alpha;
signed int I_Beta;

/* Park Trans Variable */
int16_t Id = 0;
int16_t Iq = 0;
float pt_cof_DF = 0.2;
int16_t Id_DF = 0;
int16_t Id_DF_Perivious = 0;
int16_t Id_DF_Use_T = 0;
int16_t Iq_DF = 0;
int16_t Iq_DF_Perivious = 0;
int16_t Iq_DF_Use_T = 0;


/* SVPWM */
int16_t max_Volt = 0;
int16_t min_Volt = 0;
int16_t comon_Mode_V = 0;
float svg_v_alpha;
float svg_v_beta;
float svg_temp1;
float svg_temp2;
float svg_temp3;
uint8_t svg_sector;
int16_t va_SVPWM = 0;
int16_t vb_SVPWM = 0;
int16_t vc_SVPWM = 0;



uint16_t sin_Duty_U = 0;
uint16_t sin_Duty_V = 0;
uint16_t sin_Duty_W = 0;

uint8_t PWM_STAT = 0;


float vd_ratio = 0.0;
//#define array_Size	2000//2300
////const unt16_t array_Size = 4000;
////int16_t sector_Deg_rec[4000];
////int16_t torque_PI_SetPoint_read[array_Size];
////int16_t angleE_Read_rec1[array_Size];
////int16_t throttle_Read_rec1[array_Size];
////int16_t angleE_Read_rec[array_Size];
//int16_t aPH_I_Offset_rec[array_Size];
//int16_t bPH_I_Offset_rec[array_Size];
//int32_t cPH_I_Offset_rec[array_Size];
//int16_t hall_A_rec[array_Size];
////int8_t hall_B_rec[array_Size];
////int8_t hall_C_rec[array_Size];
////int8_t hall_A_Read_rec[array_Size];
////int8_t hall_B_Read_rec[array_Size];
////int8_t hall_C_Read_rec[array_Size];
//////int8_t pwm_SW_rec[array_Size];
////int16_t Delay_Cnt_rec[array_Size];
////int16_t rPH_RMS_rec[2000];
////int16_t yPH_RMS_rec[2000];
////int16_t bPH_RMS_rec[2000];
//int16_t dc_RMS_rec[array_Size];
//int16_t vd_rec[array_Size];
//int16_t vq_rec[array_Size];
//int16_t Id_rec[array_Size];
//int16_t Iq_rec[array_Size];
//int16_t dc_I_CTR_Cnt_DF_rec[array_Size];
//int16_t dc_Bus_I_rec[array_Size];

////int8_t flg_man = 0;
////int8_t flg1 = 0;
////uint8_t minit_rec_Cnt = 0;
//int16_t cnt11 = 0;
//int16_t torque_Set_rec[array_Size];
//int16_t speed_rec[array_Size];
//int16_t flux_set_rec[array_Size];
//int16_t va_rec[array_Size];
////int16_t vb_rec[array_Size];
//int16_t vc_rec[array_Size];
////int16_t throttle_rec[4000];
////int16_t throttle_No_Ramp_rec[4000];
////uint16_t ram_State_rec[4000];
////int16_t offset_Thet_rec[array_Size];
////int16_t adv_Thet_rec[array_Size];
//int16_t speed_rec[array_Size];
////int16_t Is_read[array_Size];
////int16_t sect_Deg_rec[array_Size];
//int16_t ele_Theta1_rec[array_Size];
int16_t ele_Theta1 = 0;
//int16_t dc_Volt_Rec[array_Size];
//int16_t dc_Bus_V_Cnt_Rec[array_Size];
//int16_t throt_Act_rec[array_Size];
uint8_t rec_Delay_Cnt = 0;
uint8_t flg = 1;//0;
uint8_t flg1 = 1;//0;
uint8_t rec_Flg_En = 0;
uint16_t cnt1q = 0;
uint16_t cnt = 0;
uint16_t mode_rec_Cnt = 0;
uint8_t TREIP_ACT = 0;
uint16_t angle_ACT = 0;


int16_t id_DF_Read = 0;
int16_t iq_DF_Read = 0;
int16_t Vq_Read = 0;
int16_t vd_Read = 0;
int16_t flux_Read = 0;
int16_t torque_Read = 0;
int16_t throtle_Act = 0;

int16_t va_Self_Cm = 1000;

int16_t rec_Teake = 0;
unsigned int sin_Cnt = 0;

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Sinusoidal_MODE(void)
{
	if(PWM_MODE_Switch == 0)
	{
		angle_ACT = sect_Deg;
		OFFSET_THE = 0;
	}
	else
	{
		angle_ACT = ele_Theta;
		OFFSET_THE = 30;
	}
	ele_Theta=angle_ACT;
	ele_Theta1 = angle_ACT;
	
	if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == ACTIVATE) && (TPZ_MODE == DEACTIVATE) )
	{		
		man_Theta_Inc_delay++;
	        if(man_Theta_Inc_delay >= man_Theta_delay_adj)
	        {
	            if(man_Theta <= 359)
	            {
	                man_Theta++;
	            }
	            else
	            {
	                man_Theta = 0;
	            }
	            man_Theta_Inc_delay = 0;
	        }
	        ele_Theta = man_Theta;
		OFFSET_THE = 0;
		v_q = va_Self_Cm;		
	}
	Angle_Conversion();
	
	/* Offset theta Base sin and cos find out */
	if(theta1 > (OFFSET_THE*182)) /* 1 degree is equal to 182*/  
	{
		rotor_Theta = theta1 - (OFFSET_THE*182); /* rotor_Theta is Sine theta */
	}
	else
	{
		rotor_Theta = theta1 + ((360-OFFSET_THE)*182); 
	}
    	if (rotor_Theta > 0xFFFF)
   	{
    	    rotor_Theta = 0;
	}
	if (rotor_Theta < 49151) /* cos theta is 90 degree phase shift os sine theta */ 
	{
        	rotor_Theta1 = rotor_Theta + 16383; /* rotor_Theta1 is cos theta */
	}
        else
        {
        	rotor_Theta1 = (rotor_Theta - 49151);
	}
	sine_Theta = Table[rotor_Theta >> 8]; /* 65535 to 256 conversion */ 
    	cose_Theta = Table[rotor_Theta1 >> 8]; /* 65535 to 256 conversion */ 

	
	/* Advance Theta Calculation */
        if( (rotor_Theta+ (ADV_THE * 182)) >= (360* 182) ) /* 1 degree is equal to 182*/
        {
            rotor_Theta_ADV =  (rotor_Theta+ (ADV_THE * 182)) - (360* 182); /* rotor_Theta is Sine theta */
        }
        else
        {
            rotor_Theta_ADV = (rotor_Theta+ (ADV_THE * 182));
        }

        if (rotor_Theta_ADV < 49151) /* cos theta is 90 degree phase shift of sine theta */
        {
            rotor_Theta1_ADV = rotor_Theta_ADV + 16383; /* rotor_Theta1 is cos theta */
        }
        else
        {
            rotor_Theta1_ADV = (rotor_Theta_ADV - 49151);
        }
        sine_Theta_ADV = Table[rotor_Theta_ADV >> 8]; /* 65535 to 256 conversion */ 
        cose_Theta_ADV = Table[rotor_Theta1_ADV >> 8]; /* 65535 to 256 conversion */

	
	Clark_Transfer();
        Park_Transfer();
	pi_Delay++;
	if(pi_Delay >= 1)
        {
		Torque_PI();
		Flux_PI();
		pi_Delay = 0;
		manual_Delay = 0;
		if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == DEACTIVATE) && ( (forward_Mode == ACTIVATE) || (forward_Mode == DEACTIVATE) ) )
		{
			v_q_Act = (signed int)Torque_Output;
			v_d = (signed int)Flux_Output;
			
			if( v_q_Act >= Torque_MAX)
			{
				v_q_Act = Torque_MAX;
			}

			if(v_d <= Flux_MIN)
			{
				v_d = Flux_MIN;
			}
			act_Vs = (int16_t)(sqrt((v_d * v_d)+(v_q_Act * v_q_Act)));
			
			if(act_Vs > Vs_REF_MAX)
			{
				v_q = (int16_t)(sqrt((Vs_REF_MAX * Vs_REF_MAX) - (v_d * v_d)));/*v_q Calculating */
			}
			else
			{
				v_q = v_q_Act;
			}
		}
	}
	if( ( (SINUSOIDAL_OPEN_LOOP == ACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == DEACTIVATE) ) && ( (forward_Mode == DEACTIVATE) || (forward_Mode == ACTIVATE)) )
	{
		v_q = vq_SetPoint;
		v_d = vd_SetPoint;
	}
	
    	/* Inverse park transform based on Paper */
  	v_Alpha = ((v_d * cose_Theta_ADV) - (v_q * sine_Theta_ADV)) >> 15;//divide by 2^15
    	v_Beta = ((v_q * cose_Theta_ADV) + (v_d * sine_Theta_ADV)) >> 15;//divide by 2^15
	
	/* Inverse clark transform */
   	va = (signed int) (v_Alpha); //va = Valpha
    	vb = (signed int) (((1732 * v_Beta) / 2000) - (v_Alpha / 2)); //vb = (-Valpha + 1.732 * Vbeta) / 2
   	vc = (signed int) ((-(1732 * v_Beta) / 2000) - (v_Alpha / 2)); //vc = (-Valpha - 1.732 * Vbeta) / 2
	
	if(SPWM == 0)
	{
		/* SVPWM */
		/* Find Max Volt */
		if(va >= vb)
		{
			if(va >= vc)
			{
				max_Volt = va;
			}
			else
			{
				max_Volt = vc;
			}
		}
		else if(vb >= vc)
		{
			max_Volt = vb;
		}
		else
		{
			max_Volt = vc;
		}
		/* Find Miniumum Volt*/
		if(va <= vb)
		{
			if(va <= vc)
			{
				min_Volt = va;
			}
			else
			{
				min_Volt = vc;
			}
		}
		else if(vb <= vc)
		{
			min_Volt = vb;
		}
		else
		{
			min_Volt = vc;
		}
		comon_Mode_V = -((max_Volt + min_Volt)/2);
		
		va_SVPWM = (va+comon_Mode_V);
		vb_SVPWM = (vb+comon_Mode_V);
		vc_SVPWM = (vc+comon_Mode_V);
		
	}
	else if(SPWM == 1)
	{
		/***********SPWM*************/
		va_SVPWM = va;
		vb_SVPWM = vb;
		vc_SVPWM = vc;
	}
	
	sin_Duty_U = va_SVPWM + DUTY_U_PHASE;
	sin_Duty_V = vb_SVPWM + DUTY_V_PHASE;
	sin_Duty_W = vc_SVPWM + DUTY_W_PHASE;
	
	if( ( (SINUSOIDAL_OPEN_LOOP == ACTIVATE) || (SINUSOIDAL_SELF_COMMI == ACTIVATE) ) && (TPZ_MODE == DEACTIVATE) )
	{
		Update_PWM_Duty(sin_Duty_U , sin_Duty_V , sin_Duty_W); 
	}
	
	if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == DEACTIVATE) && (rev_Rotate_FLG == 1) && (forward_Mode == ACTIVATE) && (drive_Mode == ACTIVATE) )
	{
		Update_PWM_Duty(0, 0, 0); 
		PWM_STAT = 5;
	}
	else
	{		
		Update_PWM_Duty(sin_Duty_U , sin_Duty_V , sin_Duty_W); 
		PWM_STAT = 1;
	}

	

	
	
	
//	rec_Delay_Cnt++;
//	if(rec_Delay_Cnt >= 1)//1
//	{
		
//		rec_Delay_Cnt = 0;
	
			
//		if( (flg == 1) && (cnt < array_Size))// && (stp_FLG == 0))
//		{
////			if(PWM_MODE_Switch == 1)
////			{
////				stp_Cnt++;
////				if(stp_Cnt >= 1700)
////				{
////					stp_FLG = 1;
////					stp_Cnt = 1701;
////				}
////			}
////			if( (high_Level_FLT == 1) || (flt_CLR == 1) )
////			{
////				stp_FLG = 1;
////			}


//			aPH_I_Offset_rec[cnt] = AC_R_PH_V_CNT;//ac_R_Ph_V;//ac_R_Ph_I_Cnt;
//			bPH_I_Offset_rec[cnt] = AC_Y_PH_V_CNT;//ac_Y_Ph_V;//y_Vaue;
//			cPH_I_Offset_rec[cnt] = AC_B_PH_V_CNT;//ac_B_Ph_V;//ac_B_Ph_I_Cnt;
			
//			vd_rec[cnt] = v_d;
//			vq_rec[cnt] = v_q;
//			Id_rec[cnt] = Id_DF;
//			Iq_rec[cnt] = Iq_DF;
//			torque_Set_rec[cnt] = torque_PI_SetPoint;//PWM_change;//torque_PI_SetPoint;
//			flux_set_rec[cnt] = flux_setPoint;//PWM_MODE_Switch;//flux_setPoint;
////			throt_Act_rec[cnt] = ref_Torque_Nm;//throttle_Read;/* Is   After Ramp */
//			va_rec[cnt]= va_SVPWM;//(delta_Theta * 100);//va_SVPWM;//iq_SetPoint;//va_SVPWM;//va;
//			//vb_rec[cnt]= vb_SVPWM;//(delta_Theta_cnt * 100);//vb_SVPWM;//flux_Ref_Val;//vb_SVPWM;//vb;
//			vc_rec[cnt]= torque_Sat_Limit;//vc_SVPWM;//freq;//vc_SVPWM;//torque_Sat_Limit;//vc_SVPWM;//vc;
//			dc_I_CTR_Cnt_DF_rec[cnt] = dc_I_CTR_Cnt_DF;
			
//			//Is_read[cnt] = ref_Torque_Nm;
//			//angleE_Read_rec[cnt] = angle_ACT;
//			hall_A_rec[cnt] = hall_A;
////			hall_B_rec[cnt] = hall_B;
////			hall_C_rec[cnt] = hall_C;
//////						hall_A_rec[cnt+1] = 5;
//////						hall_B_rec[cnt+1] = 5;
//////						hall_C_rec[cnt+1] = 5;
////						hall_A_Read_rec[cnt] = hall_A_Read;
////						hall_B_Read_rec[cnt] = hall_B_Read;
////						hall_C_Read_rec[cnt] = hall_C_Read;
	
////						hall_A_Read_rec[cnt+1] = 5;
////						hall_B_Read_rec[cnt+1] = 5;
////						hall_C_Read_rec[cnt+1] = 5;
//////						pwm_SW_rec[cnt] = PWM_MODE_Switch;
//////						Delay_Cnt_rec[cnt] = hall_Stay_Time;
//			dc_RMS_rec[cnt] = dc_I_RMS;//ele_Theta1;//dc_I_RMS;//dc_Bus_I;//dc_I_RMS;
//			dc_Bus_I_rec[cnt] = dc_Bus_I;
////						torque_Set_rec[cnt] = torque_PI_SetPoint;//torque_Sat_Limit;//torque_PI_SetPoint;
////						flux_set_rec[cnt] = flux_setPoint;
////						throt_Act_rec[cnt] = throttle_Read;/* Before_Ramp */
////						//offset_Thet_rec[cnt] = (int16_t)(rotor_Theta/182);
////						adv_Thet_rec[cnt] =  (int16_t)(rotor_Theta_ADV/182);
//						//sect_Deg_rec[cnt] = sect_Deg;
//			ele_Theta1_rec[cnt] = ele_Theta1;
//			speed_rec[cnt] = speed_RPM;
//			//angleE_Read_rec1[cnt] = throttle_Read_Act;//(int16_t)(theta1/182);
//			//throttle_Read_rec1[cnt] = throttle_Read_Act;
						
//			cnt++;
////			if(cnt >= array_Size)
////			{
////				cnt = 0;
////			}
//			id_DF_Read = PWM_MODE_Switch;//Id_DF;
//			iq_DF_Read = Iq_DF;
//			Vq_Read = v_q;
//			vd_Read = v_d;
//			flux_Read = ele_Theta1;//flux_setPoint;
//			torque_Read=torque_PI_SetPoint;
//			throtle_Act = throttle_Read_Act;
//		}		
//	}
			
		
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Angle_Conversion(void)
{
	ele_Theta = (ele_Theta * (float)(11.375));//360 to 4095 
   	theta1 = ele_Theta *(float)(16.003663);/* convert 4095 to 65535 */
   	if(theta1 >= 65535){
		theta1 = theta1 % 65535;   
   	}
}
/**
*****************************************************************************************
* See header file for function definition. 
*****************************************************************************************
*/
void Clark_Transfer() /* send the current value */
{
	I_Alpha = ac_R_Ph_I_Cnt;
	I_Beta = ((ac_R_Ph_I_Cnt + (2 * ac_Y_Ph_I_Cnt)) * (float)0.57735); /*(1/squre root of 3) = 0.57735*/
}
/**
*****************************************************************************************
* See header file for function definition. 
*****************************************************************************************
*/
void Park_Transfer() 
{
	Id = (((I_Alpha * cose_Theta)  + (I_Beta * sine_Theta)) >> 15);//divide by 2^15
	Iq = ((I_Beta * cose_Theta) - (I_Alpha * sine_Theta)) >> 15;//divide by 2^15
}

/**
*****************************************************************************************
* See header file for function definition. 
*****************************************************************************************
*/
void Flux_PI(void)
{
    Id_DF = (int)((pt_cof_DF * Id) + ( (1 - pt_cof_DF) * Id_DF_Perivious));
    Id_DF_Perivious = Id_DF;

    if( (SINUSOIDAL_OPEN_LOOP == 0) && ((torque_PI_SetPoint == 0) && (speed_RPM == 0)) )
    {
	Id_DF = 0;
	Integ_F = 0;
	Flux_Output = 0;
    }
    Error_Flux = (float)(flux_setPoint - Id_DF);
    Prop_F = (Error_Flux * kp);
    Integ_F = (Integ_F + (ki * (Error_Flux + Pre_Error_Flux)));
    if(Integ_F > (Flux_MAX))
    {
        Integ_F = (Flux_MAX);
    }
    else if ( Integ_F < (Flux_MIN))
    {
        Integ_F = (Flux_MIN);
    }
    Flux_Output = (Prop_F + Integ_F);
    if(Flux_Output > Flux_MAX)
    {
        Flux_Output = Flux_MAX;
    }
    else if(Flux_Output < Flux_MIN)
    {
        Flux_Output = Flux_MIN;
    }
    Pre_Error_Flux = Error_Flux;
}
/**
*****************************************************************************************
* See header file for function definition. 
*****************************************************************************************
*/
void Torque_PI(void)
{
    Iq_DF = (int)((pt_cof_DF * Iq) + ( (1 - pt_cof_DF) * Iq_DF_Perivious));    
    Iq_DF_Perivious = Iq_DF;
    
    if( (SINUSOIDAL_OPEN_LOOP == 0) && ((torque_PI_SetPoint == 0) && (speed_RPM == 0)) )
    {
	Iq_DF = 0;
	Integ_T = 0;
	Torque_Output = 0;
    }
    Error_Torque = (float)(torque_PI_SetPoint - Iq_DF);
    Prop_T = (Error_Torque * kp);
    Integ_T = (Integ_T + (ki * (Error_Torque + Pre_Error_Torque)));
    if(Integ_T > (Torque_MAX))
    {
        Integ_T = (Torque_MAX);
    }
    else if ( Integ_T < (Torque_MIN))
    {
        Integ_T = (Torque_MIN);
    }
    Torque_Output = (Prop_T + Integ_T);
    if(Torque_Output > Torque_MAX)
    {
        Torque_Output = Torque_MAX;
    }
    else if(Torque_Output < Torque_MIN)
    {
        Torque_Output = Torque_MIN;
    }
    Pre_Error_Torque = Error_Torque;
}