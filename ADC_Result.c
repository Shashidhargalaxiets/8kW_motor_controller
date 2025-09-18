
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "iodefine.h"
#include "ADC_Result.h"
#include "Register_Interface.h"
#include "DigitalFilter.h"
#include "math.h"
#include "Resolver.h"

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

extern uint16_t RotarTheta;
extern int16_t Sine_Theta;
extern int16_t Cos_Theta;
extern uint16_t flag1;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
uint16_t count = 0;
uint8_t flag = 0;
//uint16_t RotarTheta_array[2000];
float Rotar_ThetaRadian = 0.0F;
//uint16_t sine_filtered_array[2000];
//uint16_t cos_filtered_array[2000];
//int16_t signed_sine_value[2000];
//int16_t signed_cos_value[2000];
//int16_t sine_offset_array[2000];
//int16_t cos_offset_array[2000];
//float sine_offset_array1[2000];
//float cos_offset_array1[2000];
//float Radian[2000];
float theta_in_degree = 0;
extern int16_t iA_filteredCnt;
extern int16_t iB_filteredCnt;
extern int16_t iC_filteredCnt;
//int16_t iA_off_fil_Cnt[2000];
//int16_t iB_off_fil_Cnt[2000];
//uint16_t iA_fil_Cnt[2000];
//uint16_t iB_fil_Cnt[2000];
//uint16_t Ia_cnt_raw[2000];
//uint16_t Ib_cnt_raw[2000];
uint16_t ac_R_Ph_I_Cnt;
uint16_t ac_Y_Ph_I_Cnt;
uint16_t ac_B_Ph_I_Cnt;

uint16_t dc_V_Bus_cnt;
uint16_t dc_I_Bus_cnt;

/* DC Bus Variable */
int16_t dc_Bus_I_Cnt = 0;
int16_t dc_Bus_V_Cnt = 0;
int16_t dc_Bus_I = 0;
int16_t dc_Bus_I_DF = 0;
uint16_t dc_Bus_V = 0;

/* DC Bus Digital Filter Variable */
int16_t dc_I_CTR_SUM = 0;
uint16_t dc_I_CTR_Cnt_loop = 0;
int16_t dc_I_CTR_Cnt = 0;
int16_t dc_I_CTR_Cnt_DF = 0;
int16_t per_DC_I_CTR_Cnt_DF = 0;
float df_Cof_DC_I_CTR = 0.5;

/* DC Voltage Calculation */
uint32_t dcVolt_ACT_SUM = 0;
uint16_t dc_Volt_CAL_CNT = 0;
float dcVolt_ACT = 0;
float adj_dcV = 0.0247;

/* DC Current Calculation */
int32_t dc_I_SUM = 0;
uint8_t dc_I_Cal_CNT = 0;
int16_t dc_I_AVG = 0;
float dc_I_RMS = 0;
float dc_I_MF = 4.1;
float df_Cof_DC_I = 0.2;
float df_Cof_DC_I_Avg = 0.2;
int16_t per_DC_Bus_I_DF = 0;

/* TPS Digital Filter Variable */
float df_Cof_TPS = 0.2;
uint16_t per_TPS1_V_DF = 0;
uint16_t per_TPS2_V_DF = 0;

/* TPS Signal Variable */
uint16_t tps1_Cnt = 0;
uint16_t tps2_Cnt = 0;
uint16_t tps1_V_Cnt = 0;
uint16_t tps2_V_Cnt = 0;

/* Motor Tempereture Variable */
uint16_t motor_Temp_V_Cnt = 0;
uint16_t motor_Temp_V	  = 0;

/* Inverter Tempereture Variable */
uint16_t inv_R_Ph_Temp_V_Cnt = 0;
uint16_t inv_Y_Ph_Temp_V_Cnt = 0;
uint16_t inv_B_Ph_Temp_V_Cnt = 0;
uint16_t inv_R_Ph_Temp_V = 0;
uint16_t inv_Y_Ph_Temp_V = 0;
uint16_t inv_B_Ph_Temp_V = 0;

/* Motor Temperature Digital Filter Variable */
float df_Cof_MOT_Temp = 0.2;
uint16_t per_Motor_Temp_V_DF = 0;

