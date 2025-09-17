
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "iodefine.h"
#include "Motor_Control.h"
#include "Trapezoidal_Mode.h"
#include "Config_PWM.h"
#include "macrodriver.h"
#include "Temperature_Cal.h"
#include "math.h"
#include "Digital_Input_Read.h"
#include "IO_Status.h"

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

extern uint16_t speed_RPM;
/* Sector Estmation Variable */
extern uint8_t sector;
/* TPS Signal Variable */
extern uint16_t tps1_V_Cnt;
extern uint16_t dcVolt_ACT;
extern int16_t dc_I_RMS;

extern int16_t v_q_Act;
extern int16_t	v_q;
extern int16_t	v_d;


extern int16_t torque_PI_SetPoint;
extern int16_t flux_setPoint;
extern float Integ_F;
extern float Integ_T;
extern uint8_t flt_CLR;
extern float Torque_Output;
extern float Flux_Output;

extern uint8_t soft_SC_FLT;
extern uint8_t hall_Sens_FLT;

/* Vehical Function Input */
extern uint8_t break_Apply;
extern uint8_t forward_Mode;
extern uint8_t ideal_Mode;
extern uint8_t drive_Mode;
extern uint8_t cruise_Mode;

/* Temperature Variable */
extern uint16_t inv_R_Ph_Temp_Cel;
extern uint16_t inv_Y_Ph_Temp_Cel;
extern uint16_t inv_B_Ph_Temp_Cel;
extern uint16_t mot_Temp_Cel;

extern uint8_t WDT_EN;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
uint8_t rev_Rotate_FLG = 0;
uint8_t PWM_MODE_Switch = 0;
uint8_t soft_start_delay = 0;
uint16_t sect_Cycle_Cnt = 0;
uint16_t sect_Cycle_CLR_Delay_Cnt = 0;
uint8_t pre_Mode_Chang_sector = 0;

float vd_Ratio = 0.4;
int16_t vd_SetPoint = 0;
int16_t vq_SetPoint = 0;

uint16_t ramp_UP_Delay = 0;
uint16_t ramp_Down_Delay = 0;
		
int16_t ref_Torque_Nm = 0;

uint16_t torque_SAT_MAX = 0;
//uint16_t tps_FAST_RESP_CNT = 0;
/* Power Calculcation Variable */
int16_t input_Power = 0;
int16_t output_Power = 0;
uint8_t torque = 0;
int16_t input_Power1 = 0;


/* DC_I PI Variable */
uint16_t pi_Delay_Cnt_Idc_Reg = 0;
uint16_t pi_Delay_Cnt_flx_Ref = 0;
float dc_I_kp = 0.8;
float dc_I_ki = 0.008;
float dc_I_error = 0.0;
float Prop_DC_I = 0.0;
float Integ_DC_I = 0.0;
float pre_DC_I_error =0.0;
int16_t torque_Sat_Limit = 0;
int16_t dc_I_Ref_SI = 0;

/* MTPA Calculation Variable */
uint16_t mtpa_Cal_1 = 0;
uint16_t mtpa_Cal_2 = 0;
int16_t mtpa_Flux_Ref = 0;
float torq_Ref_SI = 0;

/* Speed PI Variable */
float speed_kp = 1.5;
float speed_ki = 0.002;
float speed_error = 0.0;
float Prop_Speed = 0.0;
float Integ_Speed = 0.0;
float pre_Speed_error = 00;
int16_t speed_Sat_Limit = 0;	
int16_t speed_Ref_SI = 0;

/* Speed Control New Methode Variable */
float speed_Derate_Float = 0.0;
int16_t speed_Derate = 0;
int16_t speed_Derate1 = 0;
int16_t speed_Derate2 = 0;
int16_t speed_Derat_Val = 0;
int16_t flux_setPoint_speed = 0;

