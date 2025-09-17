#ifndef	RESOLVER_H
#define RESOLVER_H

#include "macrodriver.h"

float Signed_ResolverCount(uint16_t resolver_count,uint16_t resolver_offset,float factor);
float Resolver_Theta(float sine_offseted_count,float cos_offseted_count);
uint16_t RadianToDegreeConversion(float theta_radian);
#endif