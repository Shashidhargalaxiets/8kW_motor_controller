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
* File Name        : Config_TAUB0_0.h
* Component Version: 1.5.1
* Device(s)        : R7F701684
* Description      : This file implements device driver for Config_TAUB0_0.
***********************************************************************************************************************/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "cg_taub.h"

#ifndef CFG_Config_TAUB0_0_H
#define CFG_Config_TAUB0_0_H

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/

#define TAUB0_0_INT_FREQ				1000					/* In Hz */
#define SYS_FREQ					40000000 				/* In Hz */
#define CLOCK_DIVIDER_TAUB0				2
#define _TAUB00_COMPARE_VALUE              		((SYS_FREQ/CLOCK_DIVIDER_TAUB0) / ( TAUB0_0_INT_FREQ)) /* Data register for compare values */

/**
****************************************************************************************************************************
*	Typedef definitions
****************************************************************************************************************************
**/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/**
****************************************************************************************************************************
* Function Name: R_Config_TAUB0_0_Create
* Description  : This function initializes the TAUB00 channel.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/

void R_Config_TAUB0_0_Create(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_TAUB0_0_Start
* Description  : This function starts the TAUB00 channel counter.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_TAUB0_0_Start(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_TAUB0_0_Stop
* Description  : This function stop the TAUB00 channel counter.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_TAUB0_0_Stop(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif