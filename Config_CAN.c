/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_canfd.c                                                       */
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
/* Functions for CAN-FD initialization and testing.                          */
/*                                                                           */
/*===========================================================================*/

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "CAN.h"
#include "Config_CAN.h"

unsigned int i = 0;
/**
****************************************************************************************************************************
*	Global variables 
****************************************************************************************************************************
**/
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void R_RSCAN0_Init(void)
{
	RCFDC0.CFDGCTR.UINT32 = 0x00000005;
	RCFDC0.CFDGAFLCFG0.UINT32 = 0x00000000;
	RCFDC0.CFDC0FDCFG.UINT32 = 0x40000000;
	
	
	while((RCFDC0.CFDGSTS.UINT8[LL] && 0x04)==0x04);	
	
	RCFDC0.CFDGCTR.UINT8[LL] &= 0xFB;   	
	
	while(RCFDC0.CFDGSTS.UINT8[LL] != 0x01);	
	
	RCFDC0.CFDGCFG.UINT8[LL] = 0x10;   			// clk_xincan clock selected
	
	
	RCFDC0.CFDC0CTR.UINT8[LL] &= 0xFB;   		       
	
								
	while((RCFDC0.CFDC0STS.UINT8[LL] && 0x07) != 0x01);									

	RCFDC0.CFDC0FDCFG.UINT8[HH] |= 0x40;			
	
	/**************** Baud settings for clk_xincan = (24MHZ/2(clcok_Divider)) **********************/
	RCFDC0.CFDC0NCFG.UINT32 = 0x04091000;			/* 500Kbps , TSEG1=10, TSEG2=5 */
	
	/**************** Receive Rule settings for RX FIFO **********************/

//Receive Rule Configuration Register

	//Receive Rule Configuration Register
	RCFDC0.CFDGAFLCFG0.UINT8[HH] = 0x04;    
	  
	
	
	RCFDC0.CFDGAFLECTR.UINT8[LH] = 0x01;   
	RCFDC0.CFDGAFLECTR.UINT8[LL] = 0x00;   
	
	
	// Channel 0 Rx rule
	/****** receive rule 1 ********/
	//Receive Rule ID Register
	RCFDC0.CFDGAFLID0.UINT32 = 0x506;   // Ext, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM0.UINT32 = 0xDFFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_0.UINT8[LH] = 0x00;   // Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_0.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_0.UINT32 = 0x01;   	 // Receive FIFO 0 selected
	
	/****** receive rule 2 ********/
	//Receive Rule ID Register
	RCFDC0.CFDGAFLID0.UINT32 = 0x501;   // Ext, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM0.UINT32 = 0xDFFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_1.UINT8[LH] = 0x00;   // Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_1.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_1.UINT32 = 0x01;   	 // Receive FIFO 0 selected
	
	/****** receive rule 3 ********/
	//Receive Rule ID Register
	RCFDC0.CFDGAFLID0.UINT32 = 0xA1;   // Ext, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM0.UINT32 = 0xDFFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_2.UINT8[LH] = 0x00;   // Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_2.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_2.UINT32 = 0x01;   	 // Receive FIFO 0 selected
	
	/****** receive rule 4 ********/
	//Receive Rule ID Register
	RCFDC0.CFDGAFLID0.UINT32 = 0xA2;   // Ext, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM0.UINT32 = 0xDFFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_3.UINT8[LH] = 0x00;   // Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_3.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_3.UINT32 = 0x01;   	 // Receive FIFO 0 selected
	
	/****** receive rule 5 ********/
	//Receive Rule ID Register
	RCFDC0.CFDGAFLID0.UINT32 = 0x0700;   // Ext, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM0.UINT32 = 0x1FFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_4.UINT8[LH] = 0x00;   // Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_4.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_4.UINT32 = 0x01;   	 // Receive FIFO 0 selected
	
	

	// receive rule 5
	////Receive Rule ID Register
	RCFDC0.CFDGAFLID1.UINT16[L] = 0x0345;  // Standard, Data frame, 11 bit ID

	//Receive Rule Mask Register
	RCFDC0.CFDGAFLM1.UINT32 = 0x1FFFFFFF;   // ID bits are compared compared

	//Receive Rule Pointer 0 Register
	RCFDC0.CFDGAFLP0_1.UINT8[LH] = 0x00;    //Do not Use messsage buffer as we are using FIFO strategy
	RCFDC0.CFDGAFLP0_1.UINT8[LL] = 0x00;   // DLC Check is disabled.

	//Receive Rule Pointer 1 Register
	RCFDC0.CFDGAFLP1_1.UINT32 = 0x01;       // Receive FIFO 0 selected

//End of Receive Rule....

	RCFDC0.CFDGAFLECTR.UINT8[LH] = 0x00; 		

	RCFDC0.CFDRFCC0.UINT16[L] = 0x1272;  
	
	// End of Buffer Setting                 

	
	//----------- Global Interrupt Settings -------------------------------------
   
	RCFDC0.CFDGCTR.UINT8[LH] = 0x00;      			
   

//------------ Interrupt Controller Unit ------------------------------------

   	//CAN Receive FIFO Interrupt.
   	INTC1.ICRCANGRECC0.BIT.TBRCANGRECC0 = 1;
   	INTC1.ICRCANGRECC0.BIT.MKRCANGRECC0 = 0;
   	INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = 0;
	
	//CAN channel 0 Transmission interrupt
   	INTC1.ICRCAN0TRX.BIT.TBRCAN0TRX = 1;
   	INTC1.ICRCAN0TRX.BIT.MKRCAN0TRX = 0;
   	INTC1.ICRCAN0TRX.BIT.RFRCAN0TRX = 0;

//*********************** Operating mode **************************//
   
   	RCFDC0.CFDGCTR.UINT8[LL] = 0x00;      		
	
	for(i=0;i<0xfff;i++);   				// Wait for transistion
        			
   	RCFDC0.CFDRFCC0.UINT8[LL] |= 0x01;      	
	
	RCFDC0.CFDC0CTR.UINT8[LL] = 0x00;   	
	
	for(i=0;i<0xfff;i++);   				// Wait for transistion   
	 
	    
}
/**
****************************************************************************************************************************
* 	See header file for function definition. 
****************************************************************************************************************************
**/
void R_CAN_Init(void)
{
    Config_CAN_PORT();
     
    R_RSCAN0_Init(); 
}
