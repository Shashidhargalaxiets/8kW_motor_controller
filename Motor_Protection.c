#include"iodefine.h"
#include"Motor_Protection.h"

extern SpeedParameters SpeedParams;
extern OpenLoopParameters OpenLpParam;

extern float dcVolt_ACT;
extern float dc_I_RMS;

extern int16_t iA_filteredCnt;
extern int16_t iB_filteredCnt;
extern int16_t iC_filteredCnt;

extern uint16_t inv_R_Ph_Temp_V;
extern uint16_t inv_Y_Ph_Temp_V;
extern uint16_t inv_B_Ph_Temp_V;

extern uint16_t motor_Temp_V;

uint8_t dc_OV_Volt_FLT = NO_FAULT;
uint8_t dc_UV_Volt_FLT = NO_FAULT;
uint8_t volt_FLT_CLR = NO_FAULT;
uint8_t dc_OC_FLT = NO_FAULT;
uint8_t rPH_I_OC_FLT = NO_FAULT;
uint8_t yPH_I_OC_FLT = NO_FAULT;
uint8_t bPH_I_OC_FLT = NO_FAULT;
uint8_t ph_I_OC_FLT = NO_FAULT;
uint8_t over_SPEED_FLT = NO_FAULT;
uint8_t over_MOT_TEMP_FLT = NO_FAULT;
uint8_t inv_rPH_TEMP_FLT = NO_FAULT;
uint8_t inv_yPH_TEMP_FLT = NO_FAULT;
uint8_t inv_bPH_TEMP_FLT = NO_FAULT;
uint8_t over_INV_TEMP_FLT = NO_FAULT;
uint8_t other_FLT = NO_FAULT;
uint8_t flt_CLR = NO_FAULT;
uint8_t Critical_Fault = NO_FAULT;

extern uint8_t sens_HLTH_FLT;
extern uint8_t sens_HLTH_OK_FLG;
extern uint8_t soft_FLT;
extern uint8_t soft_SC_FLT;
extern uint8_t Resolver_Sens_FLT;
extern uint8_t volt_Sens_HLTH_FLT;

int16_t test_values1[2000];

extern uint16_t flag1;
extern uint16_t count;