/* Inverter Temperature Digital Filter Variable */
float df_Cof_INV_Temp = 0.2;
uint16_t per_Inv_R_Ph_Temp_V_DF = 0;
uint16_t per_Inv_Y_Ph_Temp_V_DF = 0;
uint16_t per_Inv_B_Ph_Temp_V_DF = 0;
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Analog_Read(void)
{
	/*Variable declaration*/
	/* variables to get the resolver output*/
        uint16_t U_sineCount;
	uint16_t U_cosCount;
	uint16_t U_FilteredSine_Cnt;
	uint16_t U_FilteredCos_Cnt;
	
	int16_t Sine_signed_value;
	float Sine_signed_value1;
	int16_t Cos_signed_value;
	float Cos_signed_value1;
	float theta_radian;
	static uint16_t U_Prev_FilteredSine_Cnt;
	static uint16_t U_Prev_FilteredCos_Cnt;
	
	/*phase current*/
	uint16_t Ia_cnt =0;
	uint16_t Ib_cnt =0;
	uint16_t Ic_cnt =0;
	int16_t iA_ = 0;
	int16_t iB_ = 0;
	static uint16_t Ia_prev_filtered_cnt;
	static uint16_t Ib_prev_filtered_cnt;
        static uint16_t Ic_prev_filtered_cnt;
	
	/*DC_Bus quantities*/
	uint16_t dc_V_Bus; 
	uint16_t dc_I_Bus; 
	static uint16_t dc_V_Bus_prev_filtered_cnt;
	static uint16_t dc_I_Bus_prev_filtered_cnt;
	
	R_Config_ADCA0_ScanGroup1_OperationOn();
	
	while((ADCA0.SGSTR.UINT32) & 0X00000200);/* 0 means ADC conversion finish scangroup1 */	
	
	//Get the resolver Output i.e sine and cos count value
	Get_ResolverOutput(&U_sineCount,&U_cosCount );
	
	/*Applying the the filter for ADC Count of Sine */
	U_FilteredSine_Cnt = (uint16_t)low_pass_filter(U_sineCount, U_Prev_FilteredSine_Cnt, 0.2);
	U_Prev_FilteredSine_Cnt = U_FilteredSine_Cnt;
	
	Current_Feedback(&Ia_cnt,&Ib_cnt,&Ic_cnt);
	
        ac_R_Ph_I_Cnt  = (uint16_t)low_pass_filter(Ia_cnt, Ia_prev_filtered_cnt, 0.2);
	Ia_prev_filtered_cnt = ac_R_Ph_I_Cnt;
	
	ac_Y_Ph_I_Cnt  = (uint16_t)low_pass_filter(Ib_cnt, Ib_prev_filtered_cnt, 0.2);
	Ib_prev_filtered_cnt = ac_Y_Ph_I_Cnt;
	
	ac_B_Ph_I_Cnt = (uint16_t)low_pass_filter(Ic_cnt, Ic_prev_filtered_cnt, 0.2);
	Ic_prev_filtered_cnt = ac_B_Ph_I_Cnt;
	
	iA_filteredCnt = ( ac_R_Ph_I_Cnt - U_PHA_I_OFFSET);
	
	iB_filteredCnt = ( ac_Y_Ph_I_Cnt - V_PHA_I_OFFSET);
	
	iC_filteredCnt = ( ac_B_Ph_I_Cnt - W_PHA_I_OFFSET);
	
	Get_DC_quantities(&dc_V_Bus,&dc_I_Bus);
	
	//DC quantities
	
	dc_V_Bus_cnt = (uint16_t)low_pass_filter(dc_V_Bus, dc_V_Bus_prev_filtered_cnt, 0.2);
	dc_V_Bus_prev_filtered_cnt = dc_V_Bus_cnt;

        dcVolt_ACT_SUM += (dc_V_Bus_cnt);
        dc_Volt_CAL_CNT++;
        if(dc_Volt_CAL_CNT >= 100) /* 100 sample average */
        {
            dcVolt_ACT = (float)( (dcVolt_ACT_SUM / dc_Volt_CAL_CNT) * (float)adj_dcV);			/* Calculate Count to RMS Value	"adj_dcV value find Trail and error Method */
            dcVolt_ACT_SUM = 0;
            dc_Volt_CAL_CNT = 0;
        }
	
	/* DC Current Calcualtion */
	
	dc_I_Bus_cnt = (uint16_t)low_pass_filter(dc_I_Bus, dc_I_Bus_prev_filtered_cnt, 0.2);
	dc_I_Bus_prev_filtered_cnt = dc_I_Bus_cnt;
	
	dc_Bus_I_Cnt = ( dc_I_Bus_cnt - DC_I_OFFSET);							/* Read the Data from Register */
	
        dc_I_SUM +=  dc_Bus_I_Cnt;
        dc_I_Cal_CNT++;
        if(dc_I_Cal_CNT >= 50)/* 50 sample average */						/* This Average value is used for DC Current Fault Purpose and CAN Trans data */
        {
            dc_I_AVG = (int16_t)( (dc_I_SUM / 50) );
            dc_Bus_I_DF = ((df_Cof_DC_I_Avg * dc_I_AVG)+( (1 - df_Cof_DC_I_Avg) * dc_Bus_I_DF));	    
            dc_I_RMS = (float)( dc_Bus_I_DF /(float)dc_I_MF);					/* To convert Count To SI, Current sensor data sheet have 5mv/A so this value is 4.1 "5mv=1A=4.1Cnt */
            dc_I_Cal_CNT = 0;
            dc_I_SUM = 0;
        }
	// Step 3: Subtract offset to center around 0
        //iA_ = (int16_t)(ac_R_Ph_I_Cnt - U_PHA_I_OFFSET);  // Range: -2048 to +2047
        //iB_ = (int16_t)(ac_Y_Ph_I_Cnt - V_PHA_I_OFFSET);
 
        // Step 4: Normalize to Q15 range [-32768, +32767]
        //iA_filteredCnt = (int16_t)(((int32_t)iA_ << 15) / 2048);
        //iB_filteredCnt = (int16_t)(((int32_t)iB_ << 15) / 2048);  
	
	Sine_signed_value = Signed_ResolverCount(U_FilteredSine_Cnt,2059U,0.000808f);
	
	Sine_signed_value1 = (Sine_signed_value * 0.000808f);
        
	/*Applying the the filter for ADC Count for cos */
	U_FilteredCos_Cnt = (uint16_t)low_pass_filter(U_cosCount, U_Prev_FilteredCos_Cnt, 0.2);
	U_Prev_FilteredCos_Cnt = U_FilteredCos_Cnt;
	Cos_signed_value = Signed_ResolverCount(U_FilteredCos_Cnt,2040U,0.000806f);
	Cos_signed_value1 = (Cos_signed_value * 0.000806f);
	//theta_radian =  Resolver_Theta(Sine_signed_value1,Cos_signed_value1);
	//RotarTheta = RadianToDegreeConversion(theta_radian);
	
	/* Motor Temperature Measurement */	
	motor_Temp_V_Cnt = MOTOR_TEMP_CNT;										/* Read the Data from Register */
	motor_Temp_V = ((df_Cof_MOT_Temp * motor_Temp_V_Cnt)+( (1 - df_Cof_MOT_Temp) * per_Motor_Temp_V_DF));	/* Adding Digital Filter */
        per_Motor_Temp_V_DF = motor_Temp_V;
	
	/* Inverter Temperature Measurement */	
	inv_R_Ph_Temp_V_Cnt = INV_R_PH_TEMP_CNT;									/* Read the Data from Register */
	inv_R_Ph_Temp_V = ((df_Cof_INV_Temp * inv_R_Ph_Temp_V_Cnt)+( (1 - df_Cof_INV_Temp) * per_Inv_R_Ph_Temp_V_DF));	/* Adding Digital Filter */
        per_Inv_R_Ph_Temp_V_DF = inv_R_Ph_Temp_V;
	
	inv_Y_Ph_Temp_V_Cnt = INV_Y_PH_TEMP_CNT;									/* Read the Data from Register */
        inv_Y_Ph_Temp_V = ((df_Cof_INV_Temp * inv_Y_Ph_Temp_V_Cnt)+( (1 - df_Cof_INV_Temp) * per_Inv_Y_Ph_Temp_V_DF));	/* Adding Digital Filter */
        per_Inv_Y_Ph_Temp_V_DF = inv_Y_Ph_Temp_V;
	
	inv_B_Ph_Temp_V_Cnt = INV_B_PH_TEMP_CNT;									/* Read the Data from Register */
        inv_B_Ph_Temp_V = ((df_Cof_INV_Temp * inv_B_Ph_Temp_V_Cnt)+( (1 - df_Cof_INV_Temp) * per_Inv_B_Ph_Temp_V_DF));	/* Adding Digital Filter */
        per_Inv_B_Ph_Temp_V_DF = inv_B_Ph_Temp_V;
	
	
	/* TPS Calculation */ 
	tps1_Cnt = TPS1_CNT;									/* Read the Data from Register */
        tps1_V_Cnt = (float)((df_Cof_TPS * tps1_Cnt)+( (1 - df_Cof_TPS) * per_TPS1_V_DF));	/* Adding Digital Filter */
        per_DC_Bus_I_DF = dc_Bus_I;
        per_TPS1_V_DF = (float)tps1_V_Cnt;
	
	theta_radian = (float)(atan2(Sine_signed_value1, Cos_signed_value1)); // theta calculation in radian
	Rotar_ThetaRadian = theta_radian;
	theta_in_degree = (theta_radian * 57.32);
	if(theta_in_degree < 0)
	{
		theta_in_degree += 360;
	}
	RotarTheta = theta_in_degree;
	//Sine_Theta = sinf(RotarTheta);
/*	if(count < 2000 && flag1 == 1)
	{       
		//sine_filtered_array[count] = U_FilteredSine_Cnt;//Sine_signed_value;// U_FilteredSine_Cnt;
		//cos_filtered_array[count] = U_FilteredCos_Cnt;//Cos_signed_value;// U_FilteredCos_Cnt;
		//sine_offset_array[count] = Sine_signed_value;
		//cos_offset_array[count] = Cos_signed_value;
		//sine_offset_array1[count] = Sine_signed_value1;
		//cos_offset_array1[count] = Cos_signed_value1;
		//Radian[count] = theta_radian;
		//Ia_cnt_raw[count] = Ia_cnt;
		//Ib_cnt_raw[count] = Ib_cnt;
		//iA_fil_Cnt[count] = ac_R_Ph_I_Cnt;
		//iB_fil_Cnt[count] = ac_Y_Ph_I_Cnt;
		//iA_off_fil_Cnt[count] = iA_filteredCnt;
		//iB_off_fil_Cnt[count] = iB_filteredCnt;
	   	//RotarTheta_array[count] = theta_in_degree;
		
		count++;
	}
	else
	{
		count = 0;
		flag1 = 0;
	}*/
	
	
	R_Config_ADCA0_ScanGroup1_OperationOff();
}

	