#include"macrodriver.h"
#include"InverseClarke.h"

void InverseClarke(int16_t vAlpha,int16_t vBeta, int16_t *vA,int16_t *vB,int16_t *vC)
{
        *vA =  (vAlpha); //va = Valpha
    	*vB =  (((1732 * vBeta) / 2000) - (vAlpha / 2)); //vb = (-Valpha + 1.732 * Vbeta) / 2
   	*vC =  ((-(1732 * vBeta) / 2000) - (vAlpha / 2)); //vc = (-Valpha - 1.732 * Vbeta) / 2

        
}