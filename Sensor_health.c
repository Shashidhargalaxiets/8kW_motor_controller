#include "iodefine.h"
#include "Sensor_health.h"

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

extern int16_t iA_filteredCnt;
extern int16_t iB_filteredCnt;
extern int16_t iC_filteredCnt;

extern uint16_t dc_V_Bus_cnt;
extern int16_t dc_Bus_I_Cnt;

extern uint16_t ac_R_Ph_V_Cnt;
extern uint16_t ac_Y_Ph_V_Cnt;
extern uint16_t ac_B_Ph_V_Cnt;

extern uint16_t tps1_V_Cnt;

extern uint16_t U_FilteredSine_Cnt;
extern uint16_t U_FilteredCos_Cnt;

extern uint16_t motor_Temp_V;

extern uint16_t inv_R_Ph_Temp_V;
extern uint16_t inv_Y_Ph_Temp_V;
extern uint16_t inv_B_Ph_Temp_V;


/* Sensor Heal Check Fault Variable */
uint8_t ac_I_R_Sens_HLTH_FLT          = NO_FAULT;
uint8_t ac_I_Y_Sens_HLTH_FLT          = NO_FAULT;
uint8_t ac_I_B_Sens_HLTH_FLT          = NO_FAULT;
uint8_t dc_I_Sens_HLTH_FLT            = NO_FAULT;
uint8_t ac_V_R_Sens_HLTH_FLT          = NO_FAULT;
uint8_t ac_V_Y_Sens_HLTH_FLT          = NO_FAULT;
uint8_t ac_V_B_Sens_HLTH_FLT          = NO_FAULT;
uint8_t dc_V_Sens_HLTH_FLT            = NO_FAULT;
uint8_t tps1_Sens_HLTH_FLT            = NO_FAULT;
uint8_t tps2_Sens_HLTH_FLT            = NO_FAULT;
uint8_t mot_NTC_Sens_HLTH_FLT         = NO_FAULT;
uint8_t inv_R_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t inv_Y_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t inv_B_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t cur_Sens_HLTH_FLT 	      = NO_FAULT;
uint8_t volt_Sens_HLTH_FLT 	      = NO_FAULT;
uint8_t temp_Sens_HLTH_FLT	      = NO_FAULT;
uint8_t sin_Sens_HLTH_FLT		  = NO_FAULT;
uint8_t cos_Sens_HLTH_FLT		  = NO_FAULT;
uint8_t sens_HLTH_FLT		      = NO_FAULT;
uint8_t limpHome_Mode_Sens_STAT   = DEACTIVATE;
uint8_t Resolver_Sens_FLT		= NO_FAULT;


