
#ifndef FAULT_ANALYSIS_H
#define FAULT_ANALYSIS_H
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define NO_FAULT		0
#define FAULT			1

#define ENABLE			1
#define DISABLE			0

/* Debounce Time for Faults */
#define HALL_DEBOUNCE			5
#define TPS_DEBOUNCE			50
#define VOLT_MON_DEBOUNCE		5
#define INV_TEMP_HLT_DEBOUNCE		50
#define DC_I_SC_DEBOUNCE		5
#define PH_I_SC_DEBOUNCE		5
#define STALL_DEBOUNCE			1000
#define DC_V_DEBOUNCE			500
#define DC_I_RMS_DEBOUNCE		20
#define PH_I_RMS_DEBOUNCE		20
#define SPEED_DEBOUNCE			500
#define INV_TEMP_DEBOUNCE		500
#define PH_OPN_DEBOUNCE			1000

/* Sensor_Health_Check */
#define MAX_I_SENS_HLTH_LIMI            82			/* 20 A */
#define MIN_I_SENS_HLTH_LIMI            -82			/* -20 A */

#define MAX_DCV_SENS_HLTH_LIMI            3279			/* 81 V */
#define MIN_DCV_SENS_HLTH_LIMI            41			/* 1 V */

#define MAX_PHV_SENS_HLTH_LIMI            32			/* 1 V */
#define MIN_PHV_SENS_HLTH_LIMI            -32			/* -1 V */

#define MAX_TPS_SENS_HLTH_LIMI          4050			/* 4.94 V */
#define MIN_TPS_SENS_HLTH_LIMI          350//164//300		/* if remove throttle it comming 0.38V */ /* 0.2V=164Cnt for LTVS throttle*/	/* 0.36V=300Cnt for GETS throttle */	

#define MAX_MOT_NTC_SENS_HLTH_LIMI      1603			/* 10Deg*/
#define MIN_MOT_NTC_SENS_HLTH_LIMI      11			/* 300 Deg */

#define MAX_INV_TEMP_SENS_HLTH_LIMI     622			/* 138 Deg */
#define MIN_INV_TEMP_SENS_HLTH_LIMI     3669			/* 10 Deg */

#define MAX_15V_POWER_SUPPLY_LIMIT	3955			/* 15.1 V this voltage mention is before voltage divider*/
#define MIN_15V_POWER_SUPPLY_LIMIT	3076			/* 11.6 V this voltage mention is before voltage divider*/

#define MAX_5V_POWER_SUPPLY_LIMIT	2088			/* 5.1 V this voltage mention is before voltage divider*/
#define MIN_5V_POWER_SUPPLY_LIMIT	2006			/* 4.9 V this voltage mention is before voltage divider*/


/* Software Fault Monitor */
#define MAX_DC_BUS_SC_LIMIT             738                    	/* 180 A    */
#define MIN_DC_BUS_SC_LIMIT             -410                   	/* -100 A */

#define MAX_PHASE_SC_LIMIT              1500                   	/* 366 A    */
#define MIN_PHASE_SC_LIMIT              -1500                  	/* -366 A   */        	


/* Stal Protection Fault Monitor */
#define STAL_PROT_SPEED_LIMIT 		20			/* RPM */
#define STAL_PROT_DC_I_LIMIT		60			/* A */
#define STAL_Is_LIMIT			900			/* Cnt */

/* Protection Variable */
#define DC_V_MAX_LIMIT 			 60
#define DC_V_MIN_LIMIT 			 38
#define DC_I_MAX_LIMIT 			 140
#define SPEED_MAX_LIMIT 		 1200
#define PHASE_I_MAX_LIMIT 		 250
#define MOT_TEMP_MAX_LIMIT		 381			/* 90 Deg */				/* if change count to SI Value change Logi also(Opposite condition need to add) */
#define INV_TEMP_MAX_LIMIT 		 1252//1493//1765	/* 100 Deg *//* 90 Deg *//* 80 Deg */	/* if change count to SI Value change Logi also(Opposite condition need to add) */
/**
****************************************************************************************************************************
* @brief This function is to check the Sensor Health Status Monitor
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Sensor_Health_Check(void);
/**
****************************************************************************************************************************
* @brief This function is to check the Run Time Sensor Health Status
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Sensor_Run_Time_Moni(void);
/**
****************************************************************************************************************************
* @brief This function is to check the Hardwar Fault Status Monitor
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Hardware_Fault_Moni(void);
/**
****************************************************************************************************************************
* @brief This function is to check the Software Fault Status
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Software_Fault_Monitor(void);
/**
****************************************************************************************************************************
* @brief This function is to check the Run Time Sensor Health
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Run_Time_Sensor_HLTH_Moni(void);
/**
****************************************************************************************************************************
* @brief This function is to check the Motor Protection Unit
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void Motor_Protection(void);
#endif /* FAULT_ANALYSIS_H */