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
* File Name        : Config_OSTM.c
* Component Version: 1.0
* Device(s)        : R7F701690
* Description      : This file implements device driver for Config_OSTM0.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "Config_OSTM.h"
#include "CAN.h"
#include "IO_Status.h"
#include "Digital_Input_Read.h"
#include"Task_100us.h"

/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

uint8_t TASK_100us_FLAG = 0;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_OSTM0_Create(void)
{
    /* Disable OSTM0 operation */
    OSTM0.TT = _OSTM_COUNTER_STOP;
    /* Disable OSTM0 interrupt operation and clear request */
    INTC2.ICOSTM0.BIT.MKOSTM0 = _INT_PROCESSING_DISABLED;
    INTC2.ICOSTM0.BIT.RFOSTM0 = _INT_REQUEST_NOT_OCCUR;
    /* Set OSTM0 interrupt setting */
    INTC2.ICOSTM0.BIT.TBOSTM0 = _INT_TABLE_VECTOR;
    INTC2.ICOSTM0.UINT16 &= _INT_PRIORITY_HIGHEST;
    /* Set OSTM0 control setting */
    OSTM0.CTL = _OSTM_MODE_INTERVAL_TIMER | _OSTM_START_INTERRUPT_DISABLE;
    OSTM0.CMP = _OSTM0_COMPARING_COUNTER;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_OSTM0_Start(void)
{
    /* Clear OSTM0 interrupt request and enable operation */
    INTC2.ICOSTM0.BIT.RFOSTM0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICOSTM0.BIT.MKOSTM0 = _INT_PROCESSING_ENABLED;
    /* Enable OSTM0 operation */
    OSTM0.TS = _OSTM_COUNTER_START;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_OSTM0_Stop(void)
{
    /* Disable OSTM0 operation */
    OSTM0.TT = _OSTM_COUNTER_STOP;
    /* Disable OSTM0 interrupt operation and clear request */
    INTC2.ICOSTM0.BIT.MKOSTM0 = _INT_PROCESSING_DISABLED;
    INTC2.ICOSTM0.BIT.RFOSTM0 = _INT_REQUEST_NOT_OCCUR;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_OSTM0_Set_CompareValue(uint32_t value)
{
    OSTM0.CMP = value;
}


/**
****************************************************************************************************************************
* Function Name: r_Config_OSTM0_interrupt
* Description  : This function handles the INTOSTM0 interrupt.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
#pragma interrupt r_Config_OSTM0_interrupt(enable=false, channel=84, fpu=true, callt=false)
void r_Config_OSTM0_interrupt(void)
{
	/* This Interrupr is happens Every 100us Time Intervel */
	TASK_100us_FLAG = 1u;
	Task_100micro();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