/* Voltage Derate Variable */
float volt_Derate_Float = 0.0;
int16_t volt_Derate = 0;
int16_t volt_Derate1 = 0;
int16_t volt_Derate2 = 0;
int16_t volt_Derat_Val = 0;
int16_t volt_Derate_Is = 0;

/* Temperature Derate Variable */
int16_t avg_Temp = 0;
float temp_Derate_Float = 0.0;
int16_t temp_Derate = 0;
int16_t temp_Derate1 = 0;
int16_t temp_Derate2 = 0;
int16_t temp_Derat_Val = 0;
int16_t inv_Derate_Is = 0;

/* Motor Temerature Derate */
float mot_temp_Derate_Float = 0.0;
int16_t mot_temp_Derate = 0;
int16_t mot_temp_Derate1 = 0;
int16_t mot_temp_Derate2 = 0;
int16_t mot_temp_Derat_Val = 0;

/* Ref_Flux_PI Variable */
float id_MIN_LIM_MF = 0.5;
float id_MAX_LIM_MF = 0.3;
int16_t Id_MIN = 0;
int16_t Id_MAX = 0;
uint8_t flux_Ref_Start_Cnt = 0;
int16_t act_Vs_FeedBack = 0;
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

int16_t crus_throttle_Read_Act = 0;

int16_t throttle_Read = 0;
int16_t throttle_Read_Act1 = 0;
int16_t throttle_Read_Act = 0;
int16_t torq_Read_Adj = 0;
int16_t prote_Throt_Read = 0;
uint16_t sys_Stabli_Time = 0;

uint8_t test_1_PWM = 1;

