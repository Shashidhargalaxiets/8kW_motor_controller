/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "CAN.h"
#include "CAN_TX.h"
#include "iodefine.h"
#include "Digital_Input_Read.h"
#include "Fault_Analysis.h"

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/


/**
****************************************************************************************************************************
*	Extern variables
****************************************************************************************************************************
**/
extern uint8_t flt_CLR;
/* 0x600 ID Variable */
extern uint8_t hand_Shak_Latch;


/* 0x606 ID Variable */
extern uint16_t dcVolt_ACT;
extern int16_t dc_I_RMS;
extern uint16_t aPH_I_ACT_RMS_CAN;

extern uint8_t limpHome_Mode;
extern uint8_t kill_SW;


/* 0x607 ID Variable */
extern int16_t input_Power;
extern int16_t output_Power;
extern uint16_t speed_RPM;
extern uint8_t cruise_Mode;
extern int16_t torque_PI_SetPoint;

/* 0x608 ID Variable */
extern uint16_t mot_Temp_Cel;
extern uint16_t inv_R_Ph_Temp_Cel;
extern uint16_t inv_Y_Ph_Temp_Cel;
extern uint16_t inv_B_Ph_Temp_Cel;

extern uint8_t inv_R_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_Y_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_B_Ph_Temp_Sens_HLTH_FLT;

/* 0x609 ID Variable */
extern uint8_t hand_Shak_Latch;
extern uint8_t forward_Mode;
extern uint8_t power_Mode;
extern uint8_t drive_Mode;
extern uint8_t ideal_Mode;
extern uint8_t park_Mode;
extern uint8_t side_Stand;
extern uint8_t break_Apply;

extern uint8_t dc_OV_Volt_FLT;
extern uint8_t dc_UV_Volt_FLT;
extern uint8_t dc_OC_FLT;
extern uint8_t ph_I_OC_FLT;
extern uint8_t over_SPEED_FLT;
extern uint8_t over_MOT_TEMP_FLT;
extern uint8_t over_INV_TEMP_FLT;
extern uint8_t dc_BUS_SC_FLT;
extern uint8_t mot_Phase_SC_FLT;
extern uint8_t stall_Prot_FLT;
extern uint8_t hall_Sens_FLT;
extern uint8_t ac_I_R_Sens_HLTH_FLT;
extern uint8_t ac_I_Y_Sens_HLTH_FLT;
extern uint8_t ac_I_B_Sens_HLTH_FLT;
extern uint8_t dc_I_Sens_HLTH_FLT;
extern uint8_t tps_Sens_HLTH_FLT;
extern uint8_t mot_NTC_Sens_HLTH_FLT;
extern uint8_t inv_R_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_Y_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t inv_B_Ph_Temp_Sens_HLTH_FLT;
extern uint8_t ps_Sens_HLTH_FLT;


extern uint16_t tps1_V_Cnt;

/* 0x610 ID Variable */
extern uint16_t torque_SAT_MAX;
extern uint8_t park_SW;

/* Tempervory _purpose */
extern uint8_t mode_Change;
extern uint8_t mode_SW;


/* 0x611 ID Variable */
extern int16_t v_q;
extern int16_t v_d;
extern int16_t Iq_DF_Use_T; 
extern int16_t Iq_DF;
extern int16_t Id_DF;

/* 0x614 ID Variable */
extern uint16_t bPH_I_ACT_RMS_CAN;
extern uint16_t cPH_I_ACT_RMS_CAN;

/* 0x615 ID Variable */
extern int16_t throttle_Read_Act;
extern int16_t throttle_Read;
extern int16_t torque_PI_SetPoint;
extern int16_t flux_setPoint;

extern uint16_t taub0_0_CNT;


extern uint8_t MODE_CHECK_Tep;

extern uint8_t sleep_RDY_FLG;
/**
****************************************************************************************************************************
*	Global variables
****************************************************************************************************************************
**/


uint16_t speed_RPM1 = 0;
uint16_t speed_KMPH = 0;
uint16_t speed_KMPH1 = 0;
uint16_t speed_KMPH2 = 0;
		
		

