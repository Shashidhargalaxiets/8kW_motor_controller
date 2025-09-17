#include "macrodriver.h"
#include "AngleConversion.h"

int16_t SinCos_AngleConversion_AngleConversion(uint8_t electrical_theta,uint8_t sincos,uint16_t offset)
{
	uint16_t sin_theta_Count;
        uint16_t cos_theta_Count;
        int16_t retval;
        
	sin_theta_Count = Theta_RotarConversion(electrical_theta,offset);
        	//Conversion of Sin count to cos count
	
        if (sin_theta_Count < 49151) /* cos theta is 90 degree phase shift os sine theta */ 
	{
        	cos_theta_Count = sin_theta_Count + 16383; /* rotor_Theta1 is cos theta */
	}
        else
        {
        	cos_theta_Count = (sin_theta_Count - 49151);
	}
	if(sincos ==0)
	{
		retval = Table[sin_theta_Count >> 8];
	}
	else
	{
		retval = Table[cos_theta_Count >> 8];/* 65535 to 256 conversion */
	}
   return retval;
}

uint16_t Theta_RotarConversion(uint8_t electrical_theta,uint8_t offset)
{
   	uint16_t electrical_theta_count;
	uint16_t electrical_rotartheta_sincount;

	/* convert 360 degree  to 65535 count because of precise resolution*/
	electrical_theta_count = electrical_theta *(float)(182.041);
   	if(electrical_theta_count >= 65535){
	   electrical_theta_count = electrical_theta_count % 65535;   
   	}
	
	/* Offset theta Base sin and cos find out */
	if(electrical_theta_count > (offset*182)) /* 1 degree is equal to 182*/  
	{
		electrical_rotartheta_sincount = electrical_theta_count - (offset*182); /* rotor_Theta is Sine theta */
	}
	else
	{
		electrical_rotartheta_sincount = electrical_theta_count + ((360-offset)*182); 
	}
    	if (electrical_rotartheta_sincount > 0xFFFF)
   	{
    	    electrical_rotartheta_sincount = 0;
	}
        
	
	return electrical_rotartheta_sincount;
}

int16_t Adv_SinCos_AngleConversion_AngleConversion(uint8_t electrical_theta,uint8_t sincos,uint16_t offset,int16_t advance_theta)
{
	uint16_t sin_theta_Count;
        uint16_t cos_theta_Count;
        int16_t retval;
        
	sin_theta_Count = Adv_Theta_RotarConversion(electrical_theta,offset,advance_theta);
        	//Conversion of Sin count to cos count
	
        if (sin_theta_Count < 49151) /* cos theta is 90 degree phase shift os sine theta */ 
	{
        	cos_theta_Count = sin_theta_Count + 16383; /* rotor_Theta1 is cos theta */
	}
        else
        {
        	cos_theta_Count = (sin_theta_Count - 49151);
	}
	if(sincos ==0)
	{
		retval = Table[sin_theta_Count >> 8];
	}
	else
	{
		retval = Table[cos_theta_Count >> 8];/* 65535 to 256 conversion */
	}
   return retval;
}

uint16_t Adv_Theta_RotarConversion(uint8_t electrical_theta,uint8_t offset,int8_t advance_theta)
{
   	uint16_t electrical_theta_count;
	uint16_t electrical_rotartheta_sincount;

	/* convert 360 degree  to 65535 count because of precise resolution*/
	electrical_theta_count = electrical_theta *(float)(182.041);
   	if(electrical_theta_count >= 65535){
	   electrical_theta_count = electrical_theta_count % 65535;   
   	}
	
	/* Offset theta Base sin and cos find out */
	if(electrical_theta_count > ((offset + advance_theta)*182)) /* 1 degree is equal to 182*/  
	{
		electrical_rotartheta_sincount = electrical_theta_count - ((offset + advance_theta)*182); /* rotor_Theta is Sine theta */
	}
	else
	{
		electrical_rotartheta_sincount = electrical_theta_count + ((360-(offset + advance_theta)*182)); 
	}
    	if (electrical_rotartheta_sincount > 0xFFFF)
   	{
    	    electrical_rotartheta_sincount = 0;
	}
        
	
	return electrical_rotartheta_sincount;
}
