#include"iodefine.h"
#include"PWM.h"
#include"macrodriver.h"

void Update_PWM_Duty(uint16_t duty_Uph, uint16_t duty_Vph, uint16_t duty_Wph)
{
	
	TAUD0.CDR4 = (uint16_t)duty_Uph; 
	TAUD0.CDR6 = (uint16_t)duty_Vph; 
	TAUD0.CDR8 = (uint16_t)duty_Wph; 
	TAUD0.RDT = 0x0150;	
}