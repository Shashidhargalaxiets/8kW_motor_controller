#include "iodefine.h"
#include "ShortCircuitFault_Monitor.h"

extern int16_t iA_filteredCnt;
extern int16_t iB_filteredCnt;
extern int16_t iC_filteredCnt;

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


extern int16_t dc_I_CTR_Cnt_DF;
extern int16_t dc_Bus_I_Cnt;


void Software_Fault_Monitor(void)
{
    static uint16_t dc_I_SC_DB_Cnt = 0;
    static uint16_t ac_R_PH_SC_DB_Cnt = 0; 
    static uint16_t ac_Y_PH_SC_DB_Cnt = 0;
    static uint16_t ac_B_PH_SC_DB_Cnt = 0;

    /* DC Bus Short Circuit Current Monitor */
    FaultCheck_Debounced(&dc_BUS_SC_FLT, dc_I_CTR_Cnt_DF, MIN_DC_BUS_SC_LIMIT, MAX_DC_BUS_SC_LIMIT, DC_I_SC_DEBOUNCE, &dc_I_SC_DB_Cnt);

    /* Phase Short Circuit Current Monitor */    
    FaultCheck_Debounced(&mot_R_Phase_SC_FLT, iA_filteredCnt, MIN_PHASE_SC_LIMIT, MAX_PHASE_SC_LIMIT, PH_I_SC_DEBOUNCE, &ac_R_PH_SC_DB_Cnt);
    FaultCheck_Debounced(&mot_Y_Phase_SC_FLT, iB_filteredCnt, MIN_PHASE_SC_LIMIT, MAX_PHASE_SC_LIMIT, PH_I_SC_DEBOUNCE, &ac_Y_PH_SC_DB_Cnt);
    FaultCheck_Debounced(&mot_B_Phase_SC_FLT, iC_filteredCnt, MIN_PHASE_SC_LIMIT, MAX_PHASE_SC_LIMIT, PH_I_SC_DEBOUNCE, &ac_B_PH_SC_DB_Cnt);
	

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