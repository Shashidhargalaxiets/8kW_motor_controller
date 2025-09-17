#ifndef	RAMP_H
#define RAMP_H 
#include "macrodriver.h"

//int16_t CalculateRampStep(int16_t initial_TorqueSetPoint, int16_t target_TorqueSetPoint);
//int16_t RampToTarget(int16_t initial_TorqueSetPoint, int16_t target_TorqueSetPoint);
int16_t Ramp_function(float initial_SetPoint,float target_SetPoint);
#endif