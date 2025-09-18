#include "iodefine.h"
#include "SensorRunTime_Monitor.h"

extern SpeedParameters SpeedParams;

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

extern uint16_t tps1_V_Cnt;

extern uint16_t dc_V_Bus_cnt;

extern uint16_t U_FilteredSine_Cnt;
extern uint16_t U_FilteredCos_Cnt;

extern uint16_t motor_Temp_V;

extern uint16_t inv_R_Ph_Temp_V;
extern uint16_t inv_Y_Ph_Temp_V;
extern uint16_t inv_B_Ph_Temp_V;

extern uint8_t dc_V_Sens_HLTH_FLT;
extern uint8_t sens_HLTH_FLT;
extern uint8_t tps1_Sens_HLTH_FLT;
extern uint8_t sin_Sens_HLTH_FLT;
extern uint8_t cos_Sens_HLTH_FLT;
extern uint8_t mot_NTC_Sens_HLTH_FLT;
extern uint8_t inv_R_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_Y_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_B_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t temp_Sens_HLTH_FLT;
extern uint8_t limpHome_Mode_Sens_STAT;
extern uint8_t Resolver_Sens_FLT;

uint8_t run_Time_Fault = NO_FAULT;
uint8_t sens_HLTH_OK_FLG = NO_FAULT;


uint8_t vehi_INI_Run_Stat = 0;

void Sensor_Run_Time_Moni(void)
{

	static uint16_t tps1_DB_Cnt = 0;
	static uint16_t inv_R_Temp_HLT_DB_Cnt = 0;
	static uint16_t inv_Y_Temp_HLT_DB_Cnt = 0;
	static uint16_t inv_B_Temp_HLT_DB_Cnt = 0;

	
	/* TPS Sensor Signal Health Check */
	FaultCheck_Debounced(&tps1_Sens_HLTH_FLT, tps1_V_Cnt, MIN_TPS_SENS_HLTH_LIMI, MAX_TPS_SENS_HLTH_LIMI, TPS_DEBOUNCE, &tps1_DB_Cnt);
	

	/*Resolver Health check*/
	sin_Sens_HLTH_FLT = Fault_Check(U_FilteredSine_Cnt, MIN_SIN_SENS_HLTH_LIMI, MAX_SIN_SENS_HLTH_LIMI);
	cos_Sens_HLTH_FLT = Fault_Check(U_FilteredCos_Cnt, MIN_COS_SENS_HLTH_LIMI, MAX_COS_SENS_HLTH_LIMI);

	if((sin_Sens_HLTH_FLT == FAULT)||(cos_Sens_HLTH_FLT == FAULT))
	{
		Resolver_Sens_FLT = FAULT;
	}
	else
	{
		Resolver_Sens_FLT = NO_FAULT;
	}

	/* Motor Temperature Sensor Health Check */ 
	mot_NTC_Sens_HLTH_FLT = Fault_Check(motor_Temp_V, MIN_MOT_NTC_SENS_HLTH_LIMI, MAX_MOT_NTC_SENS_HLTH_LIMI);

	/* Inverter Temperature Sensor Health Check */
	FaultCheck_Debounced(&inv_R_Ph_Temp_Sens_HLTH_FLT, inv_R_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI, INV_TEMP_HLT_DEBOUNCE, &inv_R_Temp_HLT_DB_Cnt);
	FaultCheck_Debounced(&inv_Y_Ph_Temp_Sens_HLTH_FLT, inv_Y_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI, INV_TEMP_HLT_DEBOUNCE, &inv_Y_Temp_HLT_DB_Cnt);
	FaultCheck_Debounced(&inv_B_Ph_Temp_Sens_HLTH_FLT, inv_B_Ph_Temp_V, MAX_INV_TEMP_SENS_HLTH_LIMI, MIN_INV_TEMP_SENS_HLTH_LIMI, INV_TEMP_HLT_DEBOUNCE, &inv_B_Temp_HLT_DB_Cnt);
	

	/* Over All Temperature Fault */
	if( ((mot_NTC_Sens_HLTH_FLT == FAULT) || (inv_R_Ph_Temp_Sens_HLTH_FLT == FAULT)) || ((inv_Y_Ph_Temp_Sens_HLTH_FLT == FAULT) || (inv_B_Ph_Temp_Sens_HLTH_FLT == FAULT)) )
	{
		temp_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		temp_Sens_HLTH_FLT = NO_FAULT;
	}
		
	/* Over All Run Time Fault */
	if( (tps1_Sens_HLTH_FLT == FAULT ) || (temp_Sens_HLTH_FLT == FAULT) )
	{
		run_Time_Fault = FAULT;
	}
	else
	{
		run_Time_Fault = NO_FAULT;
	}
}