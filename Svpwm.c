#include"macrodriver.h"
#include"Svpwm.h"
#include"Config_PWM.h"
//uint16_t pwmsin_u[2000];
//uint16_t pwmsin_v[2000];
//uint16_t pwmsin_w[2000];

//int16_t va_array[2000];
//int16_t vb_array[2000];
//int16_t vc_array[2000];

uint16_t cnt = 0;
uint8_t flag1 =0;
void Svpwm_Duty(int16_t vA,int16_t vB,int16_t vC)
{
	int16_t max_Volt;
        int16_t min_Volt;
	int16_t comon_Mode_V;
	int16_t vA_SVPWM;
	int16_t vB_SVPWM;
	int16_t vC_SVPWM;
	uint16_t sin_Duty_U;
	uint16_t sin_Duty_V;
	uint16_t sin_Duty_W; 
	
	if(vA >= vB)
	{
		if(vA >= vC)
		{
			max_Volt = vA;
		}
		else
		{
			max_Volt = vC;
		}
	}
	else if(vB >= vC)
	{
		max_Volt = vB;
	}
	else
	{
		max_Volt = vC;
	}
	/* Find Miniumum Volt*/
	if(vA <= vB)
	{
		if(vA <= vC)
		{
			min_Volt = vA;
		}
		else
		{
			min_Volt = vC;
		}
	}
	else if(vB <= vC)
	{
		min_Volt = vB;
	}
	else
	{
		min_Volt = vC;
	}
	comon_Mode_V = -((max_Volt + min_Volt)/2);
	
	vA_SVPWM = (vA+comon_Mode_V);
	vB_SVPWM = (vB+comon_Mode_V);
	vC_SVPWM = (vC+comon_Mode_V);
	
	
	sin_Duty_U = vA_SVPWM + DUTY_U_PHASE;
	sin_Duty_V = vB_SVPWM + DUTY_V_PHASE;
	sin_Duty_W = vC_SVPWM + DUTY_W_PHASE;
	/*if((cnt<=2000)&&(flag1==1))
	{
		//va_array[cnt] = vA;
		//vb_array[cnt] = vB;
		//vc_array[cnt] = vC;
		//pwmsin_u[cnt]=sin_Duty_U;
		//pwmsin_v[cnt]=sin_Duty_V;
		//pwmsin_w[cnt]=sin_Duty_W;
		//cnt++;
	}
	else
	{
	        cnt = 0;
		flag1 = 0;
	}*/
	
	Update_PWM_Duty(sin_Duty_U,sin_Duty_V,sin_Duty_W);
}