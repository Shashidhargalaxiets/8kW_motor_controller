
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "IO_Status.h"

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


extern uint8_t side_Stand_CAN;

extern uint8_t park_SW;
extern uint8_t break_Apply;
extern uint8_t forward_SW;
extern uint8_t mode_SW;
extern uint8_t eco_SW;
extern uint8_t side_Stand_Read;
extern uint8_t crus_SW;
extern uint8_t kill_SW;


extern uint16_t speed_RPM;
extern int16_t speed_Ref_SI;
extern uint16_t tps2_V_Cnt;
extern uint8_t crus_FLT_STAT;


extern int16_t throttle_Read_Act;
extern int16_t throttle_Read;

extern float id_MIN_LIM_MF;
extern int16_t Flux_MIN;
extern int16_t Torque_MAX;
extern uint16_t torque_SAT_MAX;
//extern uint16_t tps_FAST_RESP_CNT;

extern int16_t speed_Derat_Val;

extern uint16_t sys_Stabli_Time;

extern uint8_t limpHome_Mode_Sens_STAT;
extern int16_t crus_throttle_Read_Act;


extern uint8_t sleep_REQ_Latch;
extern uint8_t sens_HLTH_OK_FLG;
extern uint8_t vehicle_Not_Drivable;

/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/

uint8_t side_Stand = 0;
uint8_t ss_Act_Cnt = 0;
uint8_t ss_DeAct_Cnt = 0;
/* Mode_Change Variable */
uint8_t mode_Change = DEACTIVATE;
uint8_t mode_Sele_LCK = 0;

/* Ideal Mode Variable */


uint8_t modeSW_ON_Time_Cnt = 0;
uint8_t modeSW_Cnt = 0;
uint8_t mode_SW_Cnt = 0;

uint8_t sys_ON = DEACTIVATE;
uint8_t sys_ON_LATCH = DEACTIVATE;
uint8_t mode_SW_LATCH = DEACTIVATE;
uint8_t power_SW_Cnt = RST;

uint8_t park_SW_LATCH = DEACTIVATE;
uint8_t park_SW_Cnt = RST;
uint8_t park_SW_ON_Time_Cnt = RST;


uint8_t forward_SW_LATCH = DEACTIVATE;
uint8_t forward_Cnt = STEP_ONE;
uint8_t forwardSW_Cnt = RST;

uint8_t park_Mode = DEACTIVATE;
uint8_t power_Mode = DEACTIVATE;
uint8_t pre_Power_Mode = DEACTIVATE;
uint8_t parkSW_Cnt = RST;

uint8_t limpHome_Mode = DEACTIVATE;
uint8_t limp_Lock = 0;
uint8_t cruise_Mode = 0;

uint8_t forward_Mode = ACTIVATE;
uint8_t drive_Mode = DEACTIVATE;
uint8_t ideal_Mode = ACTIVATE;
uint8_t crus_MODE = DEACTIVATE;
uint8_t crus_Speed_Lock = DEACTIVATE;
uint8_t eco_Mode = DEACTIVATE;
uint8_t eco_SW_Latch = DEACTIVATE;

uint8_t crus_Lock = 0;
uint8_t pre_Power_Mode_Crus = 0;

uint16_t mode_Cnt = 0;
uint16_t mode_Cnt1 = 0;
uint16_t mode_TEST_Cnt = 0;
uint16_t mode_TEST_Cnt1 = 0;
uint32_t vehical_IO_Delay = 0;


/* Ideal Mode Variable */
uint16_t vehi_Ideal_Cnt = 0;
uint8_t vehi_Ideal_180s_Flg = 0;
uint8_t ideal_Mode_Time_Cnt = RST;


uint8_t MODE_CHECK_Tep = 0;

/* SS act after mode selection Variable */
uint8_t speed0_SS_Act_Mode = 0;
uint8_t speed0_SS_Act_Drive_Mode = 0;
uint8_t speed0_SS_Act_Park_Mode = 0;
uint8_t speed0_SS_Act_Power_Mode = 0;
uint8_t speed0_SS_Act_Forward_Mode = 0;

/* Test Purpose */
uint8_t ideal_Check = 0;
uint8_t mode_SW_Status = 5;
uint8_t park_SW_status = 5;
uint8_t break_Apply_Status = 5;
uint8_t mode_Change_Status = 5;
uint8_t side_Stand_Status = 5;


