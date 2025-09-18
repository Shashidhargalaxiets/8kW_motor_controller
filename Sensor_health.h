
#ifndef SENSOR_HEALTH_H
#define SENSOR_HEALTH_H

#include "macrodriver.h"

#define NO_FAULT		0
#define FAULT			1

#define ENABLE			1
#define DISABLE			0

/* Sensor_Health_Check */
#define MAX_I_SENS_HLTH_LIMI            82			/* 20 A */
#define MIN_I_SENS_HLTH_LIMI            -82			/* -20 A */

#define MAX_DCV_SENS_HLTH_LIMI            3279			/* 81 V */
#define MIN_DCV_SENS_HLTH_LIMI            41			/* 1 V */

#define MAX_PHV_SENS_HLTH_LIMI            32			/* 1 V */
#define MIN_PHV_SENS_HLTH_LIMI            -32			/* -1 V */

#define MAX_TPS_SENS_HLTH_LIMI          4050			/* 4.94 V */
#define MIN_TPS_SENS_HLTH_LIMI          350//164//300		/* if remove throttle it comming 0.38V */ /* 0.2V=164Cnt for LTVS throttle*/	/* 0.36V=300Cnt for GETS throttle */	

#define MAX_MOT_NTC_SENS_HLTH_LIMI      1603			/* 10Deg*/
#define MIN_MOT_NTC_SENS_HLTH_LIMI      11			/* 300 Deg */

#define MAX_INV_TEMP_SENS_HLTH_LIMI     622			/* 138 Deg */
#define MIN_INV_TEMP_SENS_HLTH_LIMI     3669			/* 10 Deg */

#define MIN_SIN_SENS_HLTH_LIMI          700
#define MAX_SIN_SENS_HLTH_LIMI         3500

#define MIN_COS_SENS_HLTH_LIMI          700
#define MAX_COS_SENS_HLTH_LIMI          3500

#define ACTIVATE	1
#define DEACTIVATE	0

#endif