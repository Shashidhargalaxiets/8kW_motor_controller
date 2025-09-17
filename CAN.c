/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_rscanfd.c                                                     */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2016 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG Software Tool Support                                          */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: software_support-eu@lm.renesas.com                         */
/*        FAX:   +49 - (0)211 / 65 03 - 11 31                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Source code for RSCAN-FD functions.                                       */
/*                                                                           */
/*===========================================================================*/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "CAN.h"
#include "iodefine.h"
#include "CAN_TX.h"
#include "Digital_Input_Read.h"


/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/
#define TRUE 		1
#define FALSE 		0


/**
****************************************************************************************************************************
*	Extern variables
****************************************************************************************************************************
**/
extern uint8_t rx_ID506_CAN_Time_OUT_Err;
extern uint8_t rx_ID501_CAN_Time_OUT_Err;
extern uint8_t rx_IDA1_CAN_Time_OUT_Err;
extern uint8_t rx_IDA2_CAN_Time_OUT_Err;
/**
****************************************************************************************************************************
*	Global variables
****************************************************************************************************************************
**/
unsigned char rx_flag = 0;
unsigned char error_flag = 0;
unsigned char RX_Fifo_empty = 0;
unsigned int RX_fifo_full = 0;
unsigned int RX_Fifo_msg_lost = 0;
unsigned char rx_cnt = 0;

/* Recerive Variable Declaration */
unsigned char rx_msg_DLC;
unsigned int rx_msg_ID;
unsigned int rx_msg_ID_Test = 0;
unsigned long rx_msg_data0, rx_msg_data1,rx_msg_data2;


/* Rx ID_506 Variable */
uint32_t m506_ID = 0;
uint32_t m506_Data0 = 0;
uint32_t m506_Data1 = 0;
uint32_t m506_Data2 = 0;

uint8_t sleep_REQ = 0;

/* Rx ID_501 Variable */
uint32_t m501_ID = 0;
uint32_t m501_Data0 = 0;
uint32_t m501_Data1 = 0;
uint32_t m501_Data2 = 0;

uint8_t hand_Shak_REQ = 0;

/* Rx ID_A1 Variable */
uint32_t mA1_ID = 0;
uint32_t mA1_Data0 = 0;
uint32_t mA1_Data1 = 0;
uint32_t mA1_Data2 = 0;

/* Rx ID_506 Variable */
uint32_t mA2_ID = 0;
uint32_t mA2_Data0 = 0;
uint32_t mA2_Data1 = 0;
uint32_t mA2_Data2 = 0;

uint8_t charger_Status = 0;
uint8_t side_Stand_CAN = 0;
uint8_t pre_Char_Status = 0;
uint8_t vehicle_Not_Drivable = 0;

/* Rx ID_506 Variable */
uint32_t m700_ID = 0;
uint32_t m700_Data0 = 0;
uint32_t m700_Data1 = 0;
uint32_t m700_Data2 = 0;
uint16_t m700_RX_Time_Cnt = 0;

uint8_t rst_CAN_Flg = 0;

/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void can0_tx(uint32_t can_id, uint8_t data_length, uint8_t * data_ptr, uint8_t isExtended)
{  
	int i = 0;
   	if(!(RCFDC0.CFDTMSTS0 & 0x01))	
   	{       
		RCFDC0.CFDTMSTS0 = 0x00;
	
		RCFDC0.CFDTMIEC0.UINT16[L] = 0x0001;
	
		if (isExtended == TRUE)
		{
			//Extended ID
      			RCFDC0.CFDTMID0.UINT32 = can_id + 0x80000000;	
		}
		else if(isExtended == FALSE)
		{
			//Standard ID
  			RCFDC0.CFDTMID0.UINT32 = can_id;   		
		}
		
		//Transmit buffer pointer register
      		RCFDC0.CFDTMPTR0.UINT8[HH] = data_length<<4;   	
      	
      		RCFDC0.CFDTMFDCTR0.UINT32 = 0x00;

		RCFDC0.CFDTMDF0_0.UINT8[LL] = (*data_ptr++);		// Data bytes 0 to 3
		RCFDC0.CFDTMDF0_0.UINT8[LH] = (*data_ptr++);
		RCFDC0.CFDTMDF0_0.UINT8[HL] = (*data_ptr++);
		RCFDC0.CFDTMDF0_0.UINT8[HH] = (*data_ptr++); 

		RCFDC0.CFDTMDF1_0.UINT8[LL] = (*data_ptr++);		// Data bytes 4 to 7
		RCFDC0.CFDTMDF1_0.UINT8[LH] = (*data_ptr++);
		RCFDC0.CFDTMDF1_0.UINT8[HL] = (*data_ptr++);
		RCFDC0.CFDTMDF1_0.UINT8[HH] = (*data_ptr++);
		
		//Transmit buffer status register
      		RCFDC0.CFDTMC0 = 0x01;
		for(i=0;i<90;i++);
   	}
}