uint16_t dcVolt_ACT_CHECK = 0;
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Motor_Run_Mode_Select(void)
{	
	sys_Stabli_Time++;
	if(sys_Stabli_Time < _50ms) /* 50ms */
	{
		Sensor_Health_Check();
	}
	if(sys_Stabli_Time > _250ms) /* 250ms */
	{
		Sensor_Run_Time_Moni();
		Hardware_Fault_Moni();
		Software_Fault_Monitor();
		Stall_Protection();
		Motor_Protection();	
		sys_Stabli_Time = 2501;
	
		Sector_Estimation();
		Deg_Estimation();
		Speed_Estimation();
		Ele_Deg_Estimation();
	}
	
		sect_Cycle_CLR_Delay_Cnt++;
		if( (sect_Cycle_CLR_Delay_Cnt > 400))
		{
			sect_Cycle_CLR_Delay_Cnt = 0;
			if(sector == pre_Mode_Chang_sector)
			{
				sect_Cycle_Cnt = 0;
				PWM_MODE_Switch = 0;
			}
		}
		
		if(forward_Mode == ACTIVATE)
		{
			if( (sector > pre_Mode_Chang_sector) || ((sector == 1) && (pre_Mode_Chang_sector == 6)))
			{
				sect_Cycle_Cnt++;
				sect_Cycle_CLR_Delay_Cnt = 0;
			}
			else if( (sector < pre_Mode_Chang_sector) || ((sector == 6) && (pre_Mode_Chang_sector == 1)))
			{
				sect_Cycle_Cnt = 0;
				rev_Rotate_FLG = 1;
			}
		}
		else if(forward_Mode == DEACTIVATE)
		{
			if( (sector < pre_Mode_Chang_sector) || ((sector == 6) && (pre_Mode_Chang_sector == 1)))
			{
				sect_Cycle_Cnt++;
				sect_Cycle_CLR_Delay_Cnt = 0;
			}
			else if( (sector > pre_Mode_Chang_sector) || ((sector == 1) && (pre_Mode_Chang_sector == 6)))
			{
				sect_Cycle_Cnt = 0;
			}
		}
		pre_Mode_Chang_sector = sector;
		if(sect_Cycle_Cnt > ( NO_OF_ELE_CYCLE_WAIT * 6))//one_Ele_Cycle = 6 Sector
		{
			sect_Cycle_Cnt = (( NO_OF_ELE_CYCLE_WAIT * 6)+1);
			PWM_MODE_Switch = 1;
		}
		
		if( (tps1_V_Cnt >= MINIMUM_THROT) && (sys_Stabli_Time > 2500) && (break_Apply == DEACTIVATE) && (ideal_Mode == DEACTIVATE))
		{
			if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == ACTIVATE) )
			{
				throttle_Read_Act = ((tps1_V_Cnt - MINIMUM_THROT) * (float)0.952);
				if(throttle_Read_Act >= 2400)
				{
					throttle_Read_Act = 2400;
				}								
			}
			else if( (SINUSOIDAL_OPEN_LOOP == ACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE)  && (TPZ_MODE == DEACTIVATE) )
			{
				throttle_Read_Act = ((tps1_V_Cnt - MINIMUM_THROT) * (float)0.4844);
				if(throttle_Read_Act >= 1400)
				{
					throttle_Read_Act = 1400;
				}
			}
			else if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE)  && (TPZ_MODE == DEACTIVATE) )
			{
				if(tps1_V_Cnt > (MINIMUM_THROT+5))
				{
					rev_Rotate_FLG = 0;
				}
				
				throttle_Read_Act = ((tps1_V_Cnt - MINIMUM_THROT) * (float)0.5);//0.4844
								
				if(throttle_Read_Act >= torque_SAT_MAX)
				{
					throttle_Read_Act = torque_SAT_MAX;
				}
				
				
				if(throttle_Read_Act <= 0)
				{
					throttle_Read_Act = 0;
				}
				
			}
		}
		else
		{
			throttle_Read_Act = 0;
		}
		
		if( ( ( (tps1_V_Cnt >= MINIMUM_THROT) &&  (break_Apply == DEACTIVATE) ) && ((forward_Mode == ACTIVATE) || (forward_Mode == DEACTIVATE))) && ( ((SINUSOIDAL_OPEN_LOOP == ACTIVATE) || (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) ) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) ) )
		{
			if(forward_Mode == ACTIVATE)
			{
				dc_I_Ref_SI = DC_I_FOR_MOT_LIMIT_SI;
			}
			else if(forward_Mode == DEACTIVATE)
			{
				dc_I_Ref_SI = DC_I_REV_MOT_LIMIT_SI;
				
			}
						
		}
		else if( ( ( (tps1_V_Cnt < MINIMUM_THROT) && (speed_RPM > 0) ) || ( (break_Apply == ACTIVATE) && (forward_Mode == ACTIVATE) ) ) && (TPZ_MODE == DEACTIVATE) && ( SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) ) 
		{
			throttle_Read_Act = (speed_RPM * 0.8 * -1);
			if(throttle_Read_Act < TORQ_SAT_MIN)
			{
				throttle_Read_Act = TORQ_SAT_MIN;
			}
			dc_I_Ref_SI = DC_I_REG_LIMIT_SI;
		}
			
		prote_Throt_Read = throttle_Read_Act; 
		/* Ramp Function */
                if(throttle_Read_Act > throttle_Read)
		{
			soft_start_delay++;
			if(soft_start_delay > RAMP_UP_DELAY)
			{
				throttle_Read++;
			 	soft_start_delay = 0;
			}
		}
		else if(throttle_Read_Act < throttle_Read)
		{
			soft_start_delay++;
			if(soft_start_delay > RAMP_DOWN_DELAY)
			{
				throttle_Read--;
				soft_start_delay = 0;
			}
		}
		if(cruise_Mode == ACTIVATE)
		{
			throttle_Read = crus_throttle_Read_Act;
		}
			
		
		if((SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == ACTIVATE) )
		{
			v_q = throttle_Read;
			v_d = 0;
		}
			
		if( (SINUSOIDAL_OPEN_LOOP == ACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE)  && (TPZ_MODE == DEACTIVATE) )
		{
			vd_SetPoint = ( throttle_Read * -1 * (float)vd_Ratio);
		        vq_SetPoint = (int16_t)(sqrt((throttle_Read * throttle_Read) - ( vd_SetPoint * vd_SetPoint)));
			
		}
		if( ( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE)  && (TPZ_MODE == DEACTIVATE) ) && ( (forward_Mode == ACTIVATE) || (forward_Mode == DEACTIVATE)) )//&& ( (drive_Mode == ACTIVATE) || (park_Mode == ACTIVATE) ) )
		{
				/* Voltage Derating */
				volt_Derate1 = (dcVolt_ACT - VOLT_SOFT_START_VAL);
				volt_Derate2 = (VOLT_HARD_START_VAL - VOLT_SOFT_START_VAL);
				volt_Derate_Float = ((float)volt_Derate1/(float)volt_Derate2);
				volt_Derate = (100 - (int16_t)(volt_Derate_Float * 100));	/* 100 for elemenating the Float */
				
				if(volt_Derate >= 100)
				{
					volt_Derate = 100;
				}
				if(volt_Derate <= 0)
				{
					volt_Derate = 0;
				}
				volt_Derate_Is = (int16_t)((throttle_Read * volt_Derate)/100);	/* For removing 100 from before multiplcation value of 100 */
				/* Temperature Derating */
				avg_Temp = (int16_t)((inv_R_Ph_Temp_Cel + inv_Y_Ph_Temp_Cel + inv_B_Ph_Temp_Cel)/300);/* is 1/100 for Float Added so need to remove */
				
				temp_Derate1 = (avg_Temp - TEMP_SOFT_START_VAL);
				temp_Derate2 = (TEMP_HARD_START_VAL - TEMP_SOFT_START_VAL);
				temp_Derate_Float = ((float)temp_Derate1/(float)temp_Derate2);
				temp_Derate = (100 - (int16_t)(temp_Derate_Float * 100));
				if(temp_Derate >= 100)
				{
					temp_Derate = 100;
				}
				if(temp_Derate <= 0)
				{
					temp_Derate = 0;
				}
				inv_Derate_Is = (int16_t)((volt_Derate_Is * temp_Derate)/100);
				/* Motor Temp_Derate */
				mot_temp_Derate1 = ((int16_t)(mot_Temp_Cel/100) - TEMP_SOFT_START_VAL_MOT);
				mot_temp_Derate2 = (TEMP_HARD_START_VAL_MOT - TEMP_SOFT_START_VAL_MOT);
				mot_temp_Derate_Float = ((float)mot_temp_Derate1/(float)mot_temp_Derate2);
				mot_temp_Derate = (100 - (int16_t)(mot_temp_Derate_Float * 100));
				if(mot_temp_Derate >= 100)
				{
					mot_temp_Derate = 100;
				}
				if(mot_temp_Derate <= 0)
				{
					mot_temp_Derate = 0;
				}
				ref_Torque_Nm = (int16_t)((inv_Derate_Is * mot_temp_Derate)/100);
				
			
			
			/* Flux Ratio adjust based on Act Vs */
			act_Vs_FeedBack = (int16_t)(sqrt((v_d * v_d) + (v_q_Act *v_q_Act)));
			if(act_Vs_FeedBack > Vs_MAX_FLX_FEEDBACK)
			{
				act_Vs_FeedBack = Vs_MAX_FLX_FEEDBACK;
			}
			else if(act_Vs_FeedBack <= 0)
			{
				act_Vs_FeedBack = 0;
			}
			pi_Delay_Cnt_flx_Ref++;
			if(pi_Delay_Cnt_flx_Ref >= 1)
			{
				Id_MIN = ((float)id_MIN_LIM_MF * -1 * ref_Torque_Nm);
				Id_MAX = ((float)id_MAX_LIM_MF * -1 * ref_Torque_Nm);
				
				if(Id_MAX <= -75)
				{
					Id_MAX = -75;
				}
				
				Flux_Ref_PI();
				MTPA_Cal();
				DC_I_PI();
				
				if(SPEED_PI == 1)/* Speed PI methos Speed Control */
				{
					Speed_PI();
					flux_setPoint = (flux_Ref_Val + mtpa_Flux_Ref +  (torque_Sat_Limit * -1) + (speed_Sat_Limit * -1));
				}
				else if(SPEED_PI == 0)/* Speed Degrate Methods */
				{
					
					speed_Derate1 =  (speed_RPM-speed_Derat_Val);//speed_Derat_Val=soft_Start_Value
					speed_Derate2 = (speed_Ref_SI-speed_Derat_Val);//speed_Ref_SI=hard_Start_Value purpose of stop
					speed_Derate_Float = ((float)speed_Derate1/(float)speed_Derate2);
					speed_Derate = (100 - (int16_t)(speed_Derate_Float * 100));
					
					if(speed_Derate >= 100)
					{
						speed_Derate = 100;
					}
					if(speed_Derate <= 0)
					{
						speed_Derate = 0;
					}
					flux_setPoint = (((flux_Ref_Val * speed_Derate)/100) +  (torque_Sat_Limit * -1) + mtpa_Flux_Ref );
				}
				
				if(flux_setPoint > 0)
				{
					flux_setPoint = 0;
				}
				else if(flux_setPoint < Id_MIN)
				{
					flux_setPoint = Id_MIN;
				}
				
			        iq_SetPoint = ref_Torque_Nm;
				
				iq_Max = (int32_t)((MAX_PWR_W * MAX_TORQUE_CNT * (float)9.55)/((speed_RPM + 1) * MAX_TORQUE));//60/2PI=9.55
				if(iq_Max > MAX_TORQUE_CNT)
				{
					iq_Max = MAX_TORQUE_CNT;
				}
				else if(iq_Max < 100)
				{
					iq_Max = 100;
				}
				if(iq_SetPoint > iq_Max)
				{
					iq_SetPoint = iq_Max;
				}
				else if(iq_SetPoint < 0)
				{
					iq_SetPoint = 0;
				}
					
				if(SPEED_PI == 1)
				{
					torque_PI_SetPoint = (iq_SetPoint +  (((int16_t)(torque_Sat_Limit * (float)0.3)) + speed_Sat_Limit) );//0.25
				}
				else if(SPEED_PI == 0)
				{
					torque_PI_SetPoint = ((int16_t)((iq_SetPoint * speed_Derate)/100) +  ((int16_t)(torque_Sat_Limit * (float)0.5) ) );
					
				}
								
				if(torque_PI_SetPoint < 0)
				{
					torque_PI_SetPoint = 0;
				}
				
				pi_Delay_Cnt_flx_Ref = 0;			
			}
			if(ref_Torque_Nm < 0)
			{
				torque_PI_SetPoint = ref_Torque_Nm;
				flux_setPoint = 0;
			}				
		}
		
		if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == ACTIVATE) && (TPZ_MODE == DEACTIVATE) )
		{
			if(WDT_EN == 1)
			{
				P9.BIT_6 = 0;
				PWM_STOP();
				v_q = 0;
				v_d = 0;
			}
			else
			{
				P9.BIT_6 |= 1;
				if(test_1_PWM == 1)
				{
				    PWM_START();
				    test_1_PWM = 0;
				}
				TAUD0.TO  = 0xA800;
				TAUD0.TOE = 0xABF0;
				Sinusoidal_MODE();
			}
		}
		else
		{
			
			if( (soft_SC_FLT == 1) || (hall_Sens_FLT == 1) || (WDT_EN == 1))
			{
				P9.BIT_6 = 0;
				PWM_STOP();
				v_q = 0;
				v_d = 0;
				Integ_F = 0;
				Flux_Output = 0;
				Integ_T = 0;
				Torque_Output = 0;
				test_1_PWM = 1;
				throttle_Read = 0;
				torque_PI_SetPoint = 0;
				flux_setPoint = 0;
			}
			else
			{
				P9.BIT_6 |= 1;
				if(test_1_PWM == 1)
				{
				    PWM_START();
				    test_1_PWM = 0;
				}
			}
				
				
			if(flt_CLR == 1)
			{
				throttle_Read = 0;
				torque_PI_SetPoint = 0;
				flux_setPoint = 0;
			}
			if( (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == ACTIVATE) )
			{
				Trapezoidal_MODE();
			}
			else if( ( (SINUSOIDAL_OPEN_LOOP == ACTIVATE) || (SINUSOIDAL_OPEN_LOOP == DEACTIVATE) ) && (SINUSOIDAL_SELF_COMMI == DEACTIVATE) && (TPZ_MODE == DEACTIVATE) )
			{
				TAUD0.TO  = 0xA800;
				TAUD0.TOE = 0xABF0;
				Sinusoidal_MODE();
			}
		}
	
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Power_Torque_Calculation(void)
{
	input_Power = (int16_t)(dcVolt_ACT * dc_I_RMS);
	if(input_Power < 0)
	{
		input_Power1 = (uint16_t)(input_Power * -1);
	}
	else
	{
		input_Power1 = input_Power;
	}
	torque = (uint8_t)(((float)9.554 * input_Power1)/(speed_RPM));
	

}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void DC_I_PI(void)
{
	dc_I_error = (dc_I_Ref_SI -  dc_I_RMS);
	Prop_DC_I = (dc_I_error * dc_I_kp);
	Integ_DC_I = (Integ_DC_I + (dc_I_ki * (dc_I_error + pre_DC_I_error)));
	if(Integ_DC_I > 0)
	{
		Integ_DC_I = 0;
	}
	else if ( Integ_DC_I < -460)
	{
		Integ_DC_I = -460;
	}
	torque_Sat_Limit = (Prop_DC_I + Integ_DC_I);
	if(torque_Sat_Limit > 0)
	{
		torque_Sat_Limit = 0;
	}
        else if(torque_Sat_Limit < -460)
        {
        	torque_Sat_Limit = -460;
        }
    	pre_DC_I_error = dc_I_error;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Speed_PI(void)
{	
	speed_error = (speed_Ref_SI -  speed_RPM);
	Prop_Speed = (speed_error * speed_kp);
	Integ_Speed = (Integ_Speed + (speed_ki * (speed_error + pre_Speed_error)));
	if(Integ_Speed > 0)
	{
		Integ_Speed = 0;
	}
	else if ( Integ_Speed < -550)
	{
		Integ_Speed = -550;
	}
	speed_Sat_Limit = (Prop_Speed + Integ_Speed);
	if(speed_Sat_Limit > 0)
	{
		speed_Sat_Limit = 0;
	}
        else if(speed_Sat_Limit < -550)
        {
        	speed_Sat_Limit = -550;
        }
    	pre_Speed_error = speed_error;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Flux_Ref_PI(void)
{
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
}	
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void MTPA_Cal(void)
{
	torq_Ref_SI = (ref_Torque_Nm / (float)4.1);/* Divisionof 4.1 is Cnt to SI Unit Conversion */
	
	mtpa_Cal_1 = (uint16_t)(LAMDA_mWb/(2 * (Lq_mH - Ld_mH)));
	mtpa_Cal_2 = (uint16_t)(sqrt((mtpa_Cal_1 * mtpa_Cal_1) + ((float)torq_Ref_SI * (float)torq_Ref_SI)));
	mtpa_Flux_Ref = (int16_t)( (mtpa_Cal_1 - mtpa_Cal_2) * (float)4.1);
}