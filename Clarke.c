#include"macrodriver.h"
#include"Clarke.h"
#include"Config_PWM.h"
#include"clarke.h" 

uint16_t cnt1 = 0;
extern uint16_t flag1;
int16_t I_Alpha_array[2000];
int16_t I_Beta_array[2000];
int16_t I_a_array[2000];
int16_t I_b_array[2000];

void clarke_transform(int16_t iA, int16_t iB, int16_t *I_Alpha, int16_t *I_Beta)
{
    // Q15 input: iA and iB should already be in the range [-32768, +32767], i.e., -1.0 to +1.0
    // Clarke transformation coefficients:
    // I_Alpha = iA
    // I_Beta = (iA + 2 * iB) / v3 ˜ (iA + 2 * iB) * 0.57735
    int32_t temp = 0;
    const int16_t INV_SQRT3_Q15 = 18919; // 0.57735 in Q15 (0.57735 * 32768)
 
    *I_Alpha = iA;
 
    temp = ((int32_t)iA + 2 * (int32_t)iB) * INV_SQRT3_Q15;
    *I_Beta = (int16_t)(temp >> 15);  // Back to Q15
    
    	  if((cnt1<=2000)&&(flag1==1))
	   {
		I_a_array[cnt1] = iA;
		I_b_array[cnt1] = iB;
		I_Alpha_array[cnt1] = *I_Alpha;
		I_Beta_array[cnt1] = *I_Beta;
		cnt1++;
	   }
	   else
	   {
	        cnt1 = 0;
		flag1 = 0;
	   }
}