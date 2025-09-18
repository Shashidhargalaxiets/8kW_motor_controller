

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "Register_Interface.h"
uint16_t adc_val1;
uint16_t adc_val2;

int Pin_State(uint8_t pin)
{
	uint8_t pin_Status = 0;
	
	pin_Status = 10;//pin;
	return pin_Status;
}

void Get_ResolverOutput(uint16_t *U_sineCount,uint16_t *U_cosCount )
{
   *U_sineCount = RESOLVER_SINE;
   *U_cosCount =  RESOLVER_COS;
}

void Current_Feedback(uint16_t *I_a,uint16_t *I_b,uint16_t *I_c )
{
   *I_a = AC_R_PH_I_CNT;
   *I_b = AC_Y_PH_I_CNT;
   *I_c = AC_B_PH_I_CNT;

}

void Voltage_Feedback(uint16_t *V_a,uint16_t *V_b,uint16_t *V_c )
{
   *V_a = AC_R_PH_V_CNT;
   *V_b = AC_Y_PH_V_CNT;
   *V_c = AC_B_PH_V_CNT;

}

void Get_DC_quantities(uint16_t *dc_V,uint16_t *dc_I )
{
   *dc_V = DC_BUS_V_CNT;
   *dc_I = DC_BUS_I_CNT;
}
//int Pin_Set(uint8_t pin)
//{
//	pin = SET; 
//}
//inr Pin_Clear(uint8_t pin)
//{
//	pin = CLEAR;
//}