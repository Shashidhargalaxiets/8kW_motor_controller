#ifndef FAULTCHECK_FUNCTIONS_H
#define FAULTCHECK_FUNCTIONS_H

#include "macrodriver.h"
#include "Sensor_health.h"

uint8_t Fault_Check(int compare_value, int16_t min_limit, int16_t max_limit);

void FaultCheck_Debounced(uint8_t *parameter_fault_state, int16_t compare_value, int16_t min_limit, int16_t max_limit, uint8_t debounce_time, uint8_t *debounce_time_cnt);

void FaultCheck_DebouncedGreaterThan(uint8_t *parameter_fault_state, int16_t compare_value, int16_t max_limit, uint8_t debounce_time, uint16_t *debounce_time_cnt);

void FaultCheck_DebouncedLessThan(uint8_t *parameter_fault_state, int16_t compare_value, int16_t min_limit, uint8_t debounce_time, uint16_t *debounce_time_cnt);

#endif