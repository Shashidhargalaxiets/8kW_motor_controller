#include "iodefine.h"
#include "FaultCheck_Functions.h"

uint8_t Fault_Check(int16_t compare_value, int16_t min_limit, int16_t max_limit)
{
	uint8_t parameter_fault_state ;
	if((compare_value < min_limit)||(compare_value > max_limit))
	{
		parameter_fault_state = FAULT;
	}
	else
	{
		parameter_fault_state = NO_FAULT;
	}

	return parameter_fault_state;
}

void FaultCheck_Debounced(uint8_t *parameter_fault_state, int16_t compare_value, int16_t min_limit, int16_t max_limit, uint8_t debounce_time, uint8_t *debounce_time_cnt)
{
	
    if((compare_value < min_limit)||(compare_value > max_limit))
    {
        (*debounce_time_cnt)++;
        if(*debounce_time_cnt>debounce_time)
        {
             *parameter_fault_state = FAULT;
        }
    }
    else
    {
        *debounce_time_cnt = 0;
        //parameter_fault_state = NO_FAULT;
    }
 
}

void FaultCheck_DebouncedGreaterThan(uint8_t *parameter_fault_state, int16_t compare_value, int16_t max_limit, uint8_t debounce_time, uint16_t *debounce_time_cnt)
{
	
    if(compare_value >= max_limit)
    {
        (*debounce_time_cnt)++;
        if(*debounce_time_cnt>debounce_time)
        {
            *parameter_fault_state = FAULT;
        }
    }
    else
    {
        //*debounce_time_cnt = 0;
        //parameter_fault_state = NO_FAULT;
    }
}

void FaultCheck_DebouncedLessThan(uint8_t *parameter_fault_state, int16_t compare_value, int16_t min_limit, uint8_t debounce_time, uint16_t *debounce_time_cnt)
{
	
    if(compare_value <= min_limit)
    {
        (*debounce_time_cnt)++;
        if(*debounce_time_cnt>debounce_time)
        {
             *parameter_fault_state = FAULT;
        }
    }
    else
    {
        //*debounce_time_cnt = 0;
        //parameter_fault_state = NO_FAULT;
    }
}