void Motor_Protection(void)
{
    static uint16_t dc_OV_DB_Cnt = 0;
    static uint16_t dc_UV_DB_Cnt = 0;
    static uint16_t dc_I_RMS_DB_Cnt = 0;
    static uint16_t rPH_I_RMS_DB_Cnt = 0;
    static uint16_t yPH_I_RMS_DB_Cnt = 0;
    static uint16_t bPH_I_RMS_DB_Cnt = 0;
    static uint16_t speed_DB_Cnt = 0;
    static uint16_t mot_Temp_DB_Cnt = 0;
    static uint16_t inv_rPH_Temp_DB_Cnt = 0;
    static uint16_t inv_yPH_Temp_DB_Cnt = 0;
    static uint16_t inv_bPH_Temp_DB_Cnt = 0;
    static uint16_t aPH_Open_DB_Cnt = 0;
    static uint16_t bPH_Open_DB_Cnt = 0;
    static uint16_t cPH_Open_DB_Cnt = 0;


	/* DC_Voltage Protection */

	FaultCheck_DebouncedGreaterThan(&dc_OV_Volt_FLT, (int16_t)dcVolt_ACT, DC_V_MAX_LIMIT, DC_V_DEBOUNCE, &dc_OV_DB_Cnt);
	FaultCheck_DebouncedLessThan(&dc_UV_Volt_FLT, (int16_t)dcVolt_ACT, DC_V_MIN_LIMIT, DC_V_DEBOUNCE, &dc_UV_DB_Cnt);


    if( (dcVolt_ACT < DC_V_MAX_LIMIT) && (dcVolt_ACT > DC_V_MIN_LIMIT) )
    {
            volt_FLT_CLR = 1;
    }
    else
    {
            volt_FLT_CLR = 0;
    }    

	FaultCheck_DebouncedGreaterThan(&dc_OC_FLT, (int16_t)dc_I_RMS, DC_I_MAX_LIMIT, DC_I_RMS_DEBOUNCE, &dc_I_RMS_DB_Cnt);

	
	FaultCheck_DebouncedGreaterThan(&rPH_I_OC_FLT, abs(iA_filteredCnt), PHASE_I_MAX_LIMIT, PH_I_RMS_DEBOUNCE, &rPH_I_RMS_DB_Cnt);
	FaultCheck_DebouncedGreaterThan(&yPH_I_OC_FLT, abs(iB_filteredCnt), PHASE_I_MAX_LIMIT, PH_I_RMS_DEBOUNCE, &yPH_I_RMS_DB_Cnt);
	FaultCheck_DebouncedGreaterThan(&bPH_I_OC_FLT, abs(iC_filteredCnt), PHASE_I_MAX_LIMIT, PH_I_RMS_DEBOUNCE, &bPH_I_RMS_DB_Cnt);



	if((rPH_I_OC_FLT == FAULT) || (yPH_I_OC_FLT == FAULT) || (bPH_I_OC_FLT == FAULT))
    {
        ph_I_OC_FLT = 1;
    }

	FaultCheck_DebouncedGreaterThan(&over_SPEED_FLT, (int16_t)SpeedParams.speed_measured_rpm, SPEED_MAX_LIMIT, SPEED_DEBOUNCE, &speed_DB_Cnt);
	
	
	FaultCheck_DebouncedLessThan(&over_MOT_TEMP_FLT, (int16_t)motor_Temp_V, MOT_TEMP_MAX_LIMIT, INV_TEMP_DEBOUNCE, &mot_Temp_DB_Cnt);
	FaultCheck_DebouncedLessThan(&inv_rPH_TEMP_FLT, (int16_t)inv_R_Ph_Temp_V, INV_TEMP_MAX_LIMIT, INV_TEMP_DEBOUNCE, &inv_rPH_Temp_DB_Cnt);
	FaultCheck_DebouncedLessThan(&inv_yPH_TEMP_FLT, (int16_t)inv_Y_Ph_Temp_V, INV_TEMP_MAX_LIMIT, INV_TEMP_DEBOUNCE, &inv_yPH_Temp_DB_Cnt);
	FaultCheck_DebouncedLessThan(&inv_bPH_TEMP_FLT, (int16_t)inv_B_Ph_Temp_V, INV_TEMP_MAX_LIMIT, INV_TEMP_DEBOUNCE, &inv_bPH_Temp_DB_Cnt);

	
	if( (inv_rPH_TEMP_FLT == FAULT)  || (inv_yPH_TEMP_FLT == FAULT) || (inv_bPH_TEMP_FLT == FAULT) )
	{
        	over_INV_TEMP_FLT = 1;
	}


    if( ( (dc_OC_FLT == 1) || (dc_UV_Volt_FLT == 1) ) ||(  ( ( (dc_OV_Volt_FLT == 1) || (ph_I_OC_FLT == 1)) || (over_SPEED_FLT == 1)) || ( (over_MOT_TEMP_FLT == 1) || (over_INV_TEMP_FLT == 1)) || (soft_FLT == 1) || (soft_SC_FLT == 1) || (Resolver_Sens_FLT == 1) ) )
    {
		if((dc_OC_FLT == 1) || (ph_I_OC_FLT == 1) || (over_SPEED_FLT == 1) || (soft_SC_FLT == 1) )
		{
			Critical_Fault = FAULT;
			//PORT.P10 = (1 << 10);	//setting pin to high
			//PWM_STOP();
		}
    }    
    
    if(count < 2000 && flag1 == 1)
	{       
		test_values1[count] = abs(iA_filteredCnt);
	}
	else
	{
		count = 0;
		flag1 = 0;
	}
}