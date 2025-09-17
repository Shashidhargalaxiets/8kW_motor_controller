#include "Resolver.h"
#include "macrodriver.h"

uint16_t count2 = 0;
extern uint8_t flag ;
float tan_inverse[2000];
uint16_t tan_inverse_degree[2000];

float Signed_ResolverCount(uint16_t resolver_count, uint16_t resolver_offset,float factor)
{
    return ((float)(resolver_count - resolver_offset));
}

float Resolver_Theta(float sine_offseted_count,float cos_offseted_count)
{
        float theta_in_radians; 
        theta_in_radians = (float)(atan2f(sine_offseted_count, cos_offseted_count));
	return theta_in_radians;
}

uint16_t RadianToDegreeConversion(float theta_radian)
{
	float theta_degree;
	uint16_t retval;
	theta_degree = theta_radian * 57.32f;
	theta_degree = theta_radian * 57.32f;
	if (theta_degree < 0.0f)
        {
           theta_degree += 360.0f;
        }
        else if (theta_degree >= 360.0f)
        {
           theta_degree -= 360.0f;
        }
	else
	{
	  /*Do nothing*/	
	}
	retval = (uint16_t)(theta_degree + 0.5f);
	return retval;
}