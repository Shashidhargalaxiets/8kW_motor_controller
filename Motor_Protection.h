#ifndef MOTOR_PROTECTION_H
#define MOTOR_PROTECTION_H

#include"macrodriver.h"
#include "Sensor_health.h"
#include "Task_100us.h"

/* Protection Variable */
#define DC_V_MAX_LIMIT 			 60
#define DC_V_MIN_LIMIT 			 38
#define DC_I_MAX_LIMIT 			 140
#define SPEED_MAX_LIMIT 		 600//1200
#define PHASE_I_MAX_LIMIT 		 580 //250
#define MOT_TEMP_MAX_LIMIT		 381			/* 90 Deg */				/* if change count to SI Value change Logi also(Opposite condition need to add) */
#define INV_TEMP_MAX_LIMIT 		 1252//1493//1765	/* 100 Deg *//* 90 Deg *//* 80 Deg */	/* if change count to SI Value change Logi also(Opposite condition need to add) */

#define DC_V_DEBOUNCE			500
#define DC_I_RMS_DEBOUNCE		20
#define PH_I_RMS_DEBOUNCE		20
#define SPEED_DEBOUNCE			500
#define INV_TEMP_DEBOUNCE		500
#define PH_OPN_DEBOUNCE			1000

#endif