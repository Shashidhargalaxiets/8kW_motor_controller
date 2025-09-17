
/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "iodefine.h"
#include "Trapezoidal_Mode.h"
#include "Digital_Input_Read.h"
#include "Motor_Control.h"

/**
****************************************************************************************************************************
*	Extern variables and functions
****************************************************************************************************************************
**/

/* Hall signal */
extern uint8_t hall_A;
extern uint8_t hall_B;
extern uint8_t hall_C;

extern int16_t	v_q;

/* Vehical Function I/O Data */
extern uint8_t forward_Mode;
/**
****************************************************************************************************************************
*	Global variables and functions
****************************************************************************************************************************
**/
/* Sector Estmation Variable */
uint8_t sector = 0;

/* Sector Degree Estimation */
uint16_t sect_Deg = 0;

/* Speed Estimation Variable */
float freq_Adj = 1;
uint16_t speed_Counter = 0;
uint16_t speed_Esti_Counter = 0;
uint8_t prev_sect = 0;
uint16_t freq = 0;
uint16_t freq_Add = 0;
uint32_t freq_Sum = 0;
uint8_t freq_Sum_Cnt = 0;
uint16_t speed_RPM = 0;
float delta_Theta = 0;
float delta_Theta_cnt = 0;
int16_t ele_Theta = 0;
uint8_t no_of_Pole_pair = 30;

/* Electrical Degree Estimation */
uint8_t reset_Speed = 0;

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Sector_Estimation(void)
{
	if( ( (hall_A == 1) && (hall_B == 0)) && (hall_C == 1) ){
	    sector = 1;
	}else if( ( (hall_A == 1) && (hall_B == 0)) && (hall_C == 0) ){
	    sector = 2;
	}else if( ( (hall_A == 1) && (hall_B == 1)) && (hall_C == 0) ){
	    sector = 3;
	}else if( ( (hall_A == 0) && (hall_B == 1)) && (hall_C == 0) ){
	    sector = 4;
	}else if( ( (hall_A == 0) && (hall_B == 1)) && (hall_C == 1) ){
	    sector = 5;
	}else if( ( (hall_A == 0) && (hall_B == 0)) && (hall_C == 1) ){
	    sector = 6;
	}
	else
	{
		
	}
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Deg_Estimation(void)
{
	if(forward_Mode == DEACTIVATE)
	{
		if (sector == 1) {
		    sect_Deg = 0;
		} else if (sector == 2) {
		    sect_Deg = 60;
		} else if (sector == 3) {
		    sect_Deg = 120;
		} else if (sector == 4) {
		    sect_Deg = 180;
		} else if (sector == 5) {
		    sect_Deg = 240;
		} else if (sector == 6) {
		    sect_Deg = 300;
		}
	}
	else if(forward_Mode == ACTIVATE)
	{
		if (sector == 1) {
		    sect_Deg = 180;
		}else if (sector == 2) {
		    sect_Deg = 240;
		}else if (sector == 3) {
		    sect_Deg = 300;
		}else if (sector == 4) {
		    sect_Deg = 0;
		}else if (sector == 5) {
		    sect_Deg = 60;
		}else if (sector == 6) {
		    sect_Deg = 120;
		}
	}
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Speed_Estimation(void)
{
	speed_Counter++;
	if( ( (prev_sect == 6) && (sector == 1)) || ( (prev_sect == 1) && (sector == 6) ) ) 
	{
		reset_Speed = 0;
		speed_Esti_Counter = speed_Counter;
		speed_Counter = 0;
		freq_Add = ( (10000/speed_Esti_Counter) * (float)freq_Adj);
		freq_Sum_Cnt++;
		freq_Sum +=freq_Add;
		if(freq_Sum_Cnt >=2)
		{
			freq = (freq_Sum / freq_Sum_Cnt);
			freq_Sum = 0;
			freq_Sum_Cnt = 0;
		}
		speed_RPM = ( ((120 * freq) / (no_of_Pole_pair * 2)));
		
		delta_Theta = ( (6.283 * freq)/10000);
	}
	if(prev_sect != sector)
	{
		delta_Theta_cnt = 0;
		prev_sect = sector;
	}
	if (speed_Counter >= 65535) 
	{
		speed_Counter = 0;
	}
	if(speed_Counter >= 10000)
	{
		speed_RPM = 0;
		ele_Theta = 0;
		freq_Add = 0;
	}
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Ele_Deg_Estimation(void)
{
	if(forward_Mode == DEACTIVATE)
	{
		delta_Theta_cnt = (delta_Theta_cnt + delta_Theta);
		ele_Theta = (signed int)(sect_Deg + 60 -(float)( delta_Theta_cnt * (float)57.32));
		if(ele_Theta < 0)
		{
			ele_Theta = 360+ele_Theta;
		}
	}
	else if(forward_Mode == ACTIVATE)
	{
		delta_Theta_cnt = (delta_Theta_cnt + delta_Theta);
		ele_Theta = (sect_Deg +( delta_Theta_cnt * (float)57.32));
	}
}
/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Trapezoidal_Patern(void)
{
	if(forward_Mode == DEACTIVATE)
	{
		if (sector == 1) {
		     TAUD0.TO = 0x8200;//U0,W-
		     TAUD0.TOE = 0x0040;//V_OP
		}else if (sector == 2) {
		     TAUD0.TO = 0x0820;//U-,W0
		     TAUD0.TOE = 0x0040;//V_OP
		}else if (sector == 3) {
		     TAUD0.TO = 0x0820;//U-,V0
		     TAUD0.TOE = 0x0100;//W_OP
		}else if (sector == 4) {
		     TAUD0.TO = 0x2080;//U0,V-
		     TAUD0.TOE = 0x0100;//W_OP
		}else if (sector == 5) {
		     TAUD0.TO = 0x2080;//V-,W0
		     TAUD0.TOE = 0x0010;//U_OP
		}else if (sector == 6) {
		     TAUD0.TO = 0x8200;//V0,W-
		     TAUD0.TOE = 0x0010;//U_OP
		}
	}
	else if(forward_Mode == ACTIVATE)
	{
		if (sector == 6) {
		     TAUD0.TO = 0x0820;//U-,V0
		     TAUD0.TOE = 0x0100;//W_OP
		}else if (sector == 5) {
		     TAUD0.TO = 0x0820;//U-,W0
		     TAUD0.TOE = 0x0040;//V_OP
		}else if (sector == 4) {
		     TAUD0.TO = 0x8200;//U0,W-
		     TAUD0.TOE = 0x0040;//V_OP
		}else if (sector == 3) {
		     TAUD0.TO = 0x8200;//V0,W-
		     TAUD0.TOE = 0x0010;//U_OP
		}else if (sector == 2) {
		     TAUD0.TO = 0x2080;//V-,W0
		     TAUD0.TOE = 0x0010;//U_OP
		}else if (sector == 1) {
		     TAUD0.TO = 0x2080;//U0,V-
		     TAUD0.TOE = 0x0100;//W_OP
		}
	}
	
	
}

/**
****************************************************************************************************************************
*	See header file for function definition. 
****************************************************************************************************************************
**/
void Trapezoidal_MODE(void)
{
	Trapezoidal_Patern();
	
	Update_PWM_Duty(v_q,v_q,v_q);
}
  

