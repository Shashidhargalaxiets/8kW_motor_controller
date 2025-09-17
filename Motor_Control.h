
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "ADC_Result.h"
/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define NO_OF_ELE_CYCLE_WAIT		1

/* All Zero Means Closed Loop */
#define TPZ_MODE			0
#define SINUSOIDAL_SELF_COMMI 	 	0
#define SINUSOIDAL_OPEN_LOOP 		0


#define SPEED_PI			0//1

#define TPS_MF1				1.8
#define TPS_MF2				1.5

#define _50ms				500		/*(Interrupt)100us*500=50ms*/
#define _250ms				2500		/*(Interrupt)100us*2500=25ms*/

#define MINIMUM_THROT			730//512//730//512//730//725//720//770//512//770//512		/* 0.625V=512Cnt for LTVS Throttle*//* 0.9=730Cnt for GETS Throttle */	
#define TORQ_SAT_MIN    		-500

#define RAMP_UP_DELAY			5
#define RAMP_DOWN_DELAY			5

#define DC_I_FOR_MOT_LIMIT_SI		110			/* A */
#define DC_I_REV_MOT_LIMIT_SI		40			/* A */
#define DC_I_REG_LIMIT_SI		-40			/* A */


#define MAX_PWR_W			4500
#define MAX_TORQUE_CNT			1180
#define MAX_TORQUE			140

#define SPEED_REF_FOR_MOT_MODE_SI	1000			/* RPM */
#define SPEED_REF_REV_MOT_MODE_SI	100			/* RPM */

/** Derate Function Values for Voltage and Tesmperature */
#define VOLT_SOFT_START_VAL		44			/* Volt */
#define VOLT_HARD_START_VAL		38			/* Volt */

#define TEMP_SOFT_START_VAL		90			/* Deg */
#define TEMP_HARD_START_VAL		100			/* Deg */

#define TEMP_SOFT_START_VAL_MOT		80			/* Deg */
#define TEMP_HARD_START_VAL_MOT		90			/* Deg */

#define Vs_REF_MAX			1350			/* Cnt */
#define Vs_MAX_FLX_FEEDBACK		1400			/* Cnt */



#define LAMDA_mWb			9			/* mWb */
#define Lq_mH				0.0225			/* mH */
#define Ld_mH				0.02172			/* mH */

/**
****************************************************************************************************************************
* Function Name: Motor_Run_Mode_Select
* Description  : This function to Find the Run the Motor in Trapezoidal and Sinusoidal Mode
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void Motor_Run_Mode_Select(void);
/**
****************************************************************************************************************************
* Function Name: Motor_Run_Mode_Select
* Description  : This function to Find the Run the Motor in Trapezoidal and Sinusoidal Mode
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void Power_Torque_Calculation(void);
/**
*****************************************************************************************
* @brief This function is to control the input Current
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void DC_I_PI(void);
/**
*****************************************************************************************
* @brief This function is to control Speed of the motor
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Speed_PI(void);
/**
*****************************************************************************************
* @brief This function is to control Id Reference Value
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Flux_Ref_PI(void);
/**
*****************************************************************************************
* @brief This function is help to calculate the Id ratio
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void MTPA_Cal(void);
#endif /* MOTOR_CONTROL_H */