/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void IO_Read(void)
{
	Hall_Read();
	Analog_Read();
	Temp_Cal();
	Vehical_Input();
	if(sys_Stabli_Time > _250ms)/* Please check macro Name */
	{
		vehical_IO_Delay++;
		if(vehical_IO_Delay >_25ms) /* Please check macro Name */
		{
			vehical_IO_Delay = 0;
			Mode_Selection();
		}
	}
}
void Mode_Selection(void)
{
	/* Please note value of the variable with mode discripection 
		drive_Mode--It is ACTIVATE When either eco or power mode Activate
		power_Mode--If it is ACTIVATE Means Power mode is activate, DEACTIVATE Maeans Eco mode is activate
		park_Mode-- It is ACTIVATE When either park_forward_Mode and park_Reverse_Mode Activate
		forward_Mode-- If it is ACTIVATE Means Forward_Mode is activate, DEACTIVATE Mean Reverse mode is activate
	*/
	
	/* Side stand comman time consider */
	/* This is consider common, because all SS based consition wait for 0.2s thats whya we add common function */ 
	if((side_Stand_Read ==  ACTIVATE) || (side_Stand_CAN == ACTIVATE) )
	{
		ss_Act_Cnt++;
		if((ss_Act_Cnt >= _200ms) || (side_Stand_CAN == ACTIVATE) )/* 200ms for Hardware recerived signal,but SS signal from CAN already have Delay */
		{
			side_Stand = ACTIVATE;
			ss_Act_Cnt = 9;
			ss_DeAct_Cnt = 0;
		}
	}
	else if((side_Stand_Read == DEACTIVATE) || (side_Stand_CAN == DEACTIVATE) )
	{
		ss_DeAct_Cnt++;
		if((ss_DeAct_Cnt >= _200ms) || (side_Stand_CAN == DEACTIVATE) )/* 200ms for Hardware recerived signal,because SS signal from CAN already have Delay *//* 0.2 sec for Hardware recerived signal,because SS signal from CAN already have Delay */
		{
			side_Stand = DEACTIVATE;
			ss_DeAct_Cnt = 9;
			ss_Act_Cnt =0;
		}
	}
	
	
	/***************** Mode Change check ****************/
	/* This condition is common for all condition, that why add common variable */
	if( ( (speed_RPM <= _1KMPH) ) && ( (break_Apply == ACTIVATE) && (side_Stand == DEACTIVATE)))//&& (tps2_V_Cnt < MINIMUM_THROT)) )
	{
		mode_Change = ACTIVATE;
	}
	else
	{
		mode_Change = DEACTIVATE;
	}
	/* Initially before run motor "limpHome_Mode_Sens_STAT" flag is activate, mode selection also done, before run the motor "sens_HLTH_OK_FLG" Flag ia activate
		This Flag is activate only DC voltage sensor is OK means , so motor no need to run in Limphome mode, Run with drive mode thats why this condition used */
	if( (sens_HLTH_OK_FLG == 1) && (limpHome_Mode == ACTIVATE) && (mode_Sele_LCK == 0))
	{
		power_Mode = DEACTIVATE;	/* Power_Mode=Deactive Means Eco Mode Activate "Note: Eco Mode will activate when Drive Mode is activate"  */
		drive_Mode = ACTIVATE;
		park_Mode = DEACTIVATE;
		limpHome_Mode = DEACTIVATE;
		modeSW_Cnt = 1;
		speed_Ref_SI = ECO_FWD_SPEED_MAX;
		id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
		Flux_MIN = ECO_FLUX_MIN_LIM;
		Torque_MAX = ECO_TORQUE_MAX_LIM;
		torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
		//tps_FAST_RESP_CNT = DRV_TPS_FAST_RESP_LIM;
		speed_Derat_Val = DRV_ECO_SPEED_DERATE;
		mode_Sele_LCK = 1;
	}
		
	/***************** Power Mode/Eco Mode  ****************/
	/* Initial Limphome mode also selected by Mode selection Switch */
	if( ( (mode_SW == ACTIVATE) && (mode_Change == ACTIVATE) ) &&  ( ( (ideal_Mode == ACTIVATE) && (sys_ON_LATCH == DEACTIVATE))|| ( (park_Mode == ACTIVATE) && (drive_Mode == DEACTIVATE) ) ) )
	{
		modeSW_ON_Time_Cnt++;
		if((modeSW_ON_Time_Cnt >= _400ms)||((speed0_SS_Act_Mode==ACTIVATE)&&(modeSW_ON_Time_Cnt>=_200ms)))/* 16=0.4 Sec for normal operation*//*8=0.2sec if SS is activate after Mode select */
		{
				mode_SW_LATCH = ACTIVATE;
				forward_Mode = ACTIVATE;
				ideal_Mode = DEACTIVATE;
				ideal_Mode_Time_Cnt = RST;	
				park_SW_ON_Time_Cnt = RST;
				modeSW_Cnt = 1;
				/* Eco Mode */
			if((limpHome_Mode_Sens_STAT == DEACTIVATE)&&(speed0_SS_Act_Mode == DEACTIVATE))
			{
				power_Mode = DEACTIVATE;
				drive_Mode = ACTIVATE;
				park_Mode = DEACTIVATE;
				limpHome_Mode = DEACTIVATE;
				modeSW_Cnt = 1;
				speed_Ref_SI = ECO_FWD_SPEED_MAX;
				id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
				Flux_MIN = ECO_FLUX_MIN_LIM;
				Torque_MAX = ECO_TORQUE_MAX_LIM;
				torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
				speed_Derat_Val = DRV_ECO_SPEED_DERATE;
			}
			else if((limpHome_Mode_Sens_STAT == ACTIVATE)&&(speed0_SS_Act_Mode==DEACTIVATE))/* Limphome mode */
			{
				limpHome_Mode = ACTIVATE;
				power_Mode = DEACTIVATE;
				drive_Mode = DEACTIVATE;
				park_Mode = DEACTIVATE;
				speed_Ref_SI = LIMP_HOME_FWD_SPEED_MAX;
				id_MIN_LIM_MF = LIMP_HOME_Id_MIN_LIM_MF;
				Flux_MIN = LIMP_HOME_FLUX_MIN_LIM;
				Torque_MAX = LIMP_HOME_TORQUE_MAX_LIM;
				torque_SAT_MAX = LIMP_HOME_TORQUE_SAT_MAX_LIM;
				speed_Derat_Val = LIMP_HOME_SPEED_DERATE;
			}
			else if(speed0_SS_Act_Mode == ACTIVATE)
			{
				/* This condition is used for when Mode is select after SS is activate, before run motor again SS is deactivate when Press Brak and Mode switch move to Previous Mode not eco mode */
				if((speed0_SS_Act_Drive_Mode==ACTIVATE)&&(speed0_SS_Act_Power_Mode==DEACTIVATE))
				{
					power_Mode = DEACTIVATE;
					drive_Mode = ACTIVATE;
					park_Mode = DEACTIVATE;
					limpHome_Mode = DEACTIVATE;
					modeSW_Cnt = 1;
					speed_Ref_SI = ECO_FWD_SPEED_MAX;
					id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
					Flux_MIN = ECO_FLUX_MIN_LIM;
					Torque_MAX = ECO_TORQUE_MAX_LIM;
					torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
					speed_Derat_Val = DRV_ECO_SPEED_DERATE;
				}
				else if((speed0_SS_Act_Drive_Mode==ACTIVATE)&&(speed0_SS_Act_Power_Mode== ACTIVATE))
				{
					power_Mode = ACTIVATE;
					drive_Mode = ACTIVATE;
					park_Mode = DEACTIVATE;
					limpHome_Mode = DEACTIVATE;
					speed_Ref_SI = PWR_FWD_SPEED_MAX;
					id_MIN_LIM_MF = PWR_Id_MIN_LIM_MF;
					Flux_MIN = PWR_FLUX_MIN_LIM;
					Torque_MAX = PWR_TORQUE_MAX_LIM;
					speed_Derat_Val = DRV_PWR_SPEED_DERATE;
					torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
					modeSW_Cnt = 2;
				}
			}
			speed0_SS_Act_Mode = DEACTIVATE;
		}
	}
	else if( ( (mode_SW == ACTIVATE) && (mode_SW_LATCH == DEACTIVATE)) && ( ( (ideal_Mode == DEACTIVATE) && (drive_Mode == ACTIVATE)) && (break_Apply == DEACTIVATE) ) && (limpHome_Mode_Sens_STAT == DEACTIVATE))
	{
		mode_SW_LATCH = ACTIVATE;
		modeSW_Cnt++;
		if(modeSW_Cnt > 2)
		{
			modeSW_Cnt = 1;
		}
		if(modeSW_Cnt == 1)
		{
			if( (speed_RPM < _40KMPH) && (throttle_Read_Act < _40PERSENT_TPS) )
			{
				power_Mode = DEACTIVATE;
				limpHome_Mode = DEACTIVATE;
				speed_Ref_SI = ECO_FWD_SPEED_MAX;
				id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
				Flux_MIN = ECO_FLUX_MIN_LIM;
				Torque_MAX = ECO_TORQUE_MAX_LIM;
				speed_Derat_Val = DRV_ECO_SPEED_DERATE;
			}
			else
			{
				modeSW_Cnt = 2;
			}
		}
		else if(modeSW_Cnt == 2)
		{
			power_Mode = ACTIVATE;
			limpHome_Mode = DEACTIVATE;
			speed_Ref_SI = PWR_FWD_SPEED_MAX;
			id_MIN_LIM_MF = PWR_Id_MIN_LIM_MF;
			Flux_MIN = PWR_FLUX_MIN_LIM;
			Torque_MAX = PWR_TORQUE_MAX_LIM;
			speed_Derat_Val = DRV_PWR_SPEED_DERATE;
		}		
	}
	else if( (mode_SW == DEACTIVATE) && (mode_SW_LATCH == ACTIVATE) )
	{
		mode_SW_LATCH = DEACTIVATE;
		modeSW_ON_Time_Cnt = RST;
		
		if(sys_ON == ACTIVATE)
		{
			sys_ON_LATCH = ACTIVATE;
		}
			
	}
	
	
	/* Drive to Ideal Mode at No Responce Of Vehicle at 180s */
	if((drive_Mode == ACTIVATE) && (speed_RPM == 0) && (throttle_Read_Act <=0))
	{
		vehi_Ideal_Cnt++;
		if(vehi_Ideal_Cnt >= _180s)/* 180s */
		{
			vehi_Ideal_Cnt = (_180s+1);	/* Limit the count manully */
			vehi_Ideal_180s_Flg = ACTIVATE;
		}
	}
	else
	{
		vehi_Ideal_Cnt = 0;
		vehi_Ideal_180s_Flg = DEACTIVATE;
	}
	
	
	/****************** Park_Mode  ************************/
	if( ( (park_SW == ACTIVATE) && ( (mode_Change == ACTIVATE) || (ideal_Mode == DEACTIVATE) ))
		&& (( (ideal_Mode == ACTIVATE) && (sys_ON_LATCH == DEACTIVATE)) || ( (drive_Mode == ACTIVATE)))
		&& (limpHome_Mode_Sens_STAT == DEACTIVATE))
	{
		MODE_CHECK_Tep = 1;
		park_SW_LATCH = ACTIVATE;
		park_SW_ON_Time_Cnt++;
		if(((park_SW_ON_Time_Cnt >= _1s)||((speed0_SS_Act_Mode==ACTIVATE)&&(park_SW_ON_Time_Cnt>=_200ms))) && ( (throttle_Read_Act < _1PERSENT_TPS) ) ) /*40=1 Sec *//*8=0.2sec if SS is activate after Mode select */
		{
			park_Mode = ACTIVATE;
			forward_Mode = ACTIVATE;
			ideal_Mode = DEACTIVATE;
			drive_Mode = DEACTIVATE;
			ideal_Mode_Time_Cnt = RST;
			modeSW_ON_Time_Cnt = RST;
			parkSW_Cnt = 1;
			speed_Ref_SI = PRK_FWD_SPEED_MAX;
			id_MIN_LIM_MF = PRK_Id_MIN_LIM_MF;
			Flux_MIN = PRK_FLUX_MIN_LIM;
			Torque_MAX = PRK_TORQUE_MAX_LIM;
			torque_SAT_MAX = PRK_TORQUE_SAT_MAX_LIM;
			speed_Derat_Val = PRK_FWD_SPEED_DERATE;
				speed0_SS_Act_Mode = DEACTIVATE;
		}
	}
	else if( ( ( (park_SW == ACTIVATE) && (speed_RPM <= _0KMPH) ) ) && 
		( ( (ideal_Mode == DEACTIVATE) && (park_Mode == ACTIVATE)) && 
		( (park_SW_LATCH == DEACTIVATE) && (break_Apply == DEACTIVATE) )) 
		&& (limpHome_Mode_Sens_STAT == DEACTIVATE))
	{
		park_SW_LATCH = ACTIVATE;
		parkSW_Cnt++;
		if(parkSW_Cnt > 2)
		{
			parkSW_Cnt = 1;
		}
		if(parkSW_Cnt == 1)
		{
			forward_Mode = ACTIVATE;
			speed_Ref_SI = PRK_FWD_SPEED_MAX;
			speed_Derat_Val = PRK_FWD_SPEED_DERATE;
		}
		else if(parkSW_Cnt == 2)
		{
			forward_Mode = DEACTIVATE;
			speed_Ref_SI = PRK_REV_SPEED_MAX;
			speed_Derat_Val = PRK_REV_SPEED_DERATE;
		}
	}		
	else if( (park_SW == DEACTIVATE) && (park_SW_LATCH == ACTIVATE) )
	{
		park_SW_LATCH = DEACTIVATE;
		park_SW_ON_Time_Cnt = RST;
		if(sys_ON == ACTIVATE)
		{
			sys_ON_LATCH = ACTIVATE;
		}
			
	}
	/************** Run Time SS Ativate go to LimpHome Mode *******************/
	
	if(((side_Stand == ACTIVATE)&& (limpHome_Mode_Sens_STAT == DEACTIVATE)) && (speed_RPM >= DRV_SS_ACT_SPEED_MAX) && (drive_Mode == ACTIVATE) )
	{
			limpHome_Mode = ACTIVATE;
			if(limp_Lock == 0)
			{
				pre_Power_Mode = power_Mode;
				limp_Lock = 1;
			}
			power_Mode = DEACTIVATE;
			drive_Mode = DEACTIVATE;
			park_Mode = DEACTIVATE;
			speed_Ref_SI = LIMP_HOME_FWD_SPEED_MAX;
			id_MIN_LIM_MF = LIMP_HOME_Id_MIN_LIM_MF;
			Flux_MIN = LIMP_HOME_FLUX_MIN_LIM;
			Torque_MAX = LIMP_HOME_TORQUE_MAX_LIM;
			torque_SAT_MAX = LIMP_HOME_TORQUE_SAT_MAX_LIM;
			speed_Derat_Val = LIMP_HOME_SPEED_DERATE;
	}
	else if(((side_Stand == DEACTIVATE)&& (limpHome_Mode_Sens_STAT == DEACTIVATE)) && ( limp_Lock == 1 ) && (ideal_Mode == DEACTIVATE) )
	{
			limpHome_Mode = DEACTIVATE;
			limp_Lock = 0;
			/* While Driving Limp Home mode to Drive mode move to Previous Mode */
		if( (pre_Power_Mode == ACTIVATE) && (side_Stand == DEACTIVATE) )
		{
			speed_Ref_SI = PWR_FWD_SPEED_MAX;
			
			
				power_Mode = ACTIVATE;
				drive_Mode = ACTIVATE;
				park_Mode = DEACTIVATE;
				limpHome_Mode = DEACTIVATE;
				//modeSW_Cnt = 1;
				speed_Ref_SI = PWR_FWD_SPEED_MAX;
				id_MIN_LIM_MF = PWR_Id_MIN_LIM_MF;
				Flux_MIN = PWR_FLUX_MIN_LIM;
				Torque_MAX = PWR_TORQUE_MAX_LIM;
				torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
				speed_Derat_Val = DRV_ECO_SPEED_DERATE;
		}
		else if( (pre_Power_Mode == DEACTIVATE) && (side_Stand == DEACTIVATE) )
		{
			speed_Ref_SI = ECO_FWD_SPEED_MAX;
			
			
				power_Mode = DEACTIVATE;
				drive_Mode = ACTIVATE;
				park_Mode = DEACTIVATE;
				limpHome_Mode = DEACTIVATE;
				speed_Ref_SI = ECO_FWD_SPEED_MAX;
				id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
				Flux_MIN = ECO_FLUX_MIN_LIM;
				Torque_MAX = ECO_TORQUE_MAX_LIM;
				torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
				speed_Derat_Val = DRV_ECO_SPEED_DERATE;
		}
	}
		
	
	/***************** Cruise Control ******************/
	if((crus_SW == ACTIVATE) && (speed_RPM >= _20KMPH) && (speed_RPM <= _45KMPH) && (drive_Mode == ACTIVATE) && (throttle_Read_Act >= 700) )
	{
		cruise_Mode = ACTIVATE;
		if(crus_Lock == 0)
		{
			crus_throttle_Read_Act = throttle_Read;//throttle_Read_Act;
			pre_Power_Mode_Crus = power_Mode;
			crus_Lock = 1;
		}
	}
	if( (side_Stand == ACTIVATE) || (crus_SW == DEACTIVATE) || (break_Apply == ACTIVATE) || (throttle_Read_Act <= 100) || (speed_RPM < _20KMPH) || (speed_RPM > _45KMPH) || (crus_FLT_STAT == ACTIVATE) )
	{	
		/* While Driving cruise mode to Drive mode move to Previous Mode */
		cruise_Mode = DEACTIVATE;
		if( (pre_Power_Mode_Crus == ACTIVATE) && (crus_Lock == 1))
		{
			speed_Ref_SI = PWR_FWD_SPEED_MAX;			
			power_Mode = ACTIVATE;
			drive_Mode = ACTIVATE;
			park_Mode = DEACTIVATE;
			speed_Ref_SI = PWR_FWD_SPEED_MAX;
			id_MIN_LIM_MF = PWR_Id_MIN_LIM_MF;
			Flux_MIN = PWR_FLUX_MIN_LIM;
			Torque_MAX = PWR_TORQUE_MAX_LIM;
			torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
			speed_Derat_Val = DRV_ECO_SPEED_DERATE;
		}
		else if( (pre_Power_Mode == DEACTIVATE) && (crus_Lock == 1) )
		{
			speed_Ref_SI = ECO_FWD_SPEED_MAX;
			
			
				power_Mode = DEACTIVATE;
				drive_Mode = ACTIVATE;
				park_Mode = DEACTIVATE;
				speed_Ref_SI = ECO_FWD_SPEED_MAX;
				id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
				Flux_MIN = ECO_FLUX_MIN_LIM;
				Torque_MAX = ECO_TORQUE_MAX_LIM;
				torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
				speed_Derat_Val = DRV_ECO_SPEED_DERATE;
		}
		crus_Lock = 0;
	}
		
	
	/****************** Ideal Mode ************************/
	if( ( ( (mode_SW == ACTIVATE) || (park_SW == ACTIVATE) ) && ((mode_SW_LATCH == DEACTIVATE) && (park_SW_LATCH == DEACTIVATE) && 
		( (sys_ON_LATCH == ACTIVATE) && ( (mode_Change == ACTIVATE) || (break_Apply == ACTIVATE) )) ))
		|| (vehi_Ideal_180s_Flg == ACTIVATE) || (vehicle_Not_Drivable == ACTIVATE) || (sleep_REQ_Latch == ACTIVATE) || 
		((kill_SW == ACTIVATE) ||( (((side_Stand == ACTIVATE) && ((drive_Mode == ACTIVATE) || (park_Mode == ACTIVATE)) ) || 
		((side_Stand == ACTIVATE) && (limpHome_Mode == ACTIVATE)&&(speed_RPM <_1KMPH))) && 
		(limpHome_Mode_Sens_STAT == DEACTIVATE) && (speed_RPM < DRV_SS_ACT_SPEED_MAX)) ))
	{
		ideal_Mode_Time_Cnt++;
		if((kill_SW == ACTIVATE) || (ideal_Mode_Time_Cnt > _1s))/* 1 Sec *//* Kill Switch Done Have any delay Time, but other condition need 1s dealy to act Ideal Mode */
		{
			/* Side stand Happens After Drive Mode Select When go back move to previous Mode not Defaul Mode so find what is the status of mOde is select */
			if((speed_RPM == 0)&&(side_Stand == ACTIVATE)&&((drive_Mode == ACTIVATE)||(park_Mode == ACTIVATE)) )
			{
				speed0_SS_Act_Drive_Mode = drive_Mode;
				speed0_SS_Act_Park_Mode = park_Mode;
				speed0_SS_Act_Power_Mode = power_Mode;
				speed0_SS_Act_Mode = ACTIVATE;
			}
			else
			{
				speed0_SS_Act_Mode = DEACTIVATE;
			}
			ideal_Mode = ACTIVATE;
			pre_Power_Mode = DEACTIVATE;
			limpHome_Mode = DEACTIVATE;
			drive_Mode = DEACTIVATE;
			power_Mode = DEACTIVATE;
			park_Mode = DEACTIVATE;
			modeSW_ON_Time_Cnt = RST;	
			park_SW_ON_Time_Cnt = RST;
			sys_ON = DEACTIVATE;
		}
	}
	if( ( ( (mode_SW == DEACTIVATE) && (park_SW == DEACTIVATE) ) && (( (mode_Change == ACTIVATE) || (side_Stand == ACTIVATE)) &&
		(ideal_Mode == ACTIVATE) && (sys_ON == DEACTIVATE))) || 
		( (park_Mode == ACTIVATE) && (side_Stand == ACTIVATE) && (sys_ON == DEACTIVATE)))// && ( (ideal_Mode == DEACTIVATE) && (mode_Change == ACTIVATE)) ))
	{
		sys_ON = ACTIVATE;
		sys_ON_LATCH = DEACTIVATE;
	}
	
////	/* Manually maked Mode seletion for tempervoray purpose*/
//	/* Eco Mode */
//			mode_SW_LATCH = ACTIVATE;
//			drive_Mode = ACTIVATE;
//			forward_Mode = ACTIVATE;
//			ideal_Mode = DEACTIVATE;
//			park_Mode = DEACTIVATE;
//			power_Mode = DEACTIVATE;
//			speed_Ref_SI = ECO_FWD_SPEED_MAX;
//			id_MIN_LIM_MF = ECO_Id_MIN_LIM_MF;
//			Flux_MIN = ECO_FLUX_MIN_LIM;
//			Torque_MAX = ECO_TORQUE_MAX_LIM;
//			torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
//			speed_Derat_Val = DRV_ECO_SPEED_DERATE;


///* Power Mode */
//			mode_SW_LATCH = ACTIVATE;
//			drive_Mode = ACTIVATE;
//			forward_Mode = ACTIVATE;
//			ideal_Mode = DEACTIVATE;
//			park_Mode = DEACTIVATE;
//			power_Mode = ACTIVATE;
//			speed_Ref_SI = PWR_FWD_SPEED_MAX;
//			id_MIN_LIM_MF = PWR_Id_MIN_LIM_MF;
//			Flux_MIN = PWR_FLUX_MIN_LIM;
//			Torque_MAX = PWR_TORQUE_MAX_LIM;
//			torque_SAT_MAX = DRV_TORQUE_SAT_MAX_LIM;
//			speed_Derat_Val = DRV_PWR_SPEED_DERATE;

///* Park Forward Mode */
//			park_Mode = ACTIVATE;
//			forward_Mode = ACTIVATE;
//			ideal_Mode = DEACTIVATE;
//			drive_Mode = DEACTIVATE;
//			ideal_Mode_Time_Cnt = RST;
//			modeSW_ON_Time_Cnt = RST;
//			parkSW_Cnt = 1;
//			//forwardSW_Cnt = 1;	
//			speed_Ref_SI = PRK_FWD_SPEED_MAX;
//			id_MIN_LIM_MF = PRK_Id_MIN_LIM_MF;
//			Flux_MIN = PRK_FLUX_MIN_LIM;
//			Torque_MAX = PRK_TORQUE_MAX_LIM;
//			torque_SAT_MAX = PRK_TORQUE_SAT_MAX_LIM;
//			speed_Derat_Val = PRK_FWD_SPEED_DERATE;

///* Park Reverse Mode */
//			park_Mode = ACTIVATE;
//			forward_Mode = DEACTIVATE;
//			ideal_Mode = DEACTIVATE;
//			drive_Mode = DEACTIVATE;
//			ideal_Mode_Time_Cnt = RST;
//			modeSW_ON_Time_Cnt = RST;
//			parkSW_Cnt = 1;
//			//forwardSW_Cnt = 1;	
//			speed_Ref_SI = PRK_REV_SPEED_MAX;
//			id_MIN_LIM_MF = PRK_Id_MIN_LIM_MF;
//			Flux_MIN = PRK_FLUX_MIN_LIM;
//			Torque_MAX = PRK_TORQUE_MAX_LIM;
//			torque_SAT_MAX = PRK_TORQUE_SAT_MAX_LIM;
//			speed_Derat_Val = PRK_REV_SPEED_DERATE;

}
		
	