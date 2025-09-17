
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "Temperature_Cal.h"
#include "ADC_Result.h"
#include "math.h"
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
extern uint16_t motor_Temp_V;

extern uint16_t inv_R_Ph_Temp_V_Cnt;
extern uint16_t inv_Y_Ph_Temp_V_Cnt;
extern uint16_t inv_B_Ph_Temp_V_Cnt;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
/* Motor Temperature Calculation Variable */
uint16_t mot_Pull_UP_Voltage_mV = 5000;
float mot_Temp_Volt = 0;
uint16_t mot_Temp_R2 = 0;//39000;
float mot_Temp_Current = 0;
float mot_Temp_Com_Res = 0;
float mot_Temp_R2_1 = 0;
//float mot_Temp_R2_Com3 = 0;
uint16_t mot_Temp_R0 = 10000;//50000;
uint16_t mot_Temp_R1 = 10000;//0;
uint16_t mot_Temp_Cel = 0;

/* Inverter Temperature Calculation Variable */
uint16_t inv_Pull_UP_Voltage_mV = 5000;
uint16_t inv_Temp_R1 = 1000;//10000;
uint16_t inv_Temp_R0 = 4700;

uint16_t inv_R_Ph_Temp_Volt = 0;
uint16_t inv_R_Ph_Temp_R2 = 0;
uint16_t inv_R_Ph_Temp_Cel = 0;
uint16_t inv_Y_Ph_Temp_Volt = 0;
uint16_t inv_Y_Ph_Temp_R2 = 0;
uint16_t inv_Y_Ph_Temp_Cel = 0;

uint16_t inv_B_Ph_Temp_Volt = 0;
uint16_t inv_B_Ph_Temp_R2 = 0;
uint16_t inv_B_Ph_Temp_Cel = 0;

uint32_t inv_R_Ph_Temp_Cel_Sum = 0;
uint32_t inv_Y_Ph_Temp_Cel_Sum = 0;
uint32_t inv_B_Ph_Temp_Cel_Sum = 0;
uint32_t mot_Temp_Cel_Sum = 0;

uint16_t temp_Avg_Cnt = 0;

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

void Temp_Cal(void)
{
	/* Celcius Calculation Formula for Motor And Inverter
		Celcius = (1/(1/T0+(1/Beta*Log(R2/R0))))-273.15
		T0=298 is constant
		Beta is based on NTC
		R0=NTC Value 
	*/
       /* Deatils of Calculation in HSI Document */
       
    /* Motor Temperature */
    mot_Temp_Volt = (float)( ((float)motor_Temp_V / 819));						/* Convert Count to Volt */ 													/* voltage=Cnt/819 	 Count to Volt Calculation */
    mot_Temp_Current = (float)(((float)(mot_Pull_UP_Voltage_mV/1000)-(float)(mot_Temp_Volt))/mot_Temp_R1);								/*I=V/R			Calculate the Current */
    mot_Temp_Com_Res = (float)(((float)(mot_Temp_Volt))/((float)mot_Temp_Current));											/* Coman_Res=V/I 	Calculate Common Resistance Vale*/
    mot_Temp_R2_1 = (float)((float)(1/mot_Temp_Com_Res)-(float)0.0001 );												/* mot_Temp_R2_1=1/Coman_Res-1/R2 */
    mot_Temp_R2 = (float)(1/mot_Temp_R2_1);																/* mot_Temp_R2 =(1/mot_Temp_R2_1) Calculate Motor NTC Resistance Value*/
    mot_Temp_Cel_Sum += (uint16_t)( ((1/( (float)0.003354 + ((float)0.00028 * (log(((float)(mot_Temp_R2 )/(float)mot_Temp_R0)))))) - (float)273.15) * 100);		/* Calculate Temperature in Celcius 100 for Remove Float */
  	

    /* Inverter Temperature */
    inv_R_Ph_Temp_Volt = (uint16_t)( ((float)inv_R_Ph_Temp_V_Cnt / 819)* 1000);				/* Convert Count to Mili Volt */	
    inv_R_Ph_Temp_R2 = (uint16_t)((inv_Temp_R1 * inv_R_Ph_Temp_Volt )/ (inv_Pull_UP_Voltage_mV - inv_R_Ph_Temp_Volt));
    inv_R_Ph_Temp_Cel_Sum += (uint16_t)( ((1/( (float)0.003354 + ((float)0.000282 * (log(((float)inv_R_Ph_Temp_R2/(float)inv_Temp_R0)))))) - (float)273.15) * 100);/* 100 for Remove Float */
 
    
    /* Inverter Temperature */
    inv_Y_Ph_Temp_Volt = (uint16_t)( ((float)inv_Y_Ph_Temp_V_Cnt / 819)* 1000);
    inv_Y_Ph_Temp_R2 = (uint16_t)((inv_Temp_R1 * inv_Y_Ph_Temp_Volt )/ (inv_Pull_UP_Voltage_mV - inv_Y_Ph_Temp_Volt));
    inv_Y_Ph_Temp_Cel_Sum += (uint16_t)( ((1/( (float)0.003354 + ((float)0.000282 * (log(((float)inv_Y_Ph_Temp_R2/(float)inv_Temp_R0)))))) - (float)273.15) * 100);/* 100 for Remove Float */

     /* Inverter Temperature */
    inv_B_Ph_Temp_Volt = (uint16_t)( ((float)inv_B_Ph_Temp_V_Cnt / 819)* 1000);
    inv_B_Ph_Temp_R2 = (uint16_t)((inv_Temp_R1 * inv_B_Ph_Temp_Volt )/ (inv_Pull_UP_Voltage_mV - inv_B_Ph_Temp_Volt));
    inv_B_Ph_Temp_Cel_Sum += (uint16_t)( ((1/( (float)0.003354 + ((float)0.000282 * (log(((float)inv_B_Ph_Temp_R2/(float)inv_Temp_R0)))))) - (float)273.15) * 100);/* 100 for Remove Float */

    temp_Avg_Cnt++;
    if(temp_Avg_Cnt >=  1000)
    {
	   inv_R_Ph_Temp_Cel = (int16_t)(inv_R_Ph_Temp_Cel_Sum / temp_Avg_Cnt);
	   inv_Y_Ph_Temp_Cel = (int16_t)(inv_Y_Ph_Temp_Cel_Sum / temp_Avg_Cnt);
	   inv_B_Ph_Temp_Cel = (int16_t)(inv_B_Ph_Temp_Cel_Sum / temp_Avg_Cnt);
	   mot_Temp_Cel = (int16_t)(mot_Temp_Cel_Sum / temp_Avg_Cnt);
	   temp_Avg_Cnt = 0;
	   inv_R_Ph_Temp_Cel_Sum = 0;
	   inv_Y_Ph_Temp_Cel_Sum = 0;
	   inv_B_Ph_Temp_Cel_Sum = 0;
	   mot_Temp_Cel_Sum = 0;
    }
	   
    
}