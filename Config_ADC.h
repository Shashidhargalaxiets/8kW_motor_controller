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
* File Name        : Config_ADC.h
* Component Version: 1.0
* Device(s)        : R7F701684
* Description      : This file implements device driver for Config_ADCA0.
***********************************************************************************************************************/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "cg_adc.h"

#ifndef CONFIG_ADC_H
#define CONFIG_ADC_H

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define _ADC0_UPPER_LIMIT_TABLE0                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE0                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE1                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE1                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE2                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE2                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE3                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE3                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE4                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE4                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE5                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE5                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE6                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE6                  (0x00000000UL)
#define _ADC0_UPPER_LIMIT_TABLE7                  (0xFFF00000UL)
#define _ADC0_LOWER_LIMIT_TABLE7                  (0x00000000UL)
#define _ADC0_STABILIZATION_TIME_TABLE0           (0x00000010UL)
#define _ADC0_STABILIZATION_TIME_TABLE1           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE2           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE3           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE4           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE5           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE6           (0x00000008UL)
#define _ADC0_STABILIZATION_TIME_TABLE7           (0x00000008UL)
#define _ADC0_SG1_START_POINTER                   (0x00000000UL)
#define _ADC0_SG1_END_POINTER                     (0x0000000FUL)

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
* Function Name: R_Config_ADCA0_Create
* Description  : This function initializes the ADC0 module.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_Create(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_Halt
* Description  : This function halts ADC0.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_Halt(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOn
* Description  : This function turns on the self-diagnostic voltage circuit or update the reference voltage.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOn(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOff
* Description  : This function turns off the self-diagnostic voltage circuit.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_SelfDiagnostic_VoltageCircuitOff(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_ScanGroup1_OperationOn
* Description  : This function starts ADC0 scan group 1 convertion.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_ScanGroup1_OperationOn(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_ScanGroup1_OperationOff
* Description  : This function stops ADC0 scan group 1 convertion.
* Arguments    : None
* Return Value : None
****************************************************************************************************************************
**/
void R_Config_ADCA0_ScanGroup1_OperationOff(void);
/**
****************************************************************************************************************************
* Function Name: R_Config_ADCA0_ScanGroup1_GetResult
* Description  : This function gets A/D conversion result for ADC0 scan group 1.
* Arguments    : buffer -
*                    buffer pointer
*                buffer_size -
*                    the size of buffer
* Return Value : MD_STATUS -
*                    MD_OK or MD_ARGERROR
****************************************************************************************************************************
**/
MD_STATUS R_Config_ADCA0_ScanGroup1_GetResult(uint16_t * const buffer, uint8_t buffer_size);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif /* CONFIG_ADC_H */