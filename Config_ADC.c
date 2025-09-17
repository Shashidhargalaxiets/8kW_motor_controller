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
* File Name        : Config_ADC.c
* Component Version: 1.0
* Device(s)        : R7F701684
* Description      : This file implements device driver for Config_ADCA0.
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
#include "Config_ADC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_Create(void)
{
    /* Disable ADC0 error interrupt (INTADCA0ERR) operation and clear request */
    INTC2.ICADCA0ERR.BIT.MKADCA0ERR = _INT_PROCESSING_DISABLED;
    INTC2.ICADCA0ERR.BIT.RFADCA0ERR = _INT_REQUEST_NOT_OCCUR;
    /* Disable ADC0 SG1 end interrupt (INTADCA0I0) operation and clear request */
    INTC1.ICADCA0I0.BIT.MKADCA0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICADCA0I0.BIT.RFADCA0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Set ADC0 SG1 end interrupt (INTADCA0I0) setting */
    INTC1.ICADCA0I0.BIT.TBADCA0I0 = _INT_TABLE_VECTOR;
    INTC1.ICADCA0I0.UINT16 &= _INT_PRIORITY_LOWEST;
    /* Set ADC0 virtual channel setting */
    ADCA0.VCR00.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI00; /* Motor_Temp_uC */ 
    ADCA0.VCR01.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI01; /* R_PHASE_V_uC */
    ADCA0.VCR02.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI02; /* Y_PHASE_V_uC */
    ADCA0.VCR03.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI03; /* B_PHASE_V_uC */
    ADCA0.VCR04.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI04; /* R_PHASE_I_uC */
    ADCA0.VCR05.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI05; /* Y_PHASE_I_uC */
    ADCA0.VCR06.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI06; /* B_PHASE_I_uC */
    ADCA0.VCR07.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI07; /* DC_BUS_I_uC */
    ADCA0.VCR08.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI08; /* DC_BUS_V_uC */
    ADCA0.VCR09.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI09; /* Temp_R_Phase_uC */
    ADCA0.VCR10.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI10; /* Temp_Y_Phase_uC */
    ADCA0.VCR11.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI11; /* Temp_B_Phase_uC */
    ADCA0.VCR12.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI12; /* TPS_Level1_uC */
    ADCA0.VCR13.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI13; /* TPS_Level2_uC*/
    ADCA0.VCR14.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI14; /* 12V_PGOOD_uC */
    ADCA0.VCR15.UINT32 = _ADC_MPX_DISABLE | _ADC_VIRTUAL_CHANNEL_END_INT_ENABLE | _ADC_LIMIT_TABLE_SELECT_NONE | 
                         _ADC_PHYSICAL_CHANNEL_ANI15; /* 5V_PGOOD_uC */
			 
    /* Set ADC0 operation setting */
    ADCA0.ADCR.UINT32 = _ADC_SYNC_SUSPEND | _ADC_12_BIT_MODE | _ADC_RIGHT_ALIGNED;
    ADCA0.SMPCR.UINT32 = _ADC_SAMPLING_18_CYCLES;
    /* Set ADC0 stabilization time setting */
    ADCA0.MPXSTBTR0.UINT32 = _ADC0_STABILIZATION_TIME_TABLE0;
    ADCA0.MPXSTBTR1.UINT32 = _ADC0_STABILIZATION_TIME_TABLE1;
    ADCA0.MPXSTBTR2.UINT32 = _ADC0_STABILIZATION_TIME_TABLE2;
    ADCA0.MPXSTBTR3.UINT32 = _ADC0_STABILIZATION_TIME_TABLE3;
    ADCA0.MPXSTBTR4.UINT32 = _ADC0_STABILIZATION_TIME_TABLE4;
    ADCA0.MPXSTBTR5.UINT32 = _ADC0_STABILIZATION_TIME_TABLE5;
    ADCA0.MPXSTBTR6.UINT32 = _ADC0_STABILIZATION_TIME_TABLE6;
    ADCA0.MPXSTBTR7.UINT32 = _ADC0_STABILIZATION_TIME_TABLE7;
    /* Set ADC0 error check setting */
    ADCA0.SFTCR.UINT32 = _ADC_READ_CLEAR_DISABLE | _ADC_LIMIT_ERROR_INT_ENABLE | _ADC_OVERWRITE_ERROR_INT_ENABLE;
    ADCA0.ULLMTBR0.UINT32 = _ADC0_UPPER_LIMIT_TABLE0 | _ADC0_LOWER_LIMIT_TABLE0;
    ADCA0.ULLMTBR1.UINT32 = _ADC0_UPPER_LIMIT_TABLE1 | _ADC0_LOWER_LIMIT_TABLE1;
    ADCA0.ULLMTBR2.UINT32 = _ADC0_UPPER_LIMIT_TABLE2 | _ADC0_LOWER_LIMIT_TABLE2;
    ADCA0.ULLMTBR3.UINT32 = _ADC0_UPPER_LIMIT_TABLE3 | _ADC0_LOWER_LIMIT_TABLE3;
    ADCA0.ULLMTBR4.UINT32 = _ADC0_UPPER_LIMIT_TABLE4 | _ADC0_LOWER_LIMIT_TABLE4;
    ADCA0.ULLMTBR5.UINT32 = _ADC0_UPPER_LIMIT_TABLE5 | _ADC0_LOWER_LIMIT_TABLE5;
    ADCA0.ULLMTBR6.UINT32 = _ADC0_UPPER_LIMIT_TABLE6 | _ADC0_LOWER_LIMIT_TABLE6;
    ADCA0.ULLMTBR7.UINT32 = _ADC0_UPPER_LIMIT_TABLE7 | _ADC0_LOWER_LIMIT_TABLE7;
    /* Set ADC0 self-diagnosis setting */
    ADCA0.DGCTL0.UINT32 = _ADC_SELF_DIAG_VOLTAGE_LEVEL_1;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH00_SEL_ANI00;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH01_SEL_ANI01;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH02_SEL_ANI02;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH03_SEL_ANI03;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH04_SEL_ANI04;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH06_SEL_ANI06;
    ADCA0.DGCTL1.UINT32 |= _ADC_SELF_DIAG_CH07_SEL_ANI07;
    /* Set ADC0 T&H setting */
    ADCA0.THER.UINT32 = _ADC_TH3_DISABLED | _ADC_TH2_DISABLED | _ADC_TH1_DISABLED | _ADC_TH0_DISABLED;
    /* Set ADC0 scan group setting */
    ADCA0.SGCR1.UINT32 = _ADC_SG_SCAN_MODE_MULTICYCLE | _ADC_SG_SCAN_END_INT_ENABLE | _ADC_SG_CHANNEL_REPEAT_TIME_1;
    ADCA0.SGVCSP1.UINT32 = _ADC0_SG1_START_POINTER;
    ADCA0.SGVCEP1.UINT32 = _ADC0_SG1_END_POINTER;
    ADCA0.SGMCYCR1.UINT32 = _ADC_SG_MULTICYCLE_NUMBER_1;
    /* Set ADC0 scan group trigger enable */
    ADCA0.SGCR1.UINT32 |= _ADC_SG_HW_TRIGGER_DISABLE;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_Halt(void)
{
    /* All scan groups are halted and initialized */
    ADCA0.ADHALTR.UINT32 = _ADC_HALT;
    /* Disable ADC0 SG1 end interrupt (INTADCA0I0) operation and clear request */
    INTC1.ICADCA0I0.BIT.MKADCA0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICADCA0I0.BIT.RFADCA0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    __syncp();
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOn(void)
{
    /* The self-diagnostic voltage circuit is turned on, or the reference voltage is updated */
    ADCA0.ADCR.UINT32 |= _ADC_SELF_DIAG_VOLTAGE_CIRCUIT_ON;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOff(void)
{
    /* The self-diagnostic voltage circuit is turned off */
    ADCA0.ADCR.UINT32 &= _ADC_SELF_DIAG_VOLTAGE_CIRCUIT_OFF;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_ScanGroup1_OperationOn(void)
{
    /* Enable ADC0 SG1 operation */
    ADCA0.SGSTCR1.UINT32 = _ADC_START;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_ADCA0_ScanGroup1_OperationOff(void)
{
    /* Disable ADC0 SG1 operation */
    ADCA0.SGSTPCR1.UINT32 = _ADC_STOP;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
MD_STATUS R_Config_ADCA0_ScanGroup1_GetResult(uint16_t * const buffer, uint8_t buffer_size)
{
    uint8_t start_pointer;
    uint8_t end_pointer;
    uint8_t count_num;
    uint8_t buffer_index;
    uint32_t * p_addr;
    uint32_t convert_data;

    start_pointer = (uint8_t)ADCA0.SGVCSP1.UINT32;
    end_pointer = (uint8_t)ADCA0.SGVCEP1.UINT32;
    count_num = (end_pointer - start_pointer) + 1U;
    if (buffer_size < count_num)
    {
        return MD_ARGERROR;
    }

    p_addr = (uint32_t*)(_ADC0_VCHANNEL_DATA_BASE + (2U * start_pointer));

    for (buffer_index = 0U; buffer_index < count_num; buffer_index = buffer_index + 2U)
    {
        convert_data = (uint32_t) * p_addr;
        buffer[buffer_index] = (uint16_t)(convert_data & 0x0000FFFFUL);
        if ((count_num - buffer_index) > 1U)
        {
            buffer[buffer_index + 1U] = (uint16_t)((convert_data & 0xFFFF0000UL) >> 16U);
        }
        p_addr++;
    }

    return MD_OK;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