uint16_t _7msCnt = 0;
uint16_t _10msCnt = 0;
uint16_t _20msCnt = 0;
uint16_t _30msCnt = 0;
uint16_t _40msCnt = 0;
uint16_t _50msCnt = 0;
uint16_t _70msCnt = 0;
uint16_t _80msCnt = 0;
uint16_t _90msCnt = 0;
uint16_t _100msCnt = 0;
		
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void CAN_TX(void)
{
	/* This fucntion is called every 0.5ms to calling inside funtion is x*0.5ms=for calling time based on DBC 
		for example taub0_0_CNT %20(20 is x) so 20*0.5ms=10ms
	*/
	if(GETS_CAN == 1)
	{
		if( (taub0_0_CNT % 20 == 0) )
		{
			trans_615();
		}
		if( (taub0_0_CNT % 41 == 0) )
		{
			trans_614();		
		}
		if( (taub0_0_CNT % 63 == 0) )
		{
			trans_606();
		}
		if( (taub0_0_CNT % 81 == 0) )
		{
			trans_607();
		}
		if( (taub0_0_CNT % 101 == 0) )
		{
			trans_611();
		}
		if( (taub0_0_CNT % 121 == 0) )
		{
			trans_608();
		}
		if( (taub0_0_CNT % 150 == 0) )
		{
			trans_609();
		}
		if( (taub0_0_CNT % 199 == 0) )
		{
			trans_600();
		}
		
		if(sleep_RDY_FLG == ACTIVATE)
		{
			if( (taub0_0_CNT % 190 == 0) )
			{
				//trans_605();
			}
		}
	}
	else if(GETS_CAN == 0)
	{
		if( (taub0_0_CNT % 20 == 0) )
		{
			trans_606();
		}
		if( (taub0_0_CNT % 41 == 0) )
		{
			trans_607();		
		}
		if( (taub0_0_CNT % 63 == 0) )
		{
			trans_608();
		}
		if( (taub0_0_CNT % 81 == 0) )
		{
			trans_609();
		}
		if( (taub0_0_CNT % 101 == 0) )
		{
			trans_555();
			//trans_610();
		}
		if( (taub0_0_CNT % 141 == 0) )
		{
			trans_610();
		}
		if( (taub0_0_CNT % 199 == 0) )
		{
			trans_600();
			trans_605();
		}
	}
	else if(GETS_CAN == 2)
	{
		if( (taub0_0_CNT % 40 == 0) )
		{
			trans_610();
		}
		if( (taub0_0_CNT % 60 == 0) )
		{
			trans_608();		
		}
		if( (taub0_0_CNT % 140 == 0) )
		{
			trans_600();
		}
		if(taub0_0_CNT >= 140)
		{
			taub0_0_CNT = 0;
		}
	}
	else if(GETS_CAN == 3)
	{
//		_7msCnt +=1;
//		_10msCnt +=1;
//		_20msCnt +=1;
//		_30msCnt +=1;
//		_40msCnt += 1;
//		_50msCnt +=1;
//		_70msCnt +=1;
//		_80msCnt +=1;
//		_90msCnt +=1;
//		_100msCnt +=1;
		
//		if( (_7msCnt >= 14) )
//		{
//			trans_608();
//			_7msCnt = 0;
//		}
//		if( (_40msCnt >= 80))
//		{	
//			trans_610();
//			_40msCnt = 0;
//		}
//		if( (_100msCnt >= 200) )
//		{
//			trans_600();
//			_100msCnt = 0;
//		}
//		/* GETS LAB View based CAN DBC File */
//		if( (_10msCnt >=20) )
//		{
//			trans_615();
//			_10msCnt = 0;
//		}
//		if( (_50msCnt >=100) )
//		{
//			trans_614();
//			_50msCnt = 0;
//		}
//		if( (_30msCnt >= 60) )
//		{
//			trans_606();
//			_30msCnt = 0;
//		}
//		if( (_40msCnt >= 80) )
//		{
//			trans_607();
//			_40msCnt = 0;
//		}
//		if( (_70msCnt >= 140) )
//		{
//			trans_611();
//			_70msCnt = 0;
//		}
//		if( (_80msCnt >=160) )
//		{
//			trans_605();
//			_80msCnt = 0;
//		}
//		if( (_90msCnt >= 180) )
//		{
//			trans_609();
//			_90msCnt = 0;
//		}
		
		
		if( (taub0_0_CNT % 21 == 0) )//14
		{
			trans_608();
		}
		if( (taub0_0_CNT % 40 == 0) )
		{	
			trans_610();	
		}
		if( (taub0_0_CNT % 199 == 0) )
		{
			trans_600();
		}
		/* GETS LAB View based CAN DBC File */
		if( (taub0_0_CNT % 19 == 0) )
		{
			trans_615();
		}
		if( (taub0_0_CNT % 98 == 0) )
		{
			trans_614();		
		}
		if( (taub0_0_CNT % 59 == 0) )
		{
			trans_606();
		}
		if( (taub0_0_CNT % 78 == 0) )
		{
			trans_607();
		}
		if( (taub0_0_CNT % 143 == 0) )
		{
			trans_611();
		}
		if( (taub0_0_CNT % 161 == 0) )
		{
			trans_605();/* if we send data through CAN but GUI not show any temperature value, because GUI ID Vehicle communication purpose used */
		}
		if( (taub0_0_CNT % 180 == 0) )
		{
			trans_609();
		}
		
	}
	
		
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_600(void)
{
	uint8_t tx_arr_600[DATA_LENGTH_1];
	
	tx_arr_600[0] = 0x23;
	
	can0_tx(TX_ID600,DATA_LENGTH_1,tx_arr_600,0);
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_605(void)
{
	if(GETS_CAN == 0)
	{
		uint8_t tx_arr_605[DATA_LENGTH_1];
		
		tx_arr_605[0] = 0xC;
		
		can0_tx(TX_ID605,DATA_LENGTH_1,tx_arr_605,0);
	}	
	else if(GETS_CAN == 3)
	{
		uint8_t tx_arr_605[DATA_LENGTH_8];

		tx_arr_605[0] = ((mot_Temp_Cel>> 0) & 0xFF);
		tx_arr_605[1] = ((mot_Temp_Cel >> 8) & 0xFF);
		tx_arr_605[2] = ((inv_R_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_605[3] = ((inv_R_Ph_Temp_Cel >> 8) & 0xFF);
		
		tx_arr_605[4] = ((inv_Y_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_605[5] = ((inv_Y_Ph_Temp_Cel >> 8) & 0xFF);
		tx_arr_605[6] = ((inv_B_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_605[7] = ((inv_B_Ph_Temp_Cel >> 8) & 0xFF);
		
		can0_tx(TX_ID605,DATA_LENGTH_8,tx_arr_605,0);
	}
}	
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_555(void)
{
	uint8_t tx_arr_555[DATA_LENGTH_6];
	uint8_t ref_ID = 0;
	uint8_t act_ID = 0;
	uint8_t ref_IQ = 0;
	uint8_t act_IQ = 0;
	uint8_t ref_VD = 0;
	uint8_t ref_VQ = 0;
	
	ref_ID = (uint8_t)((flux_setPoint/(float)4.1)+128);/* 128 is offset */
	ref_IQ = (uint8_t)((torque_PI_SetPoint/(float)4.1)+128);
	act_ID = (uint8_t)((Id_DF/(float)4.1)+128);		/* 4.1 is current convertion DF from current sensor(discripection chekc with ADC_Read.c file */
	act_IQ = (uint8_t)((Iq_DF/(float)4.1)+128);
	ref_VD = (uint8_t)((v_d/(float)40.48)+128);		/* 1/40.48= 0.0295 deatils pleace in ADC_Read.c file DC voltage calculation from count to SI value refer */
	ref_VQ = (uint8_t)((v_q/(float)33.898)+128);
	
	tx_arr_555[0] = ref_ID;
	tx_arr_555[1] = act_ID;
	tx_arr_555[2] = ref_IQ;
	tx_arr_555[3] = act_IQ;
	
	tx_arr_555[4] = ref_VD;
	tx_arr_555[5] = ref_VQ;
	
	
	can0_tx(TX_ID555,DATA_LENGTH_6,tx_arr_555,0);	
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_606(void)
{
	if((GETS_CAN == 1) || (GETS_CAN == 3))
	{
		uint8_t tx_arr_606[DATA_LENGTH_8];
		uint16_t dc_I_RMS_Offset = 0;
		
		dc_I_RMS_Offset = (dc_I_RMS + 400);

		tx_arr_606[0] = ((dcVolt_ACT >> 0) & 0xFF);
		tx_arr_606[1] = ((dcVolt_ACT >> 8) & 0xFF);
		tx_arr_606[2] = ((dc_I_RMS_Offset >> 0) & 0xFF);
		tx_arr_606[3] = ((dc_I_RMS_Offset >> 8) & 0xFF);
		
		tx_arr_606[4] = ((0 >> 0) & 0xFF);
		tx_arr_606[5] = ((0 >> 8) & 0xFF);
		tx_arr_606[6] = ((aPH_I_ACT_RMS_CAN >> 0) & 0xFF);
		tx_arr_606[7] = ((aPH_I_ACT_RMS_CAN >> 8) & 0xFF);
		
		can0_tx(TX_ID606,DATA_LENGTH_8,tx_arr_606,0);
	}
	else if(GETS_CAN == 0)
	{
		uint8_t tx_arr_606[DATA_LENGTH_4];		
		uint8_t start_SW=0;
		uint8_t ignition_SW=0;
		uint8_t can_Time_Out_error=0;
	
		tx_arr_606[0] = 0;	/* Throttle Voltage 2 not connected external hardware*/
		tx_arr_606[1] = 0;	/* Throttle Voltage 2 not connected external hardware*/		
		tx_arr_606[2] = ((aPH_I_ACT_RMS_CAN >> 0) & 0xFF);
		tx_arr_606[3] = ((limpHome_Mode<<0) | (kill_SW<<1) | (start_SW<<2) | (ignition_SW<<3) | (can_Time_Out_error<<4) );
		
		can0_tx(TX_ID606,DATA_LENGTH_4,tx_arr_606,0);
	}
		
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_607(void)
{
	if((GETS_CAN == 1) || (GETS_CAN == 3))
	{
		uint8_t tx_arr_607[DATA_LENGTH_8];
		uint16_t input_Power_Offset  = 0;
		uint16_t output_Power_Offset = 0;
		
		input_Power_Offset  = (input_Power + 30000);
		output_Power_Offset = (output_Power + 30000);

		tx_arr_607[0] = ((input_Power_Offset >> 0) & 0xFF);
		tx_arr_607[1] = ((input_Power_Offset >> 8) & 0xFF);
		tx_arr_607[2] = ((output_Power_Offset >> 0) & 0xFF);
		tx_arr_607[3] = ((output_Power_Offset >> 8) & 0xFF);
		
		tx_arr_607[4] = ((0 >> 0) & 0xFF);
		tx_arr_607[5] = ((0 >> 8) & 0xFF);
		tx_arr_607[6] = ((speed_RPM >> 0) & 0xFF);//
		tx_arr_607[7] = ((speed_RPM>> 8) & 0xFF);
		
		can0_tx(TX_ID607,DATA_LENGTH_8,tx_arr_607,0);
	}
	else if(GETS_CAN == 0)
	{
		uint8_t tx_arr_607[DATA_LENGTH_5];
		uint16_t motor_Torque_Output = 0;
		uint8_t precharge_FLT = 0;
		uint8_t precharge_Status_ACK_FLT = 0;
		
		uint16_t torque_Demand = 0;
		
		torque_Demand = (torque_PI_SetPoint * (float)0.1186);		/* 140(Max Torque)/1180(Max_Torque_ref)=0.1186 */

		tx_arr_607[0] = ((cruise_Mode<<0) | (precharge_FLT<<1) | (precharge_Status_ACK_FLT<<2));
		tx_arr_607[1] = ((motor_Torque_Output >> 0) & 0xFF);
		tx_arr_607[2] = ((motor_Torque_Output >> 8) & 0xFF);
		tx_arr_607[3] = ((torque_Demand >> 0) & 0xFF);
		
		tx_arr_607[4] = ((torque_Demand >> 8) & 0xFF);
		
		can0_tx(TX_ID607,DATA_LENGTH_5,tx_arr_607,0);
	}
		
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_608(void)
{
	if(GETS_CAN == 1)
	{
		uint8_t tx_arr_608[DATA_LENGTH_8];

		tx_arr_608[0] = ((mot_Temp_Cel>> 0) & 0xFF);
		tx_arr_608[1] = ((mot_Temp_Cel >> 8) & 0xFF);
		tx_arr_608[2] = ((inv_R_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_608[3] = ((inv_R_Ph_Temp_Cel >> 8) & 0xFF);
		
		tx_arr_608[4] = ((inv_Y_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_608[5] = ((inv_Y_Ph_Temp_Cel >> 8) & 0xFF);
		tx_arr_608[6] = ((inv_B_Ph_Temp_Cel >> 0) & 0xFF);
		tx_arr_608[7] = ((inv_B_Ph_Temp_Cel >> 8) & 0xFF);
		
		can0_tx(TX_ID608,DATA_LENGTH_8,tx_arr_608,0);
	}
	else if(GETS_CAN == 0)
	{
		uint8_t tx_arr_608[DATA_LENGTH_6];
		uint8_t speed_KMPH = 0;

		speed_KMPH = (uint8_t)((float)0.3768 * speed_RPM * WHEEL_RADIUS_METER);//2PI*3.6/60=0.3768, here is 3.6 is constant

		tx_arr_608[0] = ( ((inv_R_Ph_Temp_Sens_HLTH_FLT | inv_Y_Ph_Temp_Sens_HLTH_FLT | inv_B_Ph_Temp_Sens_HLTH_FLT) << 0) | (ps_Sens_HLTH_FLT << 1) | (dc_I_Sens_HLTH_FLT << 0) );
		tx_arr_608[1] = (speed_KMPH);
		tx_arr_608[2] = ((0 >> 0) & 0xFF);		/* DC Bus Regen Max Limit */
		tx_arr_608[3] = ((0 >> 8) & 0xFF);		/* DC Bus Regen Max Limit */
		
		tx_arr_608[4] = ((0 >> 0) & 0xFF);		/* DC Bus Discharge Max Limit */
		tx_arr_608[5] = ((0 >> 8) & 0xFF);		/* DC Bus Discharge Max Limit */
		
		can0_tx(TX_ID608,DATA_LENGTH_6,tx_arr_608,0);
	}
	else if( (GETS_CAN == 2) || (GETS_CAN == 3) )
	{
		uint8_t tx_arr_608[DATA_LENGTH_3];

		//speed_KMPH = (uint16_t)((float)0.3768 * speed_RPM * WHEEL_RADIUS_METER);//2PI*3.6/60=0.3768, here is 3.6 is constant
		speed_KMPH = (uint16_t)((float)0.1884 * speed_RPM * WHEEL_RADIUS_METER);//PI*60/1000=0.1884
		
		speed_KMPH1 = ((speed_KMPH << 7)& 0x80);
		speed_KMPH2 = ((speed_KMPH >> 1)& 0xFF);
		
		
		tx_arr_608[0] = ((speed_KMPH <<7 )& 0x80);//((speed_KMPH >> 8)& 0xFF);
		tx_arr_608[1] = ((speed_KMPH >> 1)& 0xFF);//((speed_KMPH >> 0)& 0xFF);
		tx_arr_608[2] = (0x00);		/* Reserived_Bit */
		
		can0_tx(TX_ID608,DATA_LENGTH_3,tx_arr_608,0);
	}
		
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_609(void)
{
	if((GETS_CAN == 1)||(GETS_CAN == 3))
	{
		uint8_t tx_arr_609[DATA_LENGTH_4];
		//tx_arr_609[0] = ((ideal_Mode <<0) | (drive_Mode << 1) | (hand_Shak_Latch << 2) | (park_Mode << 3) | (break_Apply << 4) | (side_Stand << 5) | (power_Mode << 6) | (forward_Mode << 7) );// && 0xFF);
		tx_arr_609[0] = ((ideal_Mode <<0) | (drive_Mode << 1) | (hand_Shak_Latch << 2) | (park_Mode << 3) | (break_Apply << 4) | (flt_CLR << 5) | (power_Mode << 6) | (forward_Mode << 7) );// && 0xFF);
		tx_arr_609[1] = ( (dc_OV_Volt_FLT << 0) | (dc_UV_Volt_FLT << 1) | (dc_OC_FLT << 2) | (dc_BUS_SC_FLT << 3) | (mot_Phase_SC_FLT << 4) | (stall_Prot_FLT << 5) | (ph_I_OC_FLT << 6) | (0 << 7) );
		tx_arr_609[2] = ((over_MOT_TEMP_FLT << 0) | (over_INV_TEMP_FLT << 1) | (0 << 2) | (hall_Sens_FLT << 3) | (dc_I_Sens_HLTH_FLT << 4) | (ac_I_R_Sens_HLTH_FLT << 5) | (ac_I_Y_Sens_HLTH_FLT << 6) | (ac_I_B_Sens_HLTH_FLT << 7) );
		tx_arr_609[3] = ((tps_Sens_HLTH_FLT << 0) | (mot_NTC_Sens_HLTH_FLT << 1) | (inv_R_Ph_Temp_Sens_HLTH_FLT << 2) | (inv_Y_Ph_Temp_Sens_HLTH_FLT << 3) | (inv_B_Ph_Temp_Sens_HLTH_FLT << 4) | (over_INV_TEMP_FLT << 5) | (ps_Sens_HLTH_FLT << 6) | (0 << 7) );
		
		can0_tx(TX_ID609,DATA_LENGTH_4,tx_arr_609,0);
	}
	else if(GETS_CAN == 0)
	{
		uint8_t tx_arr_609[DATA_LENGTH_6];
		tx_arr_609[0] = ((tps1_V_Cnt >> 0) & 0xFF);
		tx_arr_609[1] = ((tps1_V_Cnt >> 8) & 0xFF);
		tx_arr_609[2] = ((dc_I_RMS >> 0) & 0xFF);
		tx_arr_609[3] = ((dc_I_RMS >> 8) & 0xFF);
		
		tx_arr_609[4] = ((dcVolt_ACT >> 0) & 0xFF);
		tx_arr_609[5] = ((dcVolt_ACT >> 8) & 0xFF);
		
		can0_tx(TX_ID609,DATA_LENGTH_4,tx_arr_609,0);
	}		
		
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_610(void)
{
	if(GETS_CAN == 0)
	{
		uint8_t tx_arr_610[DATA_LENGTH_5];
		uint8_t throttle_Persent = 0;
		uint16_t throttle_Read_Act_CAN = 0;
		
		if(throttle_Read_Act<0)
		{
			throttle_Read_Act_CAN = 0;
		}
		else
		{
			throttle_Read_Act_CAN = throttle_Read_Act;
		}
		throttle_Persent = (uint8_t)((throttle_Read_Act_CAN/torque_SAT_MAX)*100);
		
		tx_arr_610[0] = (((tps1_V_Cnt > MAX_TPS_SENS_HLTH_LIMI)<<0) | ((tps1_V_Cnt < MIN_TPS_SENS_HLTH_LIMI)<<2) | (break_Apply<<5) | (mode_SW<<6) | (park_SW << 7));
		tx_arr_610[1] = ( (side_Stand<<0)| (( (!ideal_Mode)&(drive_Mode)&(!power_Mode))<<1) | (( (!ideal_Mode)&(drive_Mode)&(power_Mode))<<2) | ((limpHome_Mode<<2)|(limpHome_Mode<<1))|( ((!ideal_Mode)&park_Mode&forward_Mode)<<3)|( ( ((!ideal_Mode)&park_Mode&(!forward_Mode))<<3)|((!ideal_Mode)&park_Mode&(!forward_Mode))<<1) | (dc_OV_Volt_FLT<<4) | (dc_UV_Volt_FLT<<5) | (ph_I_OC_FLT<<6) | (mot_Phase_SC_FLT<<7) );
		tx_arr_610[2] = ( (stall_Prot_FLT<<0) | (hall_Sens_FLT<<1) | (over_INV_TEMP_FLT<<5) | (tps_Sens_HLTH_FLT<<6) | (over_MOT_TEMP_FLT<<7) );
		tx_arr_610[3] = ( (mot_NTC_Sens_HLTH_FLT<<1) );
		
		tx_arr_610[4] = throttle_Persent;		
		
		can0_tx(TX_ID610,DATA_LENGTH_5,tx_arr_610,0);
	}
	else if( (GETS_CAN == 2) || (GETS_CAN == 3) )
	{
		uint8_t tx_arr_610[DATA_LENGTH_8];
		uint8_t throttle_Persent = 0;
		uint16_t throttle_Read_Act_CAN = 0;
		if(throttle_Read_Act<0)
		{
			throttle_Read_Act_CAN = 0;
		}
		else
		{
			throttle_Read_Act_CAN = throttle_Read_Act;
		}
		throttle_Persent = (uint8_t)((throttle_Read_Act_CAN/torque_SAT_MAX)*100);
		
		tx_arr_610[0] = (  ((((ideal_Mode)&(drive_Mode)&(park_Mode)&&(limpHome_Mode))||((drive_Mode)&(!(power_Mode))))>>0) | (((drive_Mode)&(power_Mode))<<1) | ((limpHome_Mode<<0)|(limpHome_Mode<<1)) | ((park_Mode&(forward_Mode))<<2) | (((park_Mode&(!(forward_Mode)))<<2)|((park_Mode&(!(forward_Mode)))<<0)) | (break_Apply<<3) | (hall_Sens_FLT<<4)| (mode_SW<<5) | (park_SW<<6) | (side_Stand << 7));
		tx_arr_610[1] = 0x00;			/* Reserved Bit (Unknown1) */			
		tx_arr_610[2] = 0x00;			/* Reserved Bit (Unknown1) */			
		tx_arr_610[3] = 0x00;			/* Reserved Bit (Unknown2) */
		
		tx_arr_610[4] = 0x00;			/* Reserved Bit (Unknown2) */
		tx_arr_610[5] = throttle_Persent;
		tx_arr_610[6] = 0x00;			/* Reserved Bit (Unknown3) */
		tx_arr_610[7] = 0x00;			/* Error Byte */
		
		can0_tx(TX_ID610,DATA_LENGTH_8,tx_arr_610,0);
	}	
}

/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_611(void)
{
	uint8_t tx_arr_611[DATA_LENGTH_8];
	uint16_t v_q_Offset = 0;
	uint16_t v_d_Offset = 0;
	uint16_t Iq_DF_Offset = 0;
	uint16_t Id_DF_Offset = 0;
	
	v_q_Offset   = (v_q + 5000);
	v_d_Offset   = (v_d + 5000);
	Iq_DF_Offset = (Iq_DF + 5000);
	Id_DF_Offset = (Id_DF + 5000);

	tx_arr_611[0] = ((v_d_Offset >> 0) & 0xFF);
	tx_arr_611[1] = ((v_d_Offset >> 8) & 0xFF);
	tx_arr_611[2] = ((v_q_Offset >> 0) & 0xFF);
	tx_arr_611[3] = ((v_q_Offset >> 8) & 0xFF);
	
	tx_arr_611[4] = ((Id_DF_Offset >> 0) & 0xFF);
	tx_arr_611[5] = ((Id_DF_Offset >> 8) & 0xFF);
	tx_arr_611[6] = ((Iq_DF_Offset >> 0) & 0xFF);
	tx_arr_611[7] = ((Iq_DF_Offset >> 8) & 0xFF);
	
	can0_tx(TX_ID611,DATA_LENGTH_8,tx_arr_611,0);
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_614(void)
{
	uint8_t tx_arr_614[DATA_LENGTH_8];
	tx_arr_614[0] = ((0 >> 0) & 0xFF);
	tx_arr_614[1] = ((0 >> 8) & 0xFF);
	tx_arr_614[2] = ((bPH_I_ACT_RMS_CAN >> 0) & 0xFF);
	tx_arr_614[3] = ((bPH_I_ACT_RMS_CAN >> 8) & 0xFF);
	
	tx_arr_614[4] = ((0 >> 0) & 0xFF);
	tx_arr_614[5] = ((0 >> 8) & 0xFF);
	tx_arr_614[6] = ((cPH_I_ACT_RMS_CAN >> 0) & 0xFF);
	tx_arr_614[7] = ((cPH_I_ACT_RMS_CAN >> 8) & 0xFF);
	
	can0_tx(TX_ID614,DATA_LENGTH_8,tx_arr_614,0);
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void trans_615(void)
{
	uint8_t tx_arr_615[DATA_LENGTH_6];
	uint16_t flux_setPoint_Offset = 0;
	uint16_t throttle_Read_Offset = 0;
	uint16_t torque_PI_SetPoint_Offset = 0;
	
	flux_setPoint_Offset 	  = (flux_setPoint + 5000);
	throttle_Read_Offset	  = (throttle_Read_Act + 5000);
	torque_PI_SetPoint_Offset = (torque_PI_SetPoint + 5000);

	tx_arr_615[0] = ((throttle_Read_Offset >> 0) & 0xFF);
	tx_arr_615[1] = ((throttle_Read_Offset >> 8) & 0xFF);
	tx_arr_615[2] = ((torque_PI_SetPoint_Offset >> 0) & 0xFF);
	tx_arr_615[3] = ((torque_PI_SetPoint_Offset >> 8) & 0xFF);
	
	tx_arr_615[4] = ((flux_setPoint_Offset >> 0) & 0xFF);
	tx_arr_615[5] = ((flux_setPoint_Offset >> 8) & 0xFF);
	can0_tx(TX_ID615,DATA_LENGTH_6,tx_arr_615,0);
}
