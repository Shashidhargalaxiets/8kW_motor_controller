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
* File Name        : Config_TAUB0_0.c
* Component Version: 1.5.1
* Device(s)        : R7F701684
* Description      : This file implements device driver for Config_TAUB0_0.
***********************************************************************************************************************/
/**
****************************************************************************************************************************
*	Pragma directive
****************************************************************************************************************************
**/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "Config_TAUB0_0.h"
#include "CAN.h"
#include "CAN_TX.h"
#include "Digital_Input_Read.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

extern uint8_t hand_Shak_Latch;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/

uint8_t rx_ID506_CAN_Time_OUT_Err = 0;
uint8_t rx_ID501_CAN_Time_OUT_Err = 0;
uint8_t rx_IDA1_CAN_Time_OUT_Err = 0;
uint8_t rx_IDA2_CAN_Time_OUT_Err = 0;
uint8_t can_Time_Out_Error = 0;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
uint16_t taub0_0_CNT = 0;
uint8_t taub0_0_WDT_RST_Cnt = 0;

uint8_t test_Cnt_WDT = 5;
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_TAUB0_0_Create(void)
{
    /* Disable channel 0 counter operation */
    TAUB0.TT |= _TAUB_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUB0I0 operation and clear request */
    INTC2.ICTAUB0I0.BIT.MKTAUB0I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUB0I0.BIT.RFTAUB0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTTAUB0I0 setting */
    INTC2.ICTAUB0I0.BIT.TBTAUB0I0 = _INT_TABLE_VECTOR;
    INTC2.ICTAUB0I0.UINT16 &= _INT_PRIORITY_LEVEL1;
    TAUB0.TPS &= _TAUB_CK0_PRS_CLEAR;
    TAUB0.TPS |= _TAUB_CK0_PRE_PCLK_1;
    /* Set channel 0 setting */
    TAUB0.CMOR0 = _TAUB_SELECTION_CK0 | _TAUB_COUNT_CLOCK_PCLK | _TAUB_INDEPENDENT_CHANNEL | _TAUB_SOFTWARE_TRIGGER | 
                  _TAUB_OVERFLOW_AUTO_CLEAR | _TAUB_INTERVAL_TIMER_MODE | _TAUB_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUB0.CMUR0 = _TAUB_INPUT_EDGE_UNUSED;
    TAUB0.CDR0 = _TAUB00_COMPARE_VALUE;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_TAUB0_0_Start(void)
{
    /* Clear INTTAUB0I0 request and enable operation */
    INTC2.ICTAUB0I0.BIT.RFTAUB0I0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICTAUB0I0.BIT.MKTAUB0I0 = _INT_PROCESSING_ENABLED;
    /* Enable channel 0 counter operation */
    TAUB0.TS |= _TAUB_CHANNEL0_COUNTER_START;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_TAUB0_0_Stop(void)
{
    /* Disable channel 0 counter operation */
    TAUB0.TT |= _TAUB_CHANNEL0_COUNTER_STOP;
    /* Disable INTTAUB0I0 operation and clear request */
    INTC2.ICTAUB0I0.BIT.MKTAUB0I0 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUB0I0.BIT.RFTAUB0I0 = _INT_REQUEST_NOT_OCCUR;
}
/***********************************************************************************************************************
* Function Name: r_Config_TAUB0_0_interrupt
* Description  : This function is TAUB00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_TAUB0_0_interrupt(enable=false, channel=142, fpu=true, callt=false)
void r_Config_TAUB0_0_interrupt(void)
{
	/* Interrupt is happes on 0.5ms Time Intervel */
	
	/* Manually WDT is reset at Every 2.5ms Intervel, WDT timer is configured for 4ms */
	taub0_0_WDT_RST_Cnt++;
	if(taub0_0_WDT_RST_Cnt >= test_Cnt_WDT)/* 2.5ms cleard */
	{
		R_Config_WDT0_Restart();/* with in 4ms Should be Restart*/
		taub0_0_WDT_RST_Cnt = 0;
	}
	
	
	if(hand_Shak_Latch == 1)
	{
		taub0_0_CNT++;
		CAN_TX();
		if(taub0_0_CNT >= 201)
		{
			taub0_0_CNT = 0;
		}
	}
	
	/* CAN Time Error check for RX data */
	
	 rx_ID506_CAN_Time_OUT_Err++;
         if((rx_ID506_CAN_Time_OUT_Err/2) > ID506_TIME_INTERVEL) 	/* 2 count is equal to 1ms */
	 {
		 can_Time_Out_Error = ACTIVATE;
	 }
	 rx_ID501_CAN_Time_OUT_Err++;
         if(rx_ID501_CAN_Time_OUT_Err > ID501_TIME_INTERVEL)
	 {
		 can_Time_Out_Error = ACTIVATE;
	 }
	 rx_IDA1_CAN_Time_OUT_Err++;
         if(rx_IDA1_CAN_Time_OUT_Err > IDA1_TIME_INTERVEL)
	 {
		 can_Time_Out_Error = ACTIVATE;
	 }
	 rx_IDA2_CAN_Time_OUT_Err++;
         if(rx_IDA2_CAN_Time_OUT_Err > IDA2_TIME_INTERVEL)
	 {
		 can_Time_Out_Error = ACTIVATE;
	 }
/* Start user code for r_Config_TAUB0_0_interrupt. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */