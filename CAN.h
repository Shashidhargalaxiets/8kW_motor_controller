
#ifndef CAN_FD_H
#define CAN_FD_H

/**
****************************************************************************************************************************
*	Includes
****************************************************************************************************************************
**/
#include "macrodriver.h"

/**
****************************************************************************************************************************
*	Macro definitions
****************************************************************************************************************************
**/

#define TX_BUFFER 	1
#define TX_RX_FIFO	2

#define TX_MODE		TX_BUFFER

#define TX_ID_2		0x456
#define TX_ID_3		0x457

/* RX ID data Time Out error ALL Vlaues are ms */
#define ID506_TIME_INTERVEL	10	
#define ID501_TIME_INTERVEL	20	
#define IDA1_TIME_INTERVEL	30	
#define IDA2_TIME_INTERVEL	40	

/**
****************************************************************************************************************************
* @brief This function for the CAN0 Data tranmitting 
* @details
* @n @b Usage : 
* @param      : can_id, data_length, *dat_ptr, isExtented
* @return     : None
****************************************************************************************************************************
**/
void can0_tx(uint32_t can_id, uint8_t data_length, uint8_t * data_ptr, uint8_t isExtended);
/**
****************************************************************************************************************************
* @brief This function for the CAN0 Module Recerive the Signal 
* @details
* @n @b Usage: 
* @param     : None
* @return    : None
****************************************************************************************************************************
**/
void can0_rx(void);


#endif /* CAN_FD_H */
