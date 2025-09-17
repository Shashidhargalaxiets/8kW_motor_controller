
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "iodefine.h"
#include "Fault_Analysis.h"
#include "Register_Interface.h"
#include "Digital_Input_Read.h"
#include "IO_Status.h"

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/
/* Hall Signals Variable */
extern uint8_t hall_A;
extern uint8_t hall_B;
extern uint8_t hall_C;

/* Hardware Fault Signal Monitor Variable */
extern uint8_t sht_FLT_Sign;
extern uint8_t ocp_FLT_Sign;

/* AC Current Signal Variable */
extern int16_t ac_R_Ph_I;
extern int16_t ac_Y_Ph_I;
extern int16_t ac_B_Ph_I;
extern uint16_t aPH_I_ACT_RMS;
extern uint16_t bPH_I_ACT_RMS;
extern uint16_t cPH_I_ACT_RMS;

/* AC Voltage Signal Varible */
extern int16_t ac_R_Ph_V;
extern int16_t ac_Y_Ph_V;
extern int16_t ac_B_Ph_V;

/* DC Current Signal Variable */
extern int16_t dc_Bus_I;
extern int16_t dc_I_CTR_Cnt_DF;
extern int16_t dc_I_RMS;
/* DC Voltage Signal Variable */
extern int16_t dc_Bus_V;
extern uint16_t dcVolt_ACT;

/* TPS Sensor Variable */
extern uint16_t tps1_V_Cnt;
extern uint16_t tps2_V_Cnt;

/* Motor Temperature Sensor Variable */
extern uint16_t motor_Temp_V;

/* Inverter Temperature Sensor Variable */
extern uint16_t inv_R_Ph_Temp_V;
extern uint16_t inv_Y_Ph_Temp_V;
extern uint16_t inv_B_Ph_Temp_V;

/* Auxilary Power Supply Variable */
extern uint16_t mon_15V;
extern uint16_t mon_5V;
extern uint16_t mon_TPS_5V;

/* Protection Function Variable */
extern uint16_t speed_RPM;
extern int16_t prote_Throt_Read;
extern int16_t	v_q;
extern int16_t	v_d;

extern uint8_t side_Stand;

extern int16_t throttle_Read;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
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
uint8_t mot_NTC_Sens_HLTH_FLT        = NO_FAULT;
uint8_t inv_R_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t inv_Y_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t inv_B_Ph_Temp_Sens_HLTH_FLT   = NO_FAULT;
uint8_t cur_Sens_HLTH_FLT 	      = NO_FAULT;
uint8_t volt_Sens_HLTH_FLT 	      = NO_FAULT;
uint8_t temp_Sens_HLTH_FLT	      = NO_FAULT;
uint8_t sens_HLTH_FLT		      = NO_FAULT;


/* Run Time Sensor Monitor Variable */
uint8_t vehi_INI_Run_Stat = 0;
uint8_t sens_HLTH_OK_FLG = 0;
uint16_t ss_ReadTime_Cnt = 0;

uint8_t hall_Sens_FLT_CLR = 0;
uint8_t hall_Sens_FLT     = NO_FAULT;
uint8_t pGood_15V_FLT     = NO_FAULT;
uint8_t pGood_5V_FLT      = NO_FAULT;
uint8_t pGood_TPS_5V_FLT    = NO_FAULT;
uint8_t tps_Sens_HLTH_FLT = NO_FAULT;
uint8_t ps_Sens_HLTH_FLT  = NO_FAULT;
uint8_t run_Time_Fault	  = NO_FAULT;
uint8_t hall_Debouns_Cnt  = CLEAR;
uint8_t tps1_DB_Cnt = CLEAR;
uint8_t tps2_DB_Cnt = CLEAR;
uint8_t inv_R_Temp_HLT_DB_Cnt = CLEAR;
uint8_t inv_Y_Temp_HLT_DB_Cnt = CLEAR;
uint8_t inv_B_Temp_HLT_DB_Cnt = CLEAR;
uint8_t dc_I_SC_DB_Cnt = CLEAR;
uint8_t ac_R_PH_SC_DB_Cnt = CLEAR;
uint8_t ac_Y_PH_SC_DB_Cnt = CLEAR;
uint8_t ac_B_PH_SC_DB_Cnt = CLEAR;
uint8_t pGood_15V_DB_Cnt = CLEAR;
uint8_t pGood_5V_DB_Cnt = CLEAR;
uint8_t pGood_TPS_DB_Cnt = CLEAR;

/* Hardware Fault Status Variable */
uint8_t sht_FLT		 = NO_FAULT;
uint8_t ocp_FLT	         = NO_FAULT;
uint8_t hrd_FLT		 = NO_FAULT;


/* Software Fault Monitor Variable */
uint8_t dc_BUS_SC_FLT     = NO_FAULT;
uint8_t mot_R_Phase_SC_FLT  = NO_FAULT;
uint8_t mot_Y_Phase_SC_FLT  = NO_FAULT;
uint8_t mot_B_Phase_SC_FLT  = NO_FAULT;
uint8_t mot_Phase_SC_FLT  = NO_FAULT;
uint8_t mot_Stall_FLT     = NO_FAULT;
uint8_t mot_OT_FLT        = NO_FAULT;
uint8_t inv_OT_FLT        = NO_FAULT;
uint8_t soft_SC_FLT       = NO_FAULT;