void Sensor_Health_Check(void)
{
	
	
/* Current Sensor Health Check */
	dc_I_Sens_HLTH_FLT = Fault_Check(dc_Bus_I_Cnt, MIN_I_SENS_HLTH_LIMI, MAX_I_SENS_HLTH_LIMI);
 
	ac_I_R_Sens_HLTH_FLT = Fault_Check(iA_filteredCnt, MIN_I_SENS_HLTH_LIMI, MAX_I_SENS_HLTH_LIMI);
	ac_I_Y_Sens_HLTH_FLT = Fault_Check(iB_filteredCnt, MIN_I_SENS_HLTH_LIMI, MAX_I_SENS_HLTH_LIMI);
	ac_I_B_Sens_HLTH_FLT = Fault_Check(iC_filteredCnt, MIN_I_SENS_HLTH_LIMI, MAX_I_SENS_HLTH_LIMI);
 
 
	if( (ac_I_R_Sens_HLTH_FLT == FAULT) || (ac_I_Y_Sens_HLTH_FLT == FAULT) || (ac_I_B_Sens_HLTH_FLT == FAULT) || (dc_I_Sens_HLTH_FLT == FAULT) )
	{
		cur_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		cur_Sens_HLTH_FLT = NO_FAULT;
	}
	/* Dc Bus Voltage Sensor Health check */
	dc_V_Sens_HLTH_FLT = Fault_Check(dc_V_Bus_cnt, MIN_DCV_SENS_HLTH_LIMI, MAX_DCV_SENS_HLTH_LIMI);
 
	/* Phase Voltage Sensor Health Check */	
	ac_V_R_Sens_HLTH_FLT = Fault_Check(ac_R_Ph_V_Cnt, MIN_PHV_SENS_HLTH_LIMI, MAX_PHV_SENS_HLTH_LIMI);
	ac_V_Y_Sens_HLTH_FLT = Fault_Check(ac_Y_Ph_V_Cnt, MIN_PHV_SENS_HLTH_LIMI, MAX_PHV_SENS_HLTH_LIMI);
	ac_V_B_Sens_HLTH_FLT = Fault_Check(ac_B_Ph_V_Cnt, MIN_PHV_SENS_HLTH_LIMI, MAX_PHV_SENS_HLTH_LIMI);
 
	
	if( ( (ac_V_R_Sens_HLTH_FLT == FAULT) || (ac_V_Y_Sens_HLTH_FLT == FAULT) ) || ( (ac_V_B_Sens_HLTH_FLT == FAULT) || (dc_V_Sens_HLTH_FLT == FAULT) ) )
	{
		volt_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		volt_Sens_HLTH_FLT = NO_FAULT;
	}	
	/* TPS Sensor Signal Health Check */
	tps1_Sens_HLTH_FLT = Fault_Check(tps1_V_Cnt, MIN_TPS_SENS_HLTH_LIMI, MAX_TPS_SENS_HLTH_LIMI);
 
	/*Resolver Health check*/
	sin_Sens_HLTH_FLT = Fault_Check(U_FilteredSine_Cnt, MIN_SIN_SENS_HLTH_LIMI, MAX_SIN_SENS_HLTH_LIMI);
	cos_Sens_HLTH_FLT = Fault_Check(U_FilteredCos_Cnt, MIN_COS_SENS_HLTH_LIMI, MAX_COS_SENS_HLTH_LIMI);
 
	if((sin_Sens_HLTH_FLT == FAULT)||(cos_Sens_HLTH_FLT = FAULT))
	{
		Resolver_Sens_FLT = FAULT;
	}
	else
	{
		Resolver_Sens_FLT = FAULT;
	}
 
	/* Motor Temperature Sensor Health Check */ 
	mot_NTC_Sens_HLTH_FLT = Fault_Check(motor_Temp_V, MIN_MOT_NTC_SENS_HLTH_LIMI, MAX_MOT_NTC_SENS_HLTH_LIMI);
 
	/* Inverter Temperature Sensor Health Check */
	inv_R_Ph_Temp_Sens_HLTH_FLT = Fault_Check(inv_R_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI);
	inv_Y_Ph_Temp_Sens_HLTH_FLT = Fault_Check(inv_Y_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI);
	inv_B_Ph_Temp_Sens_HLTH_FLT = Fault_Check(inv_B_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI);

	/* Over All Temperature Fault */
	if( (mot_NTC_Sens_HLTH_FLT == FAULT) || (inv_R_Ph_Temp_Sens_HLTH_FLT == FAULT) || (inv_Y_Ph_Temp_Sens_HLTH_FLT == FAULT) || (inv_B_Ph_Temp_Sens_HLTH_FLT == FAULT) )
	{
		temp_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		temp_Sens_HLTH_FLT = NO_FAULT;
	}
	/* Over All Sens Health Fault */
	if( (cur_Sens_HLTH_FLT == FAULT) || (volt_Sens_HLTH_FLT == FAULT) || (tps1_Sens_HLTH_FLT == FAULT) || (Resolver_Sens_FLT == FAULT) || (temp_Sens_HLTH_FLT == FAULT) )
	{
		sens_HLTH_FLT = FAULT;
	}
	else
	{
		sens_HLTH_FLT = NO_FAULT;
	}	
}
