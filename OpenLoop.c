#include"OpenLoop.h"
#include"macrodriver.h"

uint16_t count1 = 0;
extern uint8_t flag;
//uint16_t elec_theta[2000];

uint16_t Emulated_RotarThetaGeneration(uint8_t time_adj)
{
	static uint16_t man_Theta_Inc_delay = 0;
	static uint16_t emulated_rotartheta=0;
	uint16_t electrical_theta = 0;
	
        man_Theta_Inc_delay++;
	if(man_Theta_Inc_delay >= time_adj)
         {
	      if(emulated_rotartheta <= 359)
	      {
	          emulated_rotartheta++;
	      }
	      else
	      {
	           emulated_rotartheta = 0;
	      }
	            man_Theta_Inc_delay = 0;
	  }
	 electrical_theta = emulated_rotartheta;
	 /*if(count1 < 2000 && flag == 1)
	{
	   	elec_theta[count1] = electrical_theta;
		count1++;
	}
	else
	{
		count1 = 0;
		flag = 0;
	}*/
	 return electrical_theta;
}