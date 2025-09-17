
#ifndef REGISTER_INTERFACE_H
#define REGISTER_INTERFACE_H

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"
#include "iodefine.h"


/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define SET	1
#define CLEAR	0

/* Digital Input Signal */
#define PGOOG_15V			PPR0.BIT_4
#define HALL_A				PPR0.BIT_9
#define HALL_B				PPR0.BIT_10
#define HALL_C				PPR0.BIT_11
#define OCP_FAULT			PPR9.BIT_1
#define SHOOT_THROUGH_FAULT		PPR9.BIT_2
#define REAR_BREAK_SW			PPR9.BIT_3
#define PARK_SW				PPR9.BIT_4
#define MODE_SW			 	PPR9.BIT_5
#define	CRUISE_CONT_SW			PPR10.BIT_9
#define SIDE_STAND_SW			PPR10.BIT_10
#define FORWARD_REVERSE_SW		PPR10.BIT_11
#define FRONT_BREAK_SW			PPR10.BIT_12
#define KILL_SW				PPR10.BIT_13
#define ANTI_THEFT_LOCK_CONT_SW		PPR10.BIT_14

/* Digital Output Signal */
#define CAN_STB_CONDITION		P0.BIT_5
#define GD_CONDITION			&PORT.P9

/* Analog Input Signal */
#define MOTOR_TEMP_CNT			ADCA0.DR00.UINT16[L]
#define AC_R_PH_V_CNT			ADCA0.DR00.UINT16[H]
#define AC_Y_PH_V_CNT			ADCA0.DR02.UINT16[L]
#define AC_B_PH_V_CNT			ADCA0.DR02.UINT16[H]
#define AC_R_PH_I_CNT			ADCA0.DR04.UINT16[L]
#define AC_Y_PH_I_CNT			ADCA0.DR04.UINT16[H]
#define AC_B_PH_I_CNT			ADCA0.DR06.UINT16[L]
#define DC_BUS_I_CNT			ADCA0.DR06.UINT16[H]
#define DC_BUS_V_CNT			ADCA0.DR08.UINT16[L]
#define INV_R_PH_TEMP_CNT		ADCA0.DR08.UINT16[H]
#define INV_Y_PH_TEMP_CNT		ADCA0.DR10.UINT16[L]
#define INV_B_PH_TEMP_CNT		ADCA0.DR10.UINT16[H]
#define TPS1_CNT			ADCA0.DR12.UINT16[L]
#define TPS2_OR_15V_PGOOD		ADCA0.DR12.UINT16[H]
#define RESOLVER_SINE		        ADCA0.DR14.UINT16[L]
#define RESOLVER_COS			ADCA0.DR14.UINT16[H]


/* PWM Signal */
#define U_PHASE_COMPARE			TAUD0.CDR4
#define V_PHASE_COMPARE			TAUD0.CDR6
#define W_PHASE_COMPARE			TAUD0.CDR8


int Pin_State(uint8_t pin);

void Get_ResolverOutput(uint16_t *U_sineCount,uint16_t *U_cosCount );
void Current_Feedback(uint16_t *I_a,uint16_t *I_b,uint16_t *I_c );
void Get_DC_quantities(uint16_t *dc_V,uint16_t *dc_I );
#endif /* REGISTER_INTERFACE_H */