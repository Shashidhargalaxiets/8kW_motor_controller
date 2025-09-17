#ifndef IO_STATUS_H
#define IO_STATUS_H

#include "Digital_Input_Read.h"
#include "ADC_Result.h"
#include "Motor_Control.h"

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/


/**
*****************************************************************************************
*          Macros  
*****************************************************************************************
*/
#define RST				0
#define STEP_ONE			1
#define STEP_TWO			2

#define ECO_TRAN_SPEED_MAX		500			/* RPM */

#define _25ms				250			/*(Interrupt_Time)100us*250=25ms*/
#define _200ms				8			/*(Fun_Call_Time)25ms*8=200ms*/
#define _400ms				16			/*(Fun_Call_Time)25ms*16=400ms*/
#define _1s				40			/*(Fun_Call_Time)25ms*40=1s*/
#define _180s				7200			/*(Fun_Call_Time)25ms*7200=180s*/

#define _0KMPH				0
#define _1KMPH				11
#define _20KMPH				227//222
#define _40KMPH				454//550
#define _45KMPH				510//600

#define _1PERSENT_TPS			10
#define _40PERSENT_TPS			400
/* Speed Limit Based On Mode */
#define LIMP_HOME_FWD_SPEED_MAX		370			/* RPM */
#define ECO_FWD_SPEED_MAX		550			/* RPM */
#define PWR_FWD_SPEED_MAX		1000			/* RPM */
#define PRK_FWD_SPEED_MAX		100			/* RPM */
#define PRK_REV_SPEED_MAX		100			/* RPM */
#define DRV_SS_ACT_SPEED_MAX		300			/* RPM */
/* DC Current Limit based on Mode */
#define ECO_FOR_DC_I_MAX		110			/* A */
#define PWR_FOR_DC_I_MAX		110			/* A */
#define PRK_FOR_DC_I_MAX		110			/* A */
#define PRK_REV_DC_I_MAX		110 			/* A */

/* Id Min limit MF Based on Mode */
#define LIMP_HOME_Id_MIN_LIM_MF		(float)0
#define ECO_Id_MIN_LIM_MF		(float)0
#define PWR_Id_MIN_LIM_MF		(float)0.42
#define PRK_Id_MIN_LIM_MF		(float)0.0

/* Vd,Vq Max Min Limit Based on Mode */ 
#define LIMP_HOME_FLUX_MIN_LIM		-500
#define LIMP_HOME_TORQUE_MAX_LIM	700
#define ECO_FLUX_MIN_LIM		-900
#define ECO_TORQUE_MAX_LIM		1350
#define PWR_FLUX_MIN_LIM		-1140
#define PWR_TORQUE_MAX_LIM		1350
#define PRK_FLUX_MIN_LIM		-500
#define PRK_TORQUE_MAX_LIM		700

/* Torque Saturate Limit Based on Mode */
#define LIMP_HOME_TORQUE_SAT_MAX_LIM		400
#define DRV_TORQUE_SAT_MAX_LIM		1180
#define PRK_TORQUE_SAT_MAX_LIM		400



/* Speed Derate Values based on Mode */
#define LIMP_HOME_SPEED_DERATE		300
#define DRV_ECO_SPEED_DERATE		520
#define DRV_PWR_SPEED_DERATE		1000
#define PRK_FWD_SPEED_DERATE		50
#define PRK_REV_SPEED_DERATE		50


/**
****************************************************************************************************************************
* Function Name: IO_Read
* Description  : This function is use to Read the IO_Signals
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void IO_Read(void);


/**
****************************************************************************************************************************
* Function Name: Mode_Selection
* Description  : This function is use to Select the moede Based On Input
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/

void Mode_Selection(void);

#endif /* IO_STATUS_H */