/* Run_Time_Sensor_HLTH_Moni Variable */
uint8_t inv_R_Ph_V_Sens_FLT       = NO_FAULT;
uint8_t inv_Y_Ph_V_Sens_FLT       = NO_FAULT;
uint8_t inv_B_Ph_V_Sens_FLT       = NO_FAULT;
uint8_t dc_BUS_V_Sens_FLT         = NO_FAULT;
uint8_t inv_R_Ph_I_Sens_FLT       = NO_FAULT;
uint8_t inv_Y_Ph_I_Sens_FLT       = NO_FAULT;
uint8_t inv_B_Ph_I_Sens_FLT       = NO_FAULT;
uint8_t dc_BUS_I_Sens_FLT         = NO_FAULT;
uint8_t tps1_V_Sens_FLT           = NO_FAULT;
uint8_t tps2_V_Sens_FLT	          = NO_FAULT;
uint8_t inv_R_Ph_Temp_Sens_FLT    = NO_FAULT;
uint8_t inv_Y_Ph_Temp_Sens_FLT    = NO_FAULT;
uint8_t inv_B_Ph_Temp_Sens_FLT    = NO_FAULT;
uint8_t mot_Temp_Sens_FLT	  = NO_FAULT;

/* Stal Protection Variable */
uint8_t stall_Prot_FLT 		  = NO_FAULT;
uint8_t soft_FLT		  = NO_FAULT;
uint16_t stall_Prot_DB_Cnt 	  = CLEAR;

/* Phse Open Fault */
uint8_t ph_Open_FLT = 0;
uint8_t aPH_Open_FLT = 0;
uint8_t bPH_Open_FLT = 0;
uint8_t cPH_Open_FLT = 0;
uint16_t aPH_Open_DB_Cnt = 0;
uint16_t bPH_Open_DB_Cnt = 0;
uint16_t cPH_Open_DB_Cnt = 0;
 
uint8_t rest_ON = 1; 		/* Inilization Should Be 1 */
uint8_t rst_ON_UV = 1;		/* Inilization Should Be 1 */
uint8_t rst_ON_OV = 1; 		/* Inilization Should Be 1 */
uint8_t man_FLT_CLRed = 0;
uint8_t flt_CLR = 0;

uint8_t other_FLT = 0;
uint8_t volt_FLT_CLR = 0;
 
uint8_t high_Level_FLT = 0;
uint8_t crus_FLT_STAT = 0;

uint8_t dc_OV_Volt_FLT = 0;
uint8_t dc_UV_Volt_FLT = 0;
uint8_t dc_OC_FLT = 0;
uint8_t ph_I_OC_FLT = 0;
uint8_t over_SPEED_FLT = 0;
uint8_t over_MOT_TEMP_FLT = 0;
uint8_t over_INV_TEMP_FLT = 0;
 
uint16_t dc_OV_DB_Cnt = 0;
uint16_t dc_UV_DB_Cnt = 0;
uint16_t dc_I_RMS_DB_Cnt = 0;
uint16_t rPH_I_RMS_DB_Cnt = 0;
uint16_t yPH_I_RMS_DB_Cnt = 0;
uint16_t bPH_I_RMS_DB_Cnt = 0;
uint16_t speed_DB_Cnt = 0;
uint16_t mot_Temp_DB_Cnt = 0;
uint16_t inv_rPH_Temp_DB_Cnt = 0;
uint16_t inv_yPH_Temp_DB_Cnt = 0;
uint16_t inv_bPH_Temp_DB_Cnt = 0;

uint8_t rPH_I_OC_FLT = 0;
uint8_t yPH_I_OC_FLT = 0;
uint8_t bPH_I_OC_FLT = 0;
uint8_t inv_rPH_TEMP_FLT = 0;
uint8_t inv_yPH_TEMP_FLT = 0;
uint8_t inv_bPH_TEMP_FLT = 0;
uint8_t man_HLTH_FLT_CLR = 0;
 
uint16_t auto_Fault_CLR_Time = 0;

/* LIMBHOME Mode */
uint8_t limpHome_Mode_Sens_STAT = 0;


