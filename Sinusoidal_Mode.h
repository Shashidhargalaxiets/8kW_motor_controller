
#ifndef	SINUSOIDAL_MODE_H
#define SINUSOIDAL_MODE_H

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"

#define SPWM		0 /* 1 SPWM Activate, 0 SVPWM Activate */
			  /* If SPWM Activate means should change limits values */

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/


/**
****************************************************************************************************************************
* Function Name: Sinusoidal_MODE
* Description  : This function is use to Run the Motor in Sinusoidal Mode
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void Sinusoidal_MODE(void);
/**
****************************************************************************************************************************
* Function Name: Angle_Conversion
* Description  : This function is use to convert Low Range of Angle Value to High Range of Angle Value
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void Angle_Conversion(void);

/**
*****************************************************************************************
* @brief This function is to convert Ia, Ib to Ialpha and Ibeta
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Clark_Transfer(void);
/**
*****************************************************************************************
* @brief This function is to convert Ialpha , Ibeta to Iq and Id
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Park_Transfer(void);
/**
*****************************************************************************************
* @brief This function is to maintain direct axis of the flux PI to be zero
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Flux_PI(void);
/**
*****************************************************************************************
* @brief This function is to operate quadrature axis using Id and speed PI output
* @n 		control signals
* @details
* @n @b Usage: 
* @param None
* @return None
*****************************************************************************************
*/
void Torque_PI(void);

#endif /* SINUSOIDAL_MODE_H */