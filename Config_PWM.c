
/**
*****************************************************************************************
*****************************************************************************************
***********************************************
* @file Config_PWM.c 
* @details Inilization of PWM signal 
* @note 
* @copyright
*****************************************************************************************
*****************************************************************************************
***********************************************
*/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "cg_pwm.h"
#include "Config_PWM.h"

/**
****************************************************************************************************************************
*	Extern variables 
****************************************************************************************************************************
**/

/**
****************************************************************************************************************************
*	Global variables 
****************************************************************************************************************************
**/
unsigned int Timer_Count = 0;

/**
****************************************************************************************************************************
*	See header file for function definition 
****************************************************************************************************************************
**/
/**
****************************************************************************************************************************
*	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_Calculate_Timer_Count(void)
{
	unsigned int Clock_Divider;
	unsigned long Timer_clock;
	unsigned char loop;
	Clock_Divider = 1;
	for((loop = (unsigned char)_TAUD_CK0_PRE_PCLK_1); loop>0; loop--)
	{
		Clock_Divider = Clock_Divider * 2;
	
	}
		Timer_clock = (PERIPHERAL_CLOCK * 1000000) / Clock_Divider;
		Timer_Count = Timer_clock / (CARRIER_FREQUENCY * 1000);
}
/**
****************************************************************************************************************************
* 	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_Init_TAUD0(void)
{
	
    /* Disable channel2 counter operation */
    TAUD0.TT |= _TAUD_CHANNEL0_COUNTER_STOP | _TAUD_CHANNEL2_COUNTER_STOP | _TAUD_CHANNEL3_COUNTER_STOP | _TAUD_CHANNEL4_COUNTER_STOP| _TAUD_CHANNEL5_COUNTER_STOP | _TAUD_CHANNEL6_COUNTER_STOP 
    	| _TAUD_CHANNEL7_COUNTER_STOP | _TAUD_CHANNEL8_COUNTER_STOP | _TAUD_CHANNEL9_COUNTER_STOP | _TAUD_CHANNEL10_COUNTER_STOP
    	| _TAUD_CHANNEL11_COUNTER_STOP | _TAUD_CHANNEL12_COUNTER_STOP | _TAUD_CHANNEL13_COUNTER_STOP;
    
     // Set TAUD Prescalar 
    TAUD0.TPS &= _TAUD_CK0_PRS_CLEAR;
    TAUD0.TPS |= _TAUD_CK0_PRE_PCLK_1;
    	
    /* Set channel 2 setting */
    TAUD0.CMOR2 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                  _TAUD_START_TRIGGER_SOFTWARE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE | 
                  _TAUD_START_INT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR2 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR2  = Timer_Count;	
    
    /* Set channel 4 setting */
    TAUD0.CMOR4 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_UP_DOWN_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_COUNT_UP_DOWN_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR4 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR4  = DUTY_U_PHASE;
    
    /* Set channel 5 setting */
    TAUD0.CMOR5 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_DEAD_TIME_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR5 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR5  = DEAD_TIME_COUNTS;
    
    /* Set channel 6 setting */
    TAUD0.CMOR6 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_UP_DOWN_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_COUNT_UP_DOWN_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR6 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR6  = DUTY_V_PHASE;
    
    /* Set channel 7 setting */
    TAUD0.CMOR7 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_DEAD_TIME_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR7 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR7  = DEAD_TIME_COUNTS;

    /* Set channel 8 setting */
    TAUD0.CMOR8 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_UP_DOWN_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_COUNT_UP_DOWN_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */	  
    TAUD0.CMUR8 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR8  = DUTY_W_PHASE;

    /* Set channel 9 setting */
    TAUD0.CMOR9 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_DEAD_TIME_OUTPUT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR9 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR9  = DEAD_TIME_COUNTS;

    /* Set channel 10 setting */
    TAUD0.CMOR10 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                  _TAUD_START_TRIGGER_VALID_EDGE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR10 = _TAUD_INPUT_EDGE_BOTH_MEASURE_LOW;
    TAUD0.CDR10  = DUTY_U_PHASE;

    /* Set channel 11 setting */
    TAUD0.CMOR11 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_PULSE_ONECOUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR11 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR11  = 0;

    /* Set channel 12 setting */
    TAUD0.CMOR12 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                  _TAUD_START_TRIGGER_VALID_EDGE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR12 = _TAUD_INPUT_EDGE_BOTH_MEASURE_LOW;
    TAUD0.CDR12  = DUTY_V_PHASE;

    /* Set channel 13 setting */
    TAUD0.CMOR13 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_PULSE_ONECOUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;;
    /* Set compare match register */
    TAUD0.CMUR13 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR13  = 0; 

    /* Set channel 14 setting */
    TAUD0.CMOR14 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                  _TAUD_START_TRIGGER_VALID_EDGE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR14 = _TAUD_INPUT_EDGE_BOTH_MEASURE_LOW;
    TAUD0.CDR14 = DUTY_W_PHASE;

    /* Set channel 15 setting */
    TAUD0.CMOR15 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                  _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_PULSE_ONECOUNT_MODE | 
                  _TAUD_START_INT_NOT_GENERATED;;
    /* Set compare match register */
    TAUD0.CMUR15 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR15 = 0;

    /* Set output mode setting */
    TAUD0.TO  = 0xA800;
    TAUD0.TOE = 0x0000;
    TAUD0.TOM = 0x03F0;
    TAUD0.TOC = 0xABF0;
    TAUD0.TOL = 0xA800; 
    TAUD0.TDE = 0x03F0;
    TAUD0.TDM = 0x0000;
    TAUD0.TDL = 0x0150;
    TAUD0.TRE = 0x0000;
    TAUD0.TRO = 0x0000;
    TAUD0.TRC = 0x0000;
    TAUD0.TME = 0x0000;
    TAUD0.RDE = 0xFFF5;
    TAUD0.RDS = 0x0000;
    TAUD0.RDM = 0x03F5;
    TAUD0.RDC = 0x0000;
}
/**
****************************************************************************************************************************
* 	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_INLI(void)
{
	PWM_Calculate_Timer_Count();
	PWM_Init_TAUD0();
	PWM_PIC0_Init();
	PWM_R_Pins_Create();
	
}
/**
****************************************************************************************************************************
*	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_PIC0_Init(void)
{
    /* Select the TIN input signal to TAUDTTIN10, TAUDTTIN12, and TAUDTTIN14. */
    PIC0.REG200 |= 0x00040000;
    
    PIC0.REG201 |= 0x0AAA0000;
    
    PIC0.REG203 |= 0x00444444;

    PIC0.HIZCEN0 |= 0x00;
    /* Select TAUD0 channel 2 to be used by TAPATSIM0 and TAPATUDCM0 (for generating valley interrupt) */
    PIC0.REG200 |= 0x02000000;
}

