#ifndef	TORQUE_H
#define TORQUE_H

#include "macrodriver.h"

#define Ld         9.474e-5   	//3.177e-5    //94.74e-6     // d-axis inductance (H)
#define Lq         5.781e-5   	// 4.732e-5   //57.81e-6     // q-axis inductance (H)
#define lambda_pm1 2.02e-2//9.57e-3 

void Power_Torque_Calculation(void);

#endif