/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void can0_rx(void)
{
   RCFDC0.CFDRFSTS0.UINT8[0] &= 0xF7;   				
   if((RCFDC0.CFDRFSTS0.UINT8[0] & 0x01) != 0x01)
   {
      do
      {
         rx_msg_ID = RCFDC0.CFDRFID0.UINT16[0];
         rx_msg_DLC = (RCFDC0.CFDRFPTR0.UINT8[3] & 0xf0) >> 4;
         
         rx_msg_data0 = RCFDC0.CFDRFDF0_0.UINT32;
         rx_msg_data1 = RCFDC0.CFDRFDF1_0.UINT32;
         
	 rx_cnt++;
         RCFDC0.CFDRFPCTR0.UINT8[0] = 0xFF;
      }while((RCFDC0.CFDRFSTS0.UINT8[0] & 0x01) != 0x01);
      
	      
   	if(rx_msg_ID == 0x506)
	{
		m506_ID = rx_msg_ID;
		m506_Data0 = rx_msg_data0;
		m506_Data1 = rx_msg_data1;
		m506_Data2 = rx_msg_data2;
		sleep_REQ = ( (m506_Data0 & 0xF));		/* sleep Req is 0xB */	
		rx_ID506_CAN_Time_OUT_Err = 0;
	}
	else if(rx_msg_ID == 0x501)
	{
		m501_ID = rx_msg_ID;
		m501_Data0 = rx_msg_data0;
		m501_Data1 = rx_msg_data1;
		m501_Data2 = rx_msg_data2;
		hand_Shak_REQ = ( (m501_Data0 >> 0) & 0x1);	
		rx_ID501_CAN_Time_OUT_Err = 0;
	}
	else if(rx_msg_ID == 0xA1)
	{
		mA1_ID = rx_msg_ID;
		mA1_Data0 = rx_msg_data0;
		mA1_Data1 = rx_msg_data1;
		mA1_Data2 = rx_msg_data2;
		if((GETS_CAN == 0) || (GETS_CAN == 2) || (GETS_CAN == 3) )
		{
			charger_Status = ( (mA1_Data0 >> 0) & 0x1);
			side_Stand_CAN = ( (mA1_Data0 >> 1) & 0x1);
			pre_Char_Status = ( (mA1_Data0 >> 2) & 0x1);
			if( (charger_Status == 1) || (pre_Char_Status == 0))
			{
				vehicle_Not_Drivable = ACTIVATE;
			}
			else
			{
				vehicle_Not_Drivable = DEACTIVATE;
			}
		}
		rx_IDA1_CAN_Time_OUT_Err = 0;
	}
	else if(rx_msg_ID == 0xA2)
	{
		mA2_ID = rx_msg_ID;
		mA2_Data0 = rx_msg_data0;
		mA2_Data1 = rx_msg_data1;
		mA2_Data2 = rx_msg_data2;
		rx_IDA2_CAN_Time_OUT_Err = 0;
	}
	else if(rx_msg_ID == 0x700)	/* Tempervory purpose used */
	{
		m700_RX_Time_Cnt = 0;
		m700_ID = rx_msg_ID;
		m700_Data0 = rx_msg_data0;
		m700_Data1 = rx_msg_data1;
		m700_Data2 = rx_msg_data2;
		
		rst_CAN_Flg = ( (m700_Data0 >> 0) & 0x1);
	}
   }
}


/***************************** CAN Rx FIFO Interrupt *******************************/
#pragma interrupt CAN_Rx_FIFO_ISR(enable=true, channel=23, fpu=true, callt=false)
void CAN_Rx_FIFO_ISR(void)
{
     	__nop();
     	rx_flag = 1;
     	RCFDC0.CFDRFSTS0.UINT8[0] &= 0xF7;   				

     	if(RCFDC0.CFDRFSTS0.UINT8[0] & 0x01)  				
     	{
		RX_Fifo_empty = 1;
	        return;
	}
     	else if(RCFDC0.CFDRFSTS0.UINT8[0] & 0x02) 			
     	{
        	RX_fifo_full = 1;     
     	}
     	can0_rx();
}

/*************************** CAN Tx Channel 0 Interrupt ****************************/
#pragma interrupt CAN0_Tx_ISR(enable=true, channel=26, fpu=true, callt=false)
void CAN0_Tx_ISR(void)
{
#if TX_MODE == TX_BUFFER   
   	RCFDC0.CFDTMSTS0= 0x00;
   	__nop();
#else                  							
   	RCFDC0.CFDRFSTS0.UINT8[0] &= 0xE7;   				
#endif
   	INTC1.ICRCAN0TRX.BIT.RFRCAN0TRX = 0;
   	__nop();
}