/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Sensor_Health_Check(void)
{
	/* Current Sensor Health Check */
        if( (ac_R_Ph_I > MAX_I_SENS_HLTH_LIMI) || (ac_R_Ph_I < MIN_I_SENS_HLTH_LIMI) )
        {
            ac_I_R_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            ac_I_R_Sens_HLTH_FLT = NO_FAULT;
        }
        if( (ac_Y_Ph_I > MAX_I_SENS_HLTH_LIMI) || (ac_Y_Ph_I < MIN_I_SENS_HLTH_LIMI) )
        {
            ac_I_Y_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            ac_I_Y_Sens_HLTH_FLT = NO_FAULT;
        }
        if( (ac_B_Ph_I > MAX_I_SENS_HLTH_LIMI) || (ac_B_Ph_I < MIN_I_SENS_HLTH_LIMI) )
        {
            ac_I_B_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            ac_I_B_Sens_HLTH_FLT = NO_FAULT;
        }
        if( (dc_Bus_I > MAX_I_SENS_HLTH_LIMI) || (dc_Bus_I < MIN_I_SENS_HLTH_LIMI) )
        {
            dc_I_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            dc_I_Sens_HLTH_FLT = NO_FAULT;
        }

	if( ( (ac_I_R_Sens_HLTH_FLT == FAULT) || (ac_I_Y_Sens_HLTH_FLT == FAULT) ) || ( (ac_I_B_Sens_HLTH_FLT == FAULT) || (dc_I_Sens_HLTH_FLT == FAULT) ) )
	{
		cur_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		cur_Sens_HLTH_FLT = NO_FAULT;
	}
	/* Dc Bus Voltage_monitor */
	//if( (dc_Bus_V <= MIN_DCV_SENS_HLTH_LIMI) || (dc_Bus_V >= MAX_DCV_SENS_HLTH_LIMI) )
	if(dc_Bus_V >= MAX_DCV_SENS_HLTH_LIMI)/* DC V circuit dont have negative value, when power is ON from 12VorDC_Source, have 0Vcnt or actual voltage count, so I consider positve short limit(Max Limit) */
	{
		dc_V_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		dc_V_Sens_HLTH_FLT = NO_FAULT;
	}
	
	/* Phase Voltage_monitor */	
	
	if( (ac_R_Ph_V < MIN_PHV_SENS_HLTH_LIMI) || (ac_R_Ph_V >= MAX_PHV_SENS_HLTH_LIMI) )
	{
		//ac_V_R_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		ac_V_R_Sens_HLTH_FLT = NO_FAULT;
	}
	if( (ac_Y_Ph_V < MIN_PHV_SENS_HLTH_LIMI) || (ac_Y_Ph_V >= MAX_PHV_SENS_HLTH_LIMI) )
	{
		//ac_V_Y_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		ac_V_Y_Sens_HLTH_FLT = NO_FAULT;
	}
	if( (ac_B_Ph_V < MIN_PHV_SENS_HLTH_LIMI) || (ac_B_Ph_V >= MAX_PHV_SENS_HLTH_LIMI) )
	{
		//ac_V_B_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		ac_V_B_Sens_HLTH_FLT = NO_FAULT;
	}
	
	if( ( (ac_V_R_Sens_HLTH_FLT == FAULT) || (ac_V_Y_Sens_HLTH_FLT == FAULT) ) || ( (ac_V_B_Sens_HLTH_FLT == FAULT) || (dc_V_Sens_HLTH_FLT == FAULT) ) )
	{
		volt_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		volt_Sens_HLTH_FLT = NO_FAULT;
	}	
	
	/* These Fault is Also Avaliable In Run Time Also */
	/* Hall Sensor Check */
	if( ( (hall_A == 1) && (hall_B == 1) && (hall_C == 1) ) || ( (hall_A == 0) && (hall_B == 0) && (hall_C == 0) ) )
	{
		hall_Sens_FLT = FAULT;
	}
	else
	{
		hall_Sens_FLT = NO_FAULT;
	}
	/* TPS Sensor Signal Health Check */
        if( (tps1_V_Cnt > MAX_TPS_SENS_HLTH_LIMI) || (tps1_V_Cnt < MIN_TPS_SENS_HLTH_LIMI) )
        {
		tps1_Sens_HLTH_FLT = FAULT;
        }
	else
	{
		tps1_Sens_HLTH_FLT = NO_FAULT;
	}
        if( (tps2_V_Cnt > MAX_TPS_SENS_HLTH_LIMI) || (tps2_V_Cnt < MIN_TPS_SENS_HLTH_LIMI) )
        {
            	//tps2_Sens_HLTH_FLT = FAULT;/* Not Used in Hardware */
        }
	else
	{
            	//tps2_Sens_HLTH_FLT = NO_FAULT;/* Not Used in Hardware */
	}
	
	/* Auxilary Power Supply Signal Check */
	if(  (mon_15V > MAX_15V_POWER_SUPPLY_LIMIT) || (mon_15V < MIN_15V_POWER_SUPPLY_LIMIT) )
	{
		pGood_15V_FLT = FAULT;
	}
	else
	{
		pGood_15V_FLT = NO_FAULT;
	}
	
	if(  (mon_5V > MAX_5V_POWER_SUPPLY_LIMIT) || (mon_5V < MIN_5V_POWER_SUPPLY_LIMIT) )
	{
		pGood_5V_FLT = FAULT;
	}
	else
	{
		pGood_5V_FLT = NO_FAULT;
	}
	
	if(  (mon_TPS_5V > MAX_5V_POWER_SUPPLY_LIMIT) || (mon_TPS_5V < MIN_5V_POWER_SUPPLY_LIMIT) )
	{
		pGood_TPS_5V_FLT = FAULT;
	}
	else
	{
		pGood_TPS_5V_FLT = NO_FAULT;
	}

	
	/* Over All TPS & Auxilary Supply Fault */
	if( (tps1_Sens_HLTH_FLT == FAULT) || (tps2_Sens_HLTH_FLT == FAULT) )
	{
		tps_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		tps_Sens_HLTH_FLT = NO_FAULT;
	}
	if( (pGood_5V_FLT == FAULT) || (pGood_TPS_5V_FLT == FAULT) )
	{
		//ps_Sens_HLTH_FLT = FAULT; /* not tested */
	}

        

        /* Motor Temperature Sensor Health Check */ 
        if( (motor_Temp_V > MAX_MOT_NTC_SENS_HLTH_LIMI) || (motor_Temp_V < MIN_MOT_NTC_SENS_HLTH_LIMI) )
        {
            	mot_NTC_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            	mot_NTC_Sens_HLTH_FLT = NO_FAULT;
        }

        /* Inverter Temperature Sensor Health Check */
        if( (inv_R_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_R_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_R_Ph_Temp_Sens_HLTH_FLT = FAULT;
        }
	else
	{
		inv_R_Ph_Temp_Sens_HLTH_FLT = NO_FAULT;
	}
	
        if( (inv_Y_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_Y_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_Y_Ph_Temp_Sens_HLTH_FLT = FAULT;
        }
	else
	{
		inv_Y_Ph_Temp_Sens_HLTH_FLT = NO_FAULT;
	}
	
        if( (inv_B_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_B_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_B_Ph_Temp_Sens_HLTH_FLT = FAULT;
        }
	else
	{
		inv_B_Ph_Temp_Sens_HLTH_FLT = NO_FAULT;
	}
	
		
	/* Over All Temperature Fault */
	if( ((mot_NTC_Sens_HLTH_FLT == FAULT) || (inv_R_Ph_Temp_Sens_HLTH_FLT == FAULT)) || ((inv_Y_Ph_Temp_Sens_HLTH_FLT == FAULT) || (inv_B_Ph_Temp_Sens_HLTH_FLT == FAULT)) )
	{
		temp_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		temp_Sens_HLTH_FLT = NO_FAULT;
	}
	
	
	//	Sensor_Run_Time_Moni();
		
	/* Over All Sens Health Fault */
	if( (cur_Sens_HLTH_FLT == FAULT) || (volt_Sens_HLTH_FLT == FAULT) || (hall_Sens_FLT == FAULT) || (ps_Sens_HLTH_FLT == FAULT) || (tps_Sens_HLTH_FLT == FAULT) || (temp_Sens_HLTH_FLT == FAULT) )
	{
		sens_HLTH_FLT = FAULT;
	}
	else
	{
		sens_HLTH_FLT = NO_FAULT;
	}	
//	/* Over All Sens Health Fault */
//	if( ((cur_Sens_HLTH_FLT == FAULT) || (volt_Sens_HLTH_FLT == FAULT)))
//	{
//		sens_HLTH_FLT = FAULT;
//	}
//	else
//	{
//		sens_HLTH_FLT = NO_FAULT;
//	}
   
	/* LIMBHOME MODE */
//OLD ONEif( (ac_I_B_Sens_HLTH_FLT == FAULT) || (dc_I_Sens_HLTH_FLT == FAULT) || (temp_Sens_HLTH_FLT == FAULT) || (dc_V_Sens_HLTH_FLT == FAULT) || (side_Stand == ACTIVATE) )
	if( (ac_I_B_Sens_HLTH_FLT == FAULT) || (dc_I_Sens_HLTH_FLT == FAULT) || (temp_Sens_HLTH_FLT == FAULT) || (dc_V_Sens_HLTH_FLT == FAULT) )
	{
		limpHome_Mode_Sens_STAT = ACTIVATE;
	}
	else
	{
		limpHome_Mode_Sens_STAT = DEACTIVATE;
	}
	
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Sensor_Run_Time_Moni(void)
{
	/* This Condition for used to when vehicle is turn on but Side stand is not deactivte or DC voltage is readed at health check time limpHome_Mode_Sens_STAT flag is enabled, but Physically Health is Ok
		thats why before vehicle Run codition checked Health is Ok or Not 
		Consider this condition Name is "CON1"
	*/
	if( (speed_RPM == 0) && (vehi_INI_Run_Stat == 0) )
	{
    //OLD One   if(((dc_V_Sens_HLTH_FLT == NO_FAULT) || ((dc_V_Sens_HLTH_FLT == FAULT) && (dc_Bus_V >= MIN_DCV_SENS_HLTH_LIMI) && (dc_Bus_V <= MAX_DCV_SENS_HLTH_LIMI) ))&&((side_Stand == DEACTIVATE) && (ss_ReadTime_Cnt > 5000) && (limpHome_Mode_Sens_STAT == ACTIVATE)))
		if(((dc_V_Sens_HLTH_FLT == NO_FAULT) || ((dc_V_Sens_HLTH_FLT == FAULT) && (dc_Bus_V >= MIN_DCV_SENS_HLTH_LIMI) && (dc_Bus_V <= MAX_DCV_SENS_HLTH_LIMI) ))&&((ss_ReadTime_Cnt > 5000) && (limpHome_Mode_Sens_STAT == ACTIVATE)))
		{
			dc_V_Sens_HLTH_FLT = DEACTIVATE;
			limpHome_Mode_Sens_STAT = DEACTIVATE;
			sens_HLTH_OK_FLG = 1;
			ss_ReadTime_Cnt = 5001;
		}
	}
	else if(speed_RPM != 0)
	{
		vehi_INI_Run_Stat = 1;
	}
		
		
	
	/* Hall Sensor Check */
	if( ( (hall_A == 1) && (hall_B == 1) && (hall_C == 1) ) || ( (hall_A == 0) && (hall_B == 0) && (hall_C == 0) ) )
	{
		hall_Debouns_Cnt++;
		if(hall_Debouns_Cnt >= HALL_DEBOUNCE)
		{
			hall_Sens_FLT = FAULT;			/* High level Fault */
			hall_Sens_FLT_CLR = 0;
		}
	}
	else
	{
			hall_Debouns_Cnt = 0;
			hall_Sens_FLT_CLR = 1;
	}
		
	
	/* TPS Sensor Signal Health Check */
        if( (tps1_V_Cnt > MAX_TPS_SENS_HLTH_LIMI) || (tps1_V_Cnt < MIN_TPS_SENS_HLTH_LIMI) )
        {
		tps1_DB_Cnt++;
		if(tps1_DB_Cnt >= TPS_DEBOUNCE)
		{
			tps1_Sens_HLTH_FLT = FAULT;
		}
        }
	else
	{
		tps1_DB_Cnt =0;
	}
        if( (tps2_V_Cnt > MAX_TPS_SENS_HLTH_LIMI) || (tps2_V_Cnt < MIN_TPS_SENS_HLTH_LIMI) )
        {
		tps2_DB_Cnt++;
		if(tps2_DB_Cnt >= TPS_DEBOUNCE)
		{
            		//tps2_Sens_HLTH_FLT = FAULT;/* Not Used IN Hardware */
		}
        }
	else
	{
		tps2_DB_Cnt = 0;
	}
	
	/* Auxilary Power Supply Signal Check */
	if(  (mon_15V > MAX_15V_POWER_SUPPLY_LIMIT) || (mon_15V < MIN_15V_POWER_SUPPLY_LIMIT) )
	{
		pGood_15V_DB_Cnt++;
		if(pGood_15V_DB_Cnt > VOLT_MON_DEBOUNCE)
		{
			pGood_15V_FLT = FAULT;
		}
	}
	else
	{
		pGood_15V_DB_Cnt = 0;
	}
	
	if(  (mon_5V > MAX_5V_POWER_SUPPLY_LIMIT) || (mon_5V < MIN_5V_POWER_SUPPLY_LIMIT) )
	{
		pGood_5V_DB_Cnt++;
		if(pGood_5V_DB_Cnt > VOLT_MON_DEBOUNCE)
		{
			pGood_5V_FLT = FAULT;
		}
	}
	else
	{
		pGood_5V_DB_Cnt = 0;
	}
	
	if(  (mon_TPS_5V > MAX_5V_POWER_SUPPLY_LIMIT) || (mon_TPS_5V < MIN_5V_POWER_SUPPLY_LIMIT) )
	{
		pGood_TPS_DB_Cnt++;
		if(pGood_TPS_DB_Cnt > VOLT_MON_DEBOUNCE)
		{
			pGood_TPS_5V_FLT = FAULT;
		}
	}
	else
	{
		pGood_TPS_DB_Cnt = 0;
	}

	
	/* Over All TPS & Auxilary Supply Fault */
	if( (tps1_Sens_HLTH_FLT == FAULT) || (tps2_Sens_HLTH_FLT == FAULT) )
	{
		tps_Sens_HLTH_FLT = FAULT;
	}
	else
	{
		tps_Sens_HLTH_FLT = NO_FAULT;
	}
	if( (pGood_15V_FLT == FAULT) || (pGood_5V_FLT == FAULT) || (pGood_TPS_5V_FLT == FAULT) )
	{
		//ps_Sens_HLTH_FLT = FAULT; /* not tested */
	}

        

        /* Motor Temperature Sensor Health Check */ 
        if( (motor_Temp_V > MAX_MOT_NTC_SENS_HLTH_LIMI) || (motor_Temp_V < MIN_MOT_NTC_SENS_HLTH_LIMI) )
        {
            mot_NTC_Sens_HLTH_FLT = FAULT;
        }
        else
        {
            mot_NTC_Sens_HLTH_FLT = NO_FAULT;
        }

        /* Inverter Temperature Sensor Health Check */
        if( (inv_R_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_R_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_R_Temp_HLT_DB_Cnt++;
		if(inv_R_Temp_HLT_DB_Cnt > INV_TEMP_HLT_DEBOUNCE)
		{
			inv_R_Ph_Temp_Sens_HLTH_FLT = FAULT;
		}
        }
	else
	{
		inv_R_Temp_HLT_DB_Cnt = 0;
	}
	
        if( (inv_Y_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_Y_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_Y_Temp_HLT_DB_Cnt++;
		if(inv_Y_Temp_HLT_DB_Cnt > INV_TEMP_HLT_DEBOUNCE)
		{
            		inv_Y_Ph_Temp_Sens_HLTH_FLT = FAULT;
		}
        }
	else
	{
		inv_Y_Temp_HLT_DB_Cnt = 0;
	}
	
        if( (inv_B_Ph_Temp_V < MAX_INV_TEMP_SENS_HLTH_LIMI) || (inv_B_Ph_Temp_V > MIN_INV_TEMP_SENS_HLTH_LIMI) )
        {
		inv_B_Temp_HLT_DB_Cnt++;
		if(inv_B_Temp_HLT_DB_Cnt > INV_TEMP_HLT_DEBOUNCE)
		{
			inv_B_Ph_Temp_Sens_HLTH_FLT = FAULT;
		}
        }
	else
	{
		inv_B_Temp_HLT_DB_Cnt = 0;
	}
		
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
	if( (tps_Sens_HLTH_FLT == FAULT ) || (ps_Sens_HLTH_FLT == FAULT) || (temp_Sens_HLTH_FLT == FAULT) )
	{
		run_Time_Fault = FAULT;
	}
	else
	{
		run_Time_Fault = NO_FAULT;
	}
		
	
}

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Hardware_Fault_Moni(void)
{
	HW_FLT_Sign_Read();
	if(sht_FLT_Sign == 1)
	{
		sht_FLT = FAULT;
	}
	
	if(ocp_FLT_Sign == 1)
	{
		ocp_FLT = FAULT;
	}
	
	if( (sht_FLT == FAULT) || (ocp_FLT == FAULT) )
	{
		//hrd_FLT = FAULT; /* Not verfied */
	}
	else
	{
		hrd_FLT = NO_FAULT;
	}
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Software_Fault_Monitor(void)
{
            /* DC Bus Short Circuit Current Monitor */
            if( (dc_I_CTR_Cnt_DF >= MAX_DC_BUS_SC_LIMIT) || (dc_Bus_I <= MIN_DC_BUS_SC_LIMIT) )
	    {
		    dc_I_SC_DB_Cnt++;
		    if(dc_I_SC_DB_Cnt > DC_I_SC_DEBOUNCE)
		    {
                    	dc_BUS_SC_FLT = FAULT;
		    }
            }
	    else 
	    {
		    dc_I_SC_DB_Cnt= 0;
	    }
    
            /* Phase Short Circuit Current Monitor */
            if( (ac_R_Ph_I >= MAX_PHASE_SC_LIMIT) || (ac_R_Ph_I <= MIN_PHASE_SC_LIMIT) )
	    {
		    ac_R_PH_SC_DB_Cnt++;
		    if(ac_R_PH_SC_DB_Cnt > PH_I_SC_DEBOUNCE)
		    {
                    	mot_R_Phase_SC_FLT = FAULT;
		    }
            }
	    else 
	    {
		    ac_R_PH_SC_DB_Cnt= 0;
	    }
            if( (ac_Y_Ph_I >= ( MAX_PHASE_SC_LIMIT)) || (ac_Y_Ph_I <= MIN_PHASE_SC_LIMIT) )//(-1700)
	    {
		    ac_Y_PH_SC_DB_Cnt++;
		    if(ac_Y_PH_SC_DB_Cnt > PH_I_SC_DEBOUNCE)
		    {
                    	mot_Y_Phase_SC_FLT = FAULT;
		    }
            }
	    else
	    {
		    mot_Y_Phase_SC_FLT = 0;
	    }
            if( (ac_B_Ph_I >= MAX_PHASE_SC_LIMIT) || (ac_B_Ph_I <= MIN_PHASE_SC_LIMIT) )
	    {
		    ac_B_PH_SC_DB_Cnt++;
		    if(ac_B_PH_SC_DB_Cnt > PH_I_SC_DEBOUNCE)
		    {
                    	mot_B_Phase_SC_FLT = FAULT;
		    }
            }
	    else
	    {
		    ac_B_PH_SC_DB_Cnt = 0;
	    }
	    if(((mot_R_Phase_SC_FLT == FAULT) || (mot_Y_Phase_SC_FLT == FAULT)) || (mot_B_Phase_SC_FLT == FAULT))
	    {
		    mot_Phase_SC_FLT = FAULT;
	    }
	    else
	    {
		    mot_Phase_SC_FLT = NO_FAULT;
	    }
	    
	    if( ( (dc_BUS_SC_FLT == FAULT) || (mot_R_Phase_SC_FLT == FAULT)) || ( (mot_Y_Phase_SC_FLT == FAULT) || (mot_B_Phase_SC_FLT == FAULT)) )
	    {
		    soft_SC_FLT = FAULT;		/* High level Fault */
	    }
	    else
	    {
		    soft_SC_FLT = NO_FAULT;
	    }
		    
    
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Stall_Protection(void)
{
    if( (speed_RPM <= STAL_PROT_SPEED_LIMIT) && (throttle_Read >= STAL_Is_LIMIT) && (dc_I_RMS >= STAL_PROT_DC_I_LIMIT) )
    {
	stall_Prot_DB_Cnt++;
	if(stall_Prot_DB_Cnt > STALL_DEBOUNCE)
	{
		stall_Prot_FLT = FAULT;
	}
    }
    else
    {
        stall_Prot_DB_Cnt = 0;
    }
    if( (sens_HLTH_FLT == 1) || (run_Time_Fault == 1) || (hrd_FLT == 1) || (stall_Prot_FLT == 1) )
    {
        soft_FLT = 1;
    }
    else
    {
        soft_FLT = 0;
    }

}

void Motor_Protection(void)
{
    /* DC_Voltage Protection */
    if(dcVolt_ACT > DC_V_MAX_LIMIT)
    {
	    dc_OV_DB_Cnt++;
	    if(dc_OV_DB_Cnt > DC_V_DEBOUNCE)
	    {
	            dc_OV_Volt_FLT = 1;
	    }
    }
    else 
    {
	    dc_OV_DB_Cnt = 0;
    }
    
    if( (dcVolt_ACT < DC_V_MIN_LIMIT) )
    {
	    
	    dc_UV_DB_Cnt++;
	    if(dc_UV_DB_Cnt > DC_V_DEBOUNCE)
	    {
			dc_UV_Volt_FLT = 1;
	    }
    }
    else 
    {
	    dc_UV_DB_Cnt = 0;    
    }
    if( (dcVolt_ACT < DC_V_MAX_LIMIT) && (dcVolt_ACT > DC_V_MIN_LIMIT) )
    {
            volt_FLT_CLR = 1;
    }
    else
    {
            volt_FLT_CLR = 0;
    }    
    
    if(dc_I_RMS > DC_I_MAX_LIMIT)
    {
	    dc_I_RMS_DB_Cnt++;
	    if(dc_I_RMS_DB_Cnt > DC_I_RMS_DEBOUNCE)
	    {
		    dc_OC_FLT = 1;
	    }
    }
    else
    {
	    dc_I_RMS_DB_Cnt = 0;
    }
    
    /* Phase Current */
    if(aPH_I_ACT_RMS > PHASE_I_MAX_LIMIT)
    {
	    rPH_I_RMS_DB_Cnt++;
	    if(rPH_I_RMS_DB_Cnt > PH_I_RMS_DEBOUNCE)
	    {
		    rPH_I_OC_FLT = FAULT;
	    }
    }
    else
    {
	    rPH_I_RMS_DB_Cnt = 0;
    }
    if(bPH_I_ACT_RMS > PHASE_I_MAX_LIMIT)
    {
	    yPH_I_RMS_DB_Cnt++;
	    if(yPH_I_RMS_DB_Cnt > PH_I_RMS_DEBOUNCE)
	    {
		    yPH_I_OC_FLT = FAULT;
	    }
    }
    else
    {
	    yPH_I_RMS_DB_Cnt = 0;
    }
    if(cPH_I_ACT_RMS > PHASE_I_MAX_LIMIT)
    {
	    bPH_I_RMS_DB_Cnt++;
	    if(bPH_I_RMS_DB_Cnt > PH_I_RMS_DEBOUNCE)
	    {
		    bPH_I_OC_FLT = FAULT;
	    }
    }
    else
    {
	    bPH_I_RMS_DB_Cnt = 0;
    }
    if((rPH_I_OC_FLT == FAULT) || (yPH_I_OC_FLT == FAULT) || (bPH_I_OC_FLT == FAULT))
    {
        ph_I_OC_FLT = 1;
    }
	   
    
    
    if(speed_RPM > SPEED_MAX_LIMIT)
    {
	    speed_DB_Cnt++;
	    if(speed_DB_Cnt > SPEED_DEBOUNCE)
	    {
		    over_SPEED_FLT = 1;
	    }
    }
    else
    {
	    speed_DB_Cnt = 0;
    }
	if(motor_Temp_V <= MOT_TEMP_MAX_LIMIT) 
	{
		mot_Temp_DB_Cnt++;
		if(mot_Temp_DB_Cnt > INV_TEMP_DEBOUNCE)
		{
			over_MOT_TEMP_FLT = FAULT;
		}
	}
	else
	{
		mot_Temp_DB_Cnt = 0;
	}
	
   
	if(inv_R_Ph_Temp_V < INV_TEMP_MAX_LIMIT)
	{
		inv_rPH_Temp_DB_Cnt++;
		if(inv_rPH_Temp_DB_Cnt > INV_TEMP_DEBOUNCE)
		{
			inv_rPH_TEMP_FLT = FAULT;
		}
	}
	else
	{
		inv_rPH_Temp_DB_Cnt = 0;
	}
   
	if(inv_Y_Ph_Temp_V < INV_TEMP_MAX_LIMIT)
	{
		inv_yPH_Temp_DB_Cnt++;
		if(inv_yPH_Temp_DB_Cnt > INV_TEMP_DEBOUNCE)
		{
			inv_yPH_TEMP_FLT = FAULT;
		}
	}
	else
	{
		inv_yPH_Temp_DB_Cnt = 0;
	}
   
	if(inv_B_Ph_Temp_V < INV_TEMP_MAX_LIMIT)
	{
		inv_bPH_Temp_DB_Cnt++;
		if(inv_bPH_Temp_DB_Cnt > INV_TEMP_DEBOUNCE)
		{
			inv_bPH_TEMP_FLT = FAULT;
		}
	}
	else
	{
		inv_bPH_Temp_DB_Cnt = 0;
	}
	if( (inv_rPH_TEMP_FLT == FAULT)  || (inv_yPH_TEMP_FLT == FAULT) || (inv_bPH_TEMP_FLT == FAULT) )
	{
        	over_INV_TEMP_FLT = 1;
	}
	


	/* Phase Open Fault check */
	if((aPH_I_ACT_RMS > 5) && (bPH_I_ACT_RMS > 5) && (cPH_I_ACT_RMS == 0))
	{
		cPH_Open_DB_Cnt++;
		if(cPH_Open_DB_Cnt >= PH_OPN_DEBOUNCE)
		{
			cPH_Open_FLT = FAULT;
		}
	}
	else
	{
		cPH_Open_DB_Cnt = 0;
	}
	if((bPH_I_ACT_RMS > 5) && (cPH_I_ACT_RMS > 5) && (aPH_I_ACT_RMS == 0))
	{
		aPH_Open_DB_Cnt++;
		if(aPH_Open_DB_Cnt >= PH_OPN_DEBOUNCE)
		{
			aPH_Open_FLT = FAULT;
		}
	}
	else
	{
		aPH_Open_DB_Cnt = 0;
	}
	if((cPH_I_ACT_RMS > 5) && (aPH_I_ACT_RMS > 5) && (bPH_I_ACT_RMS == 0))
	{
		bPH_Open_DB_Cnt++;
		if(bPH_Open_DB_Cnt >= PH_OPN_DEBOUNCE)
		{
			bPH_Open_FLT = FAULT;
		}
	}
	else
	{
		bPH_Open_DB_Cnt = 0;
	}
	if( (aPH_Open_FLT == FAULT) || (bPH_Open_FLT == FAULT) || (cPH_Open_FLT == FAULT) )
	{
		//ph_Open_FLT = FAULT;
	}

    
    
    
   if( ( ( ( (dc_OC_FLT == 1) || (dc_UV_Volt_FLT == 1) ) ||(  ( ( (dc_OV_Volt_FLT == 1) || (ph_I_OC_FLT == 1)) || (over_SPEED_FLT == 1)) || ( (over_MOT_TEMP_FLT == 1) || (over_INV_TEMP_FLT == 1)) || (ph_Open_FLT == 1) )) || (soft_FLT == 1) || (soft_SC_FLT == 1) || (hall_Sens_FLT == 1) ) )
    {
	    if( ( ( ( (dc_OC_FLT == 1) || (ph_I_OC_FLT == 1)) || ( (over_SPEED_FLT == 1)) || (over_MOT_TEMP_FLT == 1)) || ( (over_INV_TEMP_FLT == 1) || (ph_Open_FLT == 1) || (soft_FLT == 1) || (soft_SC_FLT == FAULT))))
	    {
		    other_FLT = 1;
	    }
	    else
	    {
		    other_FLT = 0;
	    }
	if((soft_SC_FLT == 0) && (hall_Sens_FLT == 0) ) /* These Two fault is High Level Fault other fault is Low Level Fault, If high level Fault Come PWM turn Off,and Safe Mode, other fault only safe Mode */
	{
       		 flt_CLR = 1;
	}
	//auto_Fault_CLR_Time = 0;
    }
    
    /* DC Voltage Fault Only */	    
  if( ( ( (v_d == 0) && (v_q == 0) &&  (prote_Throt_Read == 0) && (speed_RPM == 0) )&& ( (volt_FLT_CLR == 1) || (hall_Sens_FLT_CLR == 1) ) ) && (other_FLT == 0))
   {
	//   auto_Fault_CLR_Time++;
	//if(auto_Fault_CLR_Time >= 1500)/* 0.15s*/ /* wait for 0.15s to clear the fault if physically ok condition */
	{
		if(volt_FLT_CLR == 1)
		{
		        dc_OV_Volt_FLT = 0;
		        dc_UV_Volt_FLT = 0;
		}
		if(hall_Sens_FLT_CLR == 1)
		{
			hall_Sens_FLT = 0;
		}
		if( (volt_FLT_CLR == 1) && (hall_Sens_FLT_CLR == 1))
		{
		        volt_FLT_CLR = 0;
			hall_Sens_FLT_CLR= 0;
		        flt_CLR = 0;
		}
		
			
		auto_Fault_CLR_Time = 0;	
	}
   }
   /* Initial Time Limphome mode FLT Manual Clear */
   /* Sensor_Run_Time_Moni() at CON1 is enbled means Manually rest the Fault, so That process is done by below Condition */
   if((sens_HLTH_OK_FLG == 1) && (v_d == 0) && (v_q == 0) && (prote_Throt_Read == 0) && (speed_RPM == 0) && (man_HLTH_FLT_CLR == 0))
   {
		man_HLTH_FLT_CLR = 1;
		sens_HLTH_FLT = 0;
	        flt_CLR = 0;
		volt_Sens_HLTH_FLT = 0;
		sens_HLTH_FLT = 0;
   }
	   
	      
    
    if( (v_d == 0) && (v_q == 0) && (prote_Throt_Read == 0) && (speed_RPM == 0) &&  (man_FLT_CLRed == 1))
    {
	/* Protection Fault Clear */
        dc_OV_Volt_FLT = 0;
        dc_UV_Volt_FLT = 0;
        dc_OC_FLT = 0;
        ph_I_OC_FLT = 0;
        over_MOT_TEMP_FLT = 0;
        over_INV_TEMP_FLT = 0;
	over_SPEED_FLT = 0;
	
	ph_Open_FLT = 0;
	aPH_Open_FLT = 0;
	bPH_Open_FLT = 0;
	cPH_Open_FLT = 0;
	
        man_FLT_CLRed = 0;
        flt_CLR = 0;
	soft_SC_FLT = 0;
	
	/* Run Time Fault Clear */
	hall_Sens_FLT = 0;
    	tps1_Sens_HLTH_FLT = 0;
        tps2_Sens_HLTH_FLT = 0;
	pGood_5V_FLT = 0;
	pGood_TPS_5V_FLT = 0;
	mot_NTC_Sens_HLTH_FLT = 0;
	inv_R_Ph_Temp_Sens_HLTH_FLT = 0;
	inv_Y_Ph_Temp_Sens_HLTH_FLT = 0;
	inv_B_Ph_Temp_Sens_HLTH_FLT = 0;
	sht_FLT = 0;
	ocp_FLT = 0;
	/* Software Fault Clear */
        dc_BUS_SC_FLT = 0;
	mot_R_Phase_SC_FLT = 0;
	mot_Y_Phase_SC_FLT = 0;
	mot_B_Phase_SC_FLT = 0;
	/* Stall Fault Clear */
        stall_Prot_FLT = 0;
    }
    
    /* Cruse Mode Fault Status check */
    if((dc_OV_Volt_FLT == 1) || (dc_UV_Volt_FLT == 1) || (ph_I_OC_FLT == 1) || (dc_OC_FLT == 1) || (over_INV_TEMP_FLT == 1) || (over_MOT_TEMP_FLT == 1) || (soft_SC_FLT == FAULT) ||(soft_FLT == FAULT) )
    {
    	crus_FLT_STAT = ACTIVATE;
    }
    else
    {
    	crus_FLT_STAT = DEACTIVATE;
    }
	    
 
}

 