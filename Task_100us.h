#ifndef	TASK_100US_H
#define TASK_100US_H

//MTPA
#define Ld        3.177e-5 //94.74e-6     // d-axis inductance (H)
#define Lq        4.732e-5 //57.81e-6     // q-axis inductance (H)
#define lambda_pm 1.256e-3 //1.196e-3     // Permanent magnet flux linkage (Wb)
#define resistance6.71e-3
#define p         4            // Number of poles
#define I_max     230.0        // Max phase current (A)
#define v_max     30.2        // Max voltage (V)
//
#define MINIMUM_THROT			730//512//730//512//730//725//720//770//512//770//512		/* 0.625V=512Cnt for LTVS Throttle*//* 0.9=730Cnt for GETS Throttle */	
#define RAMP_UP_DELAY			10
#define RAMP_DOWN_DELAY			10
typedef struct
{
	    uint8_t time_adj;
	    uint16_t electrical_theta;
	    uint8_t sincos;
	    uint16_t offset;
	    int16_t adv_theta;
	    int16_t sin_adv_theta;
	    int16_t cos_adv_theta;
	    int16_t sin_theta;
	    int16_t cos_theta;
	    int16_t vQ;
	    int16_t vD;
	    int16_t vS;
	    int16_t vAlpha;
	    int16_t vBeta;
	    int16_t vA;
	    int16_t vB;
	    int16_t vC;	
}OpenLoopParameters;

typedef struct
{
	uint16_t Ia;
	uint16_t Ib;
}Current_Params;

typedef struct
{
	int16_t Ialpha;
	int16_t Ibeta;
}Clarke_Params;

typedef struct
{
	int16_t iQ ;
	int16_t iD;
	float torque_PI_SetPoint;
	float flux_setPoint;
}CurrentControl_Params;


typedef struct
{
	    float speed_setPoint;
	    float speed_measured_rpm;
	    float Tref;
	    int16_t Id_ref;
	    int16_t Iq_ref;
}SpeedParameters;

void Task_100micro(void);
#endif