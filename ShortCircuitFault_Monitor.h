#ifndef SHORTCIRCUITFAULT_MONITOR_H
#define SHORTCIRCUITFAULT_MONITOR_H

#include "macrodriver.h"
#include "Sensor_health.h"

#define DC_I_SC_DEBOUNCE		5
#define PH_I_SC_DEBOUNCE		5

/* Software Fault Monitor */
#define MAX_DC_BUS_SC_LIMIT             738                    	/* 180 A  */
#define MIN_DC_BUS_SC_LIMIT             -410                   	/* -100 A */

#define MAX_PHASE_SC_LIMIT              1500                   	/* 366 A    */
#define MIN_PHASE_SC_LIMIT              -1500                  	/* -366 A   */        

void Software_Fault_Monitor(void);

#endif