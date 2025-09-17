/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_OSTM0.h
* Component Version: 1.0
* Device(s)        : R7F701690
* Description      : This file implements device driver for Config_OSTM0.
***********************************************************************************************************************/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "cg_ostm.h"

#ifndef Config_OSTM_H
#define Config_OSTM_H

/**
****************************************************************************************************************************
*	Macro definitions (Register bit)
****************************************************************************************************************************
**/

#define OSTM_INT_FREQ				5000				/* In Hz */
#define SYS_FREQ				40000000			/* In Hz */
/* OSTMn Compare Register (OSTMnCMP) */
#define _OSTM0_COMPARING_COUNTER             	( (SYS_FREQ /OSTM_INT_FREQ)-1) /* Compare match value */

/**
****************************************************************************************************************************
*	Typedef definitions
****************************************************************************************************************************
**/

/**
****************************************************************************************************************************
*	Global functions
****************************************************************************************************************************
**/

/**
****************************************************************************************************************************
* Function Name: R_Config_OSTM0_Create
* Description  : This function initializes the OS timer.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_OSTM0_Create(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_OSTM0_Start
* Description  : This function enables the OS timer.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_OSTM0_Start(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_OSTM0_Stop
* Description  : This function stops the OS timer.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_OSTM0_Stop(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_OSTM0_Set_CompareValue
* Description  : This function sets counter value of OS timer.
* Arguments    : value -
*                    counter value
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_OSTM0_Set_CompareValue(uint32_t value);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif /* Config_OSTM_H */
