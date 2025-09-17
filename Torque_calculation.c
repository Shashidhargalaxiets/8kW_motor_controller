#include "ADC_Result.h"
#include "Torque_calculation.h"
#include "macrodriver.h"
#include "speed.h"

int16_t input_Power = 0;
int16_t output_Power = 0;
int16_t Power_input = 0;
float torque = 0;
int16_t input_Power1 = 0;
extern float corrected_theta;
extern float dcVolt_ACT;
extern float dc_I_RMS;
extern int16_t iq_feedback;
extern int16_t id_feedback;
float Ld_Lq = 0.00003693;
void Power_Torque_Calculation(uint16_t motor_speed)
{
	
	input_Power = (int16_t)(dcVolt_ACT * dc_I_RMS);
	if(input_Power < 0)
	{
		input_Power1 = (uint16_t)(input_Power * -1);
	}
	else
	{
		input_Power1 = input_Power;
	}
	torque = (uint8_t)(((float)9.554 * input_Power1)/(motor_speed));
	

}

void torque_cal(void)
{       
	torque = 6*((lambda_pm1*iq_feedback)+((Ld_Lq)*id_feedback*iq_feedback));
	Power_input = (int16_t)(dcVolt_ACT * dc_I_RMS); 
}