/**
****************************************************************************************************************************
*	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_START(void)
{	
      TAUD0.TOE = 0xABF0;
    /******************************** Setting up peak interrupt ********************************/

    /* Enable channel counter operation */
    TAUD0.TS |= (_TAUD_CHANNEL15_COUNTER_START | _TAUD_CHANNEL14_COUNTER_START | _TAUD_CHANNEL13_COUNTER_START | 
                _TAUD_CHANNEL12_COUNTER_START | _TAUD_CHANNEL11_COUNTER_START| _TAUD_CHANNEL10_COUNTER_START| _TAUD_CHANNEL9_COUNTER_START | _TAUD_CHANNEL8_COUNTER_START | _TAUD_CHANNEL7_COUNTER_START | 
                _TAUD_CHANNEL6_COUNTER_START | _TAUD_CHANNEL5_COUNTER_START | _TAUD_CHANNEL4_COUNTER_START | _TAUD_CHANNEL3_COUNTER_START | 
                _TAUD_CHANNEL2_COUNTER_START | _TAUD_CHANNEL1_COUNTER_START| _TAUD_CHANNEL0_COUNTER_START);
}

/**
****************************************************************************************************************************
*	See header file for function definition 
****************************************************************************************************************************
**/
void PWM_STOP(void)
{
	PORT.P10 &= (~(0X0A00));
    /* Disable channel counter operation */
    TAUD0.TT |= ( _TAUD_CHANNEL13_COUNTER_STOP | _TAUD_CHANNEL12_COUNTER_STOP | _TAUD_CHANNEL11_COUNTER_STOP | _TAUD_CHANNEL10_COUNTER_STOP | 
                _TAUD_CHANNEL9_COUNTER_STOP | _TAUD_CHANNEL8_COUNTER_STOP | _TAUD_CHANNEL7_COUNTER_STOP | 
                _TAUD_CHANNEL6_COUNTER_STOP | _TAUD_CHANNEL5_COUNTER_STOP | _TAUD_CHANNEL4_COUNTER_STOP | _TAUD_CHANNEL3_COUNTER_STOP | 
                _TAUD_CHANNEL2_COUNTER_STOP | _TAUD_CHANNEL1_COUNTER_STOP| _TAUD_CHANNEL0_COUNTER_STOP);
    /* Disable INTTAUD0I0 operation and clear request */
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTTAUD0I1 operation and clear request */
    INTC2.ICTAUD0I1.BIT.MKTAUD0I1 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUD0I1.BIT.RFTAUD0I1 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTTAUD0I2 operation and clear request */
    INTC1.ICTAUD0I2.BIT.MKTAUD0I2 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I2.BIT.RFTAUD0I2 = _INT_REQUEST_NOT_OCCUR;
    
    /******************************** Setting up valley interrupt ********************************/
    /* Disable interrupt operation and clear request */
    INTC1.ICTAPA0IVLY0.BIT.MKTAPA0IVLY0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAPA0IVLY0.BIT.RFTAPA0IVLY0 = _INT_REQUEST_NOT_OCCUR;

    /******************************** Setting up peak interrupt ********************************/
    /* Disable interrupt operation and clear request */
    INTC1.ICTAPA0IPEK0.BIT.MKTAPA0IPEK0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAPA0IPEK0.BIT.RFTAPA0IPEK0 = _INT_REQUEST_NOT_OCCUR;
 
    /* Synchronization processing */
    TAUD0.TOE = 0x0000;
    TAUD0.TO = 0xA800;
}
