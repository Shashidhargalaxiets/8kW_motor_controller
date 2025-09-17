#include"Clarke.h"
#include"Config_PWM.h"
#include"Park.h" 

uint16_t cnt2 = 0;
extern uint16_t flag1;
//int16_t I_q_array[2000];
//int16_t I_d_array[2000];
int16_t iq_feedback = 0;
int16_t id_feedback = 0;
void park_transform(int16_t i_alpha, int16_t i_beta, int16_t sintheta, int16_t costheta, int16_t *iQ, int16_t *iD)
{
    // Intermediate 32-bit results to avoid overflow during multiplication
    int32_t temp_d= (int32_t)i_alpha * costheta + (int32_t)i_beta * sintheta;
    int32_t temp_q = (int32_t)i_beta * costheta - (int32_t)i_alpha * sintheta;
 
    // Right shift to bring back to Q15 format (with rounding)
    //*iQ = (int16_t)((temp_q + (1 << 14)) >> 15);
    //*iD = (int16_t)((temp_d + (1 << 14)) >> 15);
    
    *iQ = (int16_t)(temp_q >> 15);
    *iD = (int16_t)(temp_d >> 15);
    
   	/*  if((cnt2<=2000)&&(flag1==1))
	   {
		I_q_array[cnt2] = *iQ;
	        I_d_array[cnt2] = *iD;
		cnt2++;
	   }
	   else
	   {
	        cnt2 = 0;
		flag1 = 0;
	   }
	*/
	iq_feedback = (*iQ/4.1);
	id_feedback = (*iD/4.1);
	
}
