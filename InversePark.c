#include"macrodriver.h"
#include"InversePark.h"

void InversePark(int16_t sin_theta,int16_t cos_theta,int16_t vQ, int16_t vD,int16_t *vAlpha,int16_t *vBeta)
{
	*vAlpha = ((vD * cos_theta) - (vQ * sin_theta)) >> 15;//divide by 2^15
    	*vBeta = ((vQ * cos_theta) + (vD * sin_theta)) >> 15;//divide by 2^15

}
