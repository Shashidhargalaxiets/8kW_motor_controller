#ifndef STALL_PROTECTION_H
#define STALL_PROTECTION_H

#include"macrodriver.h"
#include"Sensor_health.h"
#include "Task_100us.h"

/* Stal Protection Fault Monitor */
#define STAL_PROT_SPEED_LIMIT 		20			/* RPM */
#define STAL_PROT_DC_I_LIMIT		60			/* A */
#define STAL_Is_LIMIT			900			/* Cnt */

#define STALL_DEBOUNCE			1000

void Stall_Protection(void);

#endif