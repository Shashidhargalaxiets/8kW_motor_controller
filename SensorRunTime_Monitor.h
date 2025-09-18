 
#ifndef SENSORRUNTIME_MONITOR_H
#define SENSORRUNTIME_MONITOR_H

#include "macrodriver.h"
#include "Sensor_health.h"
#include "Task_100us.h"

#define TPS_DEBOUNCE			    50
#define INV_TEMP_HLT_DEBOUNCE		50

void Sensor_Run_Time_Moni(void);

#endif