#ifndef	SPEED_H
#define SPEED_H

#include "macrodriver.h"

void calculate_speed_rpm(uint16_t rotor_theta_rad_new, uint16_t *speed_rpm);
void speed_PI_controller(float speed_setPoint, float speed_measured, float *Tref);

#endif