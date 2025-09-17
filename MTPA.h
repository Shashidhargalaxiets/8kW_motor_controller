#ifndef	MTPA_H
#define MTPA_H

#include "macrodriver.h"
                   //old motor  //new motor   //old motor backup
#define Ld         9.474e-5   	//3.177e-5    //94.74e-6     // d-axis inductance (H)
#define Lq         5.781e-5   	// 4.732e-5   //57.81e-6     // q-axis inductance (H)
#define lambda_pm  1.196e-3   	//1.256e-3    //1.196e-3     // Permanent magnet flux linkage (Wb)
#define resistance 5.88e-3    	//5.71e-3
#define p          4                                     // Number of poles
#define I_rated    200
#define Torque     30
#define I_max_factor  (I_rated/Torque)*1.414//282.84//Peak           //230.0        // Max phase current (A)
//#define I_max      282.8
#define v_max      30.2                                  // Max voltage (V)
#define Vs_MAX_FLX_FEEDBACK 1400
#define term1     (lambda_pm/(4*(Lq - Ld)))
#define term2     (term1*term1)
#define Vs_REF_MAX 1250			/* Cnt */
void compute_field_weakening_given_torque();
void compute_field_weakening_max_torque();
void MTPA_OR_FW(float Tref, uint16_t speed, float *Id_ref, float *Iq_ref);
void MTPA();
void MTPA_cal(float torque_ref);
void MTPV_cal(void);
#endif