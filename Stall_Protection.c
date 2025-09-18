#include"iodefine.h"
#include"Stall_Protection.h"

extern SpeedParameters SpeedParams;

extern uint8_t sens_HLTH_FLT;
extern uint8_t run_Time_Fault;
extern float dc_I_RMS;
extern float throttle_Read;

uint8_t stall_Prot_FLT 	    = NO_FAULT;
uint8_t soft_FLT		    = NO_FAULT;
uint16_t stall_Prot_DB_Cnt 	= 0;

void Stall_Protection(void)
{
    if( (SpeedParams.speed_measured_rpm <= STAL_PROT_SPEED_LIMIT) && (throttle_Read >= STAL_Is_LIMIT) && (dc_I_RMS >= STAL_PROT_DC_I_LIMIT) )
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
    if( (sens_HLTH_FLT == 1) || (run_Time_Fault == 1) || (stall_Prot_FLT == 1) )
    {
        soft_FLT = 1;
    }
    else
    {
        soft_FLT = 0;
    }

}