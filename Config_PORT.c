
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "Config_PORT.h"
#include "cg_PORT.h"

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void PWM_R_Pins_Create(void)
{
    /* PWM_R_TOP */
    PORT.PIBC10 &= _PORT_CLEAR_BIT0;
    PORT.PBDC10 &= _PORT_CLEAR_BIT0;
    PORT.PM10 |= _PORT_SET_BIT0;
    PORT.PMC10 &= _PORT_CLEAR_BIT0;
    PORT.PIPC10 &= _PORT_CLEAR_BIT0;
    PORT.PFC10 |= _PORT_SET_BIT0;
    PORT.PFCE10 |= _PORT_SET_BIT0;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT0;
    PORT.PMC10 |= _PORT_SET_BIT0;
    PORT.PM10 &= _PORT_CLEAR_BIT0;
    
    /* PWM_R_BOT  */
    PORT.PIBC10 &= _PORT_CLEAR_BIT1;
    PORT.PBDC10 &= _PORT_CLEAR_BIT1;
    PORT.PM10 |= _PORT_SET_BIT1;
    PORT.PMC10 &= _PORT_CLEAR_BIT1;
    PORT.PIPC10 &= _PORT_CLEAR_BIT1;
    PORT.PFC10 |= _PORT_SET_BIT1;
    PORT.PFCE10 |= _PORT_SET_BIT1;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT1;
    PORT.PMC10 |= _PORT_SET_BIT1;
    PORT.PM10 &= _PORT_CLEAR_BIT1;

    /* PWM_Y_TOP */
    PORT.PIBC10 &= _PORT_CLEAR_BIT2;
    PORT.PBDC10 &= _PORT_CLEAR_BIT2;
    PORT.PM10 |= _PORT_SET_BIT2;
    PORT.PMC10 &= _PORT_CLEAR_BIT2;
    PORT.PIPC10 &= _PORT_CLEAR_BIT2;
    PORT.PFC10 |= _PORT_SET_BIT2;
    PORT.PFCE10 |= _PORT_SET_BIT2;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT2;
    PORT.PMC10 |= _PORT_SET_BIT2;
    PORT.PM10 &= _PORT_CLEAR_BIT2;    

    /* PWM_Y_BOT */
    PORT.PIBC10 &= _PORT_CLEAR_BIT3;
    PORT.PBDC10 &= _PORT_CLEAR_BIT3;
    PORT.PM10 |= _PORT_SET_BIT3;
    PORT.PMC10 &= _PORT_CLEAR_BIT3;
    PORT.PIPC10 &= _PORT_CLEAR_BIT3;
    PORT.PFC10 |= _PORT_SET_BIT3;
    PORT.PFCE10 |= _PORT_SET_BIT3;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT3;
    PORT.PMC10 |= _PORT_SET_BIT3;
    PORT.PM10 &= _PORT_CLEAR_BIT3;

    /* PWM_B_TOP */
    PORT.PIBC10 &= _PORT_CLEAR_BIT4;
    PORT.PBDC10 &= _PORT_CLEAR_BIT4;
    PORT.PM10 |= _PORT_SET_BIT4;
    PORT.PMC10 &= _PORT_CLEAR_BIT4;
    PORT.PIPC10 &= _PORT_CLEAR_BIT4;
    PORT.PFC10 |= _PORT_SET_BIT4;
    PORT.PFCE10 |= _PORT_SET_BIT4;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT4;
    PORT.PMC10 |= _PORT_SET_BIT4;
    PORT.PM10 &= _PORT_CLEAR_BIT4;

    /* PWM_B_BOT */
    PORT.PIBC10 &= _PORT_CLEAR_BIT5;
    PORT.PBDC10 &= _PORT_CLEAR_BIT5;
    PORT.PM10 |= _PORT_SET_BIT5;
    PORT.PMC10 &= _PORT_CLEAR_BIT5;
    PORT.PIPC10 &= _PORT_CLEAR_BIT5;
    PORT.PFC10 |= _PORT_SET_BIT5;
    PORT.PFCE10 |= _PORT_SET_BIT5;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT5;
    PORT.PMC10 |= _PORT_SET_BIT5;
    PORT.PM10 &= _PORT_CLEAR_BIT5;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void R_Config_PORT_Create(void)
{
    /* 15V_PGOOD_uC */
    PORT.PIBC0  |= _PORT_PIBCn4_INPUT_BUFFER_ENABLE;
    PORT.PM0    |= _PORT_PMn4_MODE_INPUT;
    PORT.PMC0   &= _PORT_CLEAR_BIT4;
    PORT.PU0    |= _PORT_PUn4_PULLUP_OFF;
    PORT.PD0    |= _PORT_PDn4_PULLDOWN_OFF;
    
    /* CAN_STB_uC */
    PORT.PM0 &= _PORT_CLEAR_BIT5;
    PORT.PMC0 &= _PORT_CLEAR_BIT5;
    PORT.P0 |= _PORT_Pn5_OUTPUT_LOW;
        
    /* HALL_A */
    PORT.PIBC0  |= _PORT_PIBCn9_INPUT_BUFFER_ENABLE;
    PORT.PM0    |= _PORT_PMn9_MODE_INPUT;
    PORT.PMC0   &= _PORT_CLEAR_BIT9;
    PORT.PU0    |= _PORT_PUn9_PULLUP_OFF;
    PORT.PD0    |= _PORT_PDn9_PULLDOWN_OFF;
    
    /* HALL_B */
    PORT.PIBC0  |= _PORT_PIBCn10_INPUT_BUFFER_ENABLE;
    PORT.PM0    |= _PORT_PMn10_MODE_INPUT;
    PORT.PMC0   &= _PORT_CLEAR_BIT10;
    PORT.PU0    |= _PORT_PUn10_PULLUP_OFF;
    PORT.PD0    |= _PORT_PDn10_PULLDOWN_OFF;
    
    /* HALL_C */
    PORT.PIBC0  |= _PORT_PIBCn11_INPUT_BUFFER_ENABLE;
    PORT.PM0    |= _PORT_PMn11_MODE_INPUT;
    PORT.PMC0   &= _PORT_CLEAR_BIT11;
    PORT.PU0    |= _PORT_PUn11_PULLUP_OFF;
    PORT.PD0    |= _PORT_PDn11_PULLDOWN_OFF;
    
    
    /* OCP_FAULT */
    PORT.PIBC9  |= _PORT_PIBCn1_INPUT_BUFFER_ENABLE;
    PORT.PM9    |= (_PORT_PM9_DEFAULT_VALUE | _PORT_PMn1_MODE_INPUT);
    PORT.PMC9   &= _PORT_CLEAR_BIT1;
    PORT.PU9    |= _PORT_PUn1_PULLUP_OFF;
    PORT.PD9    |= _PORT_PDn1_PULLDOWN_OFF;
    
    
    /* SHT_FLT_PRT */
    PORT.PIBC9  |= _PORT_PIBCn2_INPUT_BUFFER_ENABLE;
    PORT.PM9    |= (_PORT_PM9_DEFAULT_VALUE | _PORT_PMn2_MODE_INPUT);
    PORT.PMC9   &= _PORT_CLEAR_BIT2;
    PORT.PU9    |= _PORT_PUn2_PULLUP_OFF;
    PORT.PD9    |= _PORT_PDn2_PULLDOWN_OFF;
    
    /* REAR_BREAK_uC */
    PORT.PIBC9  |= _PORT_PIBCn3_INPUT_BUFFER_ENABLE;
    PORT.PM9    |= (_PORT_PM9_DEFAULT_VALUE | _PORT_PMn3_MODE_INPUT);
    PORT.PMC9   &= _PORT_CLEAR_BIT3;
    PORT.PU9    |= _PORT_PUn3_PULLUP_OFF;
    PORT.PD9    |= _PORT_PDn3_PULLDOWN_OFF;
    
    /* PARK_SWITCH_uC */
    PORT.PIBC9  |= _PORT_PIBCn4_INPUT_BUFFER_ENABLE;
    PORT.PM9    |= (_PORT_PM9_DEFAULT_VALUE | _PORT_PMn4_MODE_INPUT);
    PORT.PMC9   &= _PORT_CLEAR_BIT4;
    PORT.PU9    |= _PORT_PUn4_PULLUP_OFF;
    PORT.PD9    |= _PORT_PDn4_PULLDOWN_OFF;
    
    /* MODE_SWITCH_uC */
    PORT.PIBC9  |= _PORT_PIBCn5_INPUT_BUFFER_ENABLE;
    PORT.PM9    |= (_PORT_PM9_DEFAULT_VALUE | _PORT_PMn5_MODE_INPUT);
    PORT.PMC9   &= _PORT_CLEAR_BIT5;
    PORT.PU9    |= _PORT_PUn5_PULLUP_OFF;
    PORT.PD9    |= _PORT_PDn5_PULLDOWN_OFF;


//    PORT.PM9 &= _PORT_CLEAR_BIT5;
//    PORT.PMC9 &= _PORT_CLEAR_BIT5;
//    P9.BIT_5 |= _PORT_Pn5_OUTPUT_LOW;
    
    /* GD_ENABLE_uC */
    PORT.PM9 &= _PORT_CLEAR_BIT6;
    PORT.PMC9 &= _PORT_CLEAR_BIT6;
    PORT.P9 |= _PORT_Pn6_OUTPUT_LOW;
    
    /* CRUISE_CONTROL_uC */
    PORT.PIBC10  |= _PORT_PIBCn9_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn9_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT9;
    PORT.PU10    |= _PORT_PUn9_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn9_PULLDOWN_OFF;
    
    /* SIDE_STAND_uC */
    PORT.PIBC10  |= _PORT_PIBCn10_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn10_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT10;
    PORT.PU10    |= _PORT_PUn10_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn10_PULLDOWN_OFF;
    
    /* FORWARD_REVERSE_uC */
    PORT.PIBC10  |= _PORT_PIBCn11_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn11_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT11;
    PORT.PU10    |= _PORT_PUn11_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn11_PULLDOWN_OFF;
        
    /* FRONT_BREAK_uC */
    PORT.PIBC10  |= _PORT_PIBCn12_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn12_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT12;
    PORT.PU10    |= _PORT_PUn12_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn12_PULLDOWN_OFF;
    
    /* KILL_SWITCH_uC */
    PORT.PIBC10  |= _PORT_PIBCn13_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn13_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT13;
    PORT.PU10    |= _PORT_PUn13_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn13_PULLDOWN_OFF;
    
    /* ANTI_THEFT_LOCK_uC */
    PORT.PIBC10  |= _PORT_PIBCn14_INPUT_BUFFER_ENABLE;
    PORT.PM10    |= (_PORT_PM10_DEFAULT_VALUE | _PORT_PMn14_MODE_INPUT);
    PORT.PMC10   &= _PORT_CLEAR_BIT14;
    PORT.PU10    |= _PORT_PUn14_PULLUP_OFF;
    PORT.PD10    |= _PORT_PDn14_PULLDOWN_OFF;
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Config_CAN_PORT(void)
{
	/* CAN_Tx */
    PORT.PMC0    |= _PORT_SET_BIT0;
    PORT.PM0     &= _PORT_CLEAR_BIT0;
    PORT.PIPC0   &= _PORT_CLEAR_BIT0;
    PORT.PFCAE0  &= _PORT_CLEAR_BIT0;
    PORT.PFCE0   &= _PORT_CLEAR_BIT0;
    PORT.PFC0    |= _PORT_CLEAR_BIT0;
    
        /* CAN_Rx */
    PORT.PMC0    |= _PORT_SET_BIT1;
    PORT.PM0     |= _PORT_SET_BIT1;
    PORT.PIPC0   &= _PORT_CLEAR_BIT1;
    PORT.PFCAE0  &= _PORT_CLEAR_BIT1;
    PORT.PFCE0   &= _PORT_CLEAR_BIT1;
    PORT.PFC0    |= _PORT_CLEAR_BIT1;
    
}
 