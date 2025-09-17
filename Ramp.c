#include "macrodriver.h"

//float step_up = 0.0005;
//float step_down = 0.001; 

/*#define LOOP_FREQ_HZ    10000         // 100 µs loop -> 10,000 Hz
#define RAMP_TIME_SEC   0.002f        // Ramp duration = 2 ms

int16_t CalculateRampStep(int16_t initial_TorqueSetPoint, int16_t target_TorqueSetPoint)
{
    float step = abs(initial_TorqueSetPoint - target_TorqueSetPoint) /20;//(RAMP_TIME_SEC * LOOP_FREQ_HZ)
    return (int16_t)(step + 0.5f);  // Round to nearest int
}

int16_t RampToTarget(int16_t initial_TorqueSetPoint, int16_t target_TorqueSetPoint)
{
    int16_t step = CalculateRampStep(initial_TorqueSetPoint, target_TorqueSetPoint);

    if (initial_TorqueSetPoint < target_TorqueSetPoint - step)
        return initial_TorqueSetPoint + step;
    else if (initial_TorqueSetPoint > target_TorqueSetPoint + step)
        return initial_TorqueSetPoint - step;
    else
        return target_TorqueSetPoint;
}*/


/* int16_t Ramp_function(float initial_SetPoint,float target_SetPoint)
{
            if(initial_SetPoint >  target_SetPoint ) 
	    {
               initial_SetPoint = initial_SetPoint - step_up;//0.0005;
	    }
            else if(initial_SetPoint < target_SetPoint ) 
	    {
	    initial_SetPoint = initial_SetPoint + step_down;//0.001;
	    }
            //else initial_SetPoint = target_SetPoint;
	    
    return initial_SetPoint;
}*/