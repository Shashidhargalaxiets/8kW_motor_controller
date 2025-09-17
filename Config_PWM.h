

#ifndef CONFIG_PWM_H
#define CONFIG_PWM_H

#include "Config_PORT.h"

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define CARRIER_FREQUENCY               16				/* In Khz */	
#define DEAD_TIME			0.0000025			/* In sec */
#define PERIPHERAL_CLOCK                80  				/* In Khz */	
#define CLOCK_DIVIDER			2
#define DUTY_U_PHASE                    (( (PERIPHERAL_CLOCK * 1000000)/CLOCK_DIVIDER)/(CARRIER_FREQUENCY * 1000)*0.5)
#define DUTY_V_PHASE                    (( (PERIPHERAL_CLOCK * 1000000)/CLOCK_DIVIDER)/(CARRIER_FREQUENCY * 1000)*0.5)
#define DUTY_W_PHASE                    (( (PERIPHERAL_CLOCK * 1000000)/CLOCK_DIVIDER)/(CARRIER_FREQUENCY * 1000)*0.5)
#define DEAD_TIME_COUNTS                (PERIPHERAL_CLOCK * 1000000 * DEAD_TIME) 
/**
****************************************************************************************************************************
* @brief This function is to calculate period of the PWM signal
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_Calculate_Timer_Count(void);
/**
****************************************************************************************************************************
* @brief This function for the PWM unint Initialization 
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_INLI(void);
/**
****************************************************************************************************************************
* @brief This function for the PIC unint Initialization 
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_PIC0_Init(void);
/**
****************************************************************************************************************************
* @brief This function for the TAUD unint Initialization 
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_Init_TAUD0(void);
/**
****************************************************************************************************************************
* @brief This function for Start the PWM signal
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_START(void);
/**
****************************************************************************************************************************
* @brief This function for Stop the PWM signal
* @details
* @n @b Usage: 
* @param None
* @return None
****************************************************************************************************************************
**/
void PWM_STOP(void);
/**
****************************************************************************************************************************
* @brief This function for Updating PWM signal
* @details
* @n @b Usage: 
* @param None : U phase, V phase, W phase value
* @return None
****************************************************************************************************************************
**/

#endif /* CONFIG_